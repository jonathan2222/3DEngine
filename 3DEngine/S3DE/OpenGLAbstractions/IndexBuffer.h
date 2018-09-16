#ifndef S3DE_INDEX_BUFFER_H
#define S3DE_INDEX_BUFFER_H

namespace s3de
{
	class IndexBuffer
	{
	public:
		IndexBuffer(const unsigned int* data, unsigned int count);
		~IndexBuffer();

		void bind() const;
		void unbind() const;

		inline unsigned int getCount() const { return this->count; }

	private:
		unsigned int id;
		unsigned int count;
	};
}

#endif