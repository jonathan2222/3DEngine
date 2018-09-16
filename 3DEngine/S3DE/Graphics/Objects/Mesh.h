#ifndef S3DE_MESH_H
#define S3DE_MESH_H

#include "Vertex.h"
#include "..\..\OpenGLAbstractions\VertexArray.h"
#include "..\..\OpenGLAbstractions\IndexBuffer.h"

#include <vector>

namespace s3de
{
	class Mesh
	{
	public:
		Mesh();
		Mesh(std::vector<Vertex>& vertices, std::vector<unsigned int>& indices);
		virtual ~Mesh();

		void uploadToGPU();

		VertexArray& getVertexBuffer();
		IndexBuffer& getIndexBuffer();

		std::vector<Vertex> vertices;
		std::vector<unsigned int> indices;

	private:
		VertexArray* va;
		IndexBuffer* ib;
		VertexBuffer* vb;
	};
}

#endif