#include "Renderer.h"

s3de::Renderer::Renderer()
{
	this->shader = new Shader("./Resources/Shaders/testShader");
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

void s3de::Renderer::render(const Model * model)
{
	render(model->getMeshes(), model->getMaterials());
}

void s3de::Renderer::render(const Model * model, const Material::MaterialData & material)
{
	render(model->getMeshes(), material);
}

void s3de::Renderer::render(const std::vector<Mesh*>& meshes, const Material::MaterialData & material) const
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

void s3de::Renderer::render(const std::vector<Mesh*>& meshes, const std::vector<Material::MaterialData>& materials) const
{
	unsigned int materialIndex = 0;
	shader->bind();
	if (isWireframeOn)
		shader->setUniform3f("emissionColor", 1.0f, 1.0f, 1.0f);
	else
		shader->setUniform3f("emissionColor", 0.0f, 0.0f, 0.0f);

	for (s3de::Mesh* m : meshes)
	{
		if(!materials.empty())
			ubo->setSubData(&(materials[materialIndex]), sizeof(s3de::Material::MaterialData), 0);
		m->getVertexBuffer().bind();
		m->getIndexBuffer().bind();
		glDrawElements(GL_TRIANGLES, m->getIndexBuffer().getCount(), GL_UNSIGNED_INT, nullptr);
		materialIndex++;
	}
}

void s3de::Renderer::resetMaterial()
{
	Material::MaterialData defaultMaterial = { { 0.1f, 0.1f, 0.1f, 1.0f },{ 0.5f, 0.5f, 0.5f, 1.0f },{ 1.0f, 0.0f, 0.0f, 90.0f } };
	this->ubo->setSubData(&defaultMaterial, sizeof(s3de::Material::MaterialData), 0);
}

s3de::Shader & s3de::Renderer::getShader()
{
	return *this->shader;
}
