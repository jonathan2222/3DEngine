#include "UniformBuffer.h"

#include "GL\glew.h"

s3de::UniformBuffer::UniformBuffer(const std::string & name, unsigned int shader, unsigned int bindingPoint)
{
	this->bindingPoint = bindingPoint;
	this->index = glGetUniformBlockIndex(shader, name.c_str());
	glUniformBlockBinding(shader, this->index, this->bindingPoint);
	glGenBuffers(1, &this->id);
}

s3de::UniformBuffer::~UniformBuffer()
{
	glDeleteBuffers(1, &this->id);
}

void s3de::UniformBuffer::setData(const void * data, unsigned int size)
{
	glBindBuffer(GL_UNIFORM_BUFFER, this->id);
	glBufferData(GL_UNIFORM_BUFFER, size, data, GL_DYNAMIC_DRAW);
	glBindBufferBase(GL_UNIFORM_BUFFER, this->bindingPoint, this->id);
	glBindBuffer(GL_UNIFORM_BUFFER, 0);
}

void s3de::UniformBuffer::setSubData(const void * data, unsigned int size, unsigned int offset)
{
	glBindBuffer(GL_UNIFORM_BUFFER, this->id);
	glBufferSubData(GL_UNIFORM_BUFFER, offset, size, data);
	glBindBuffer(GL_UNIFORM_BUFFER, 0);
}
