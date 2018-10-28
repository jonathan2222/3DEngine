#include "ModelNode.h"

#include "../../../Utils/ModelLoader.h"

s3de::ModelNode::ModelNode() : Node()
{
	this->shouldDelete = false;
	setName("ModelNode[" + std::to_string(getId()) + "]");
}

s3de::ModelNode::ModelNode(const std::string & pathName) : Node()
{
	this->model = ModelLoader::loadModel(pathName);
	this->shouldDelete = true;
	setName("ModelNode[" + std::to_string(getId()) + "]");
}

s3de::ModelNode::ModelNode(Model* mode, bool shouldDelete) : Node()
{
	this->model = mode;
	this->shouldDelete = shouldDelete;
	setName("ModelNode[" + std::to_string(getId()) + "]");
}

s3de::ModelNode::~ModelNode()
{
	if (this->shouldDelete)
		delete this->model;
}

void s3de::ModelNode::singleRender(Renderer & renderer)
{
	renderer.getShader().bind();
	renderer.applyCamera();
	sm::Mat4 matrix = getTransform().chain;
	renderer.getShader().setUniformMatrix4fv("matrix", 1, false, &(matrix)[0][0]);
	renderer.render(this->model);
}

s3de::Model * s3de::ModelNode::getModel()
{
	return this->model;
}
