#include "Renderer.h"

#include "../../Scene/Camera/Camera.h"

s3de::Renderer::Renderer()
{
	this->camera = nullptr;
	this->shader = new Shader("./../3DEngine/S3DE/Resources/Shaders/testShader");
	this->shader->bind();
	this->ubo = new UniformBuffer("Material", shader->getID(), 1);
	s3de::Material::MaterialData tempMatData;
	this->ubo->setData(&tempMatData, sizeof(s3de::Material::MaterialData));
	setWireframe(false);
}

s3de::Renderer::~Renderer()
{
	delete this->ubo;
	delete this->shader;
}

void s3de::Renderer::setWireframe(bool on)
{
	if (on)
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		isWireframeOn = true;
	}
	else
	{
		glPolygonMode(GL_FRONT, GL_FILL);
		isWireframeOn = false;
	}
}

void s3de::Renderer::render(Model * model)
{
	render(model->getMeshes(), model->getMaterials());
}

void s3de::Renderer::render(const Model * model, Material::MaterialData & material)
{
	render(model->getMeshes(), material);
}

void s3de::Renderer::render(const std::vector<Mesh*>& meshes, Material::MaterialData & material) const
{
	unsigned int materialIndex = 0;
	shader->bind();
	if (isWireframeOn)
		shader->setUniform3f("emissionColor", 1.0f, 1.0f, 1.0f);
	else
		shader->setUniform3f("emissionColor", 0.0f, 0.0f, 0.0f);

	ubo->setSubData(&material, sizeof(s3de::Material::MaterialData), 0);
	for (s3de::Mesh* m : meshes)
	{
		m->getVertexBuffer().bind();
		m->getIndexBuffer().bind();
		glDrawElements(GL_TRIANGLES, m->getIndexBuffer().getCount(), GL_UNSIGNED_INT, nullptr);
		materialIndex++;
	}
}

void s3de::Renderer::render(const std::vector<Mesh*>& meshes, std::vector<Material::MaterialData>& materials) const
{
	unsigned int materialIndex = 0;
	shader->bind();
	if (isWireframeOn)
		shader->setUniform3f("emissionColor", 1.0f, 1.0f, 1.0f);
	else
		shader->setUniform3f("emissionColor", 0.0f, 0.0f, 0.0f);

	for (s3de::Mesh* m : meshes)
	{
		if (!materials.empty())
			ubo->setSubData(&(materials[materialIndex]), sizeof(s3de::Material::MaterialData), 0);
		else
			resetMaterial();
		m->getVertexBuffer().bind();
		m->getIndexBuffer().bind();
		glDrawElements(GL_TRIANGLES, m->getIndexBuffer().getCount(), GL_UNSIGNED_INT, nullptr);
		materialIndex++;
	}
}

void s3de::Renderer::resetMaterial() const
{
	Material::MaterialData defaultMaterial = { { 0.1f, 0.1f, 0.1f, 1.0f },{ 0.5f, 0.5f, 0.5f, 1.0f },{ 1.0f, 0.0f, 0.0f, 90.0f } };
	this->ubo->setSubData(&defaultMaterial, sizeof(s3de::Material::MaterialData), 0);
}

void s3de::Renderer::setCamera(Camera * camera)
{
	this->camera = camera;
}

void s3de::Renderer::setCamera(sm::Mat4* vp, sm::Vec3* pos)
{
	this->vp = vp;
	this->camPos = pos;
}

void s3de::Renderer::applyCamera(Shader* shader) const
{
	Shader* localShader = shader;
	if (localShader == nullptr) localShader = this->shader;
	if (this->camera == nullptr)
	{
		localShader->setUniform3fv("camPos", 1, &(*this->camPos)[0]);
		localShader->setUniformMatrix4fv("vp", 1, false, &(*this->vp)[0][0]);
	}
	else
	{
		localShader->setUniform3fv("camPos", 1, &(this->camera->getPosition())[0]);
		localShader->setUniformMatrix4fv("vp", 1, false, &(this->camera->getVP())[0][0]);
	}
}

s3de::Shader & s3de::Renderer::getShader()
{
	return *this->shader;
}
