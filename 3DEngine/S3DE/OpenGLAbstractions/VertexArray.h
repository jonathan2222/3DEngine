#ifndef S3DE_VERTEX_ARRAY_H
#define S3DE_VERTEX_ARRAY_H

#include "VertexBuffer.h"
#include "VertexBufferLayout.h"

namespace s3de
{
	class VertexArray
	{
	public:
		VertexArray();
		~VertexArray();

		void addBuffer(const VertexBuffer& vertexBuffer, const VertexBufferLayout& layout);

		void bind() const;
		void unbind() const;

	private:
		unsigned int id;
	};
}

#endif