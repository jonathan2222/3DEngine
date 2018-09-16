#include "Mesh.h"

s3de::Mesh::Mesh()
{
	this->va = nullptr;
	this->ib = nullptr;
	this->vb = nullptr;
}

s3de::Mesh::Mesh(std::vector<Vertex>& vertices, std::vector<unsigned int>& indices)
{
	this->vertices.reserve(vertices.size());
	for (Vertex v : vertices)
		this->vertices.push_back(v);

	this->indices.reserve(indices.size());
	for (unsigned int i : indices)
		this->indices.push_back(i);

	uploadToGPU();
}

s3de::Mesh::~Mesh()
{
	delete this->va;
	delete this->ib;
	delete this->vb;
}

void s3de::Mesh::uploadToGPU()
{
	delete this->va;
	delete this->ib;
	delete this->vb;

	this->va = new VertexArray();
	this->va->bind();
	this->vb = new VertexBuffer(&this->vertices[0], sizeof(Vertex)*this->vertices.size());
	VertexBufferLayout layout;
	layout.push<float>(3); // Position
	layout.push<float>(3); // Normal
	va->addBuffer(*this->vb, layout);
	this->ib = new IndexBuffer(&this->indices[0], this->indices.size());
	this->va->unbind();
}

s3de::VertexArray & s3de::Mesh::getVertexBuffer()
{
	return *this->va;
}

s3de::IndexBuffer & s3de::Mesh::getIndexBuffer()
{
	return *this->ib;
}
