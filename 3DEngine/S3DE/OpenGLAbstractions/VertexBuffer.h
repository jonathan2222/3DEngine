#ifndef S3DE_VERTEX_BUFFER_H
#define S3DE_VERTEX_BUFFER_H

namespace s3de
{
	class VertexBuffer
	{
	public:
		VertexBuffer(const void* data, unsigned int size);
		~VertexBuffer();

		void bind() const;
		void unbind() const;

	private:
		unsigned int id;
	};
}

#endif
