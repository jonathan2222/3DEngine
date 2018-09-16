#include "VertexArray.h"

s3de::VertexArray::VertexArray()
{
	glGenVertexArrays(1, &this->id);
}

s3de::VertexArray::~VertexArray()
{
	glDeleteVertexArrays(1, &this->id);
}

void s3de::VertexArray::addBuffer(const VertexBuffer & vertexBuffer, const VertexBufferLayout & layout)
{
	bind();
	vertexBuffer.bind();
	const auto& elements = layout.getElements();
	unsigned int offset = 0;
	for (unsigned int i = 0; i < elements.size(); i++)
	{
		const auto& element = elements[i];
		glEnableVertexAttribArray((int)i);
		glVertexAttribPointer((int)i, element.count, element.type, element.normalized, layout.getStride(), (const char*)offset);
		offset += element.count*VertexBufferElement::getSizeOfType(element.type);
	}
}

void s3de::VertexArray::bind() const
{
	glBindVertexArray(this->id);
}

void s3de::VertexArray::unbind() const
{
	glBindVertexArray(0);
}
