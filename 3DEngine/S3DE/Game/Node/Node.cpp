#include "Node.h"

s3de::Node::Node()
{
	this->parent = nullptr;
	generateId();
	setName("Node[" + std::to_string(getId())+ "]");
}

s3de::Node::Node(const std::string & name)
{
	generateId();
	setName(name);
}

s3de::Node::~Node()
{
	deleteChildren();
}

void s3de::Node::init()
{
	singleInit();
	for (Node* child : this->children)
		child->init();
}

void s3de::Node::update(float dt)
{
	this->transform.chain = sm::Mat4();
	singleUpdate(dt);
	if(this->parent != nullptr)
		this->transform.chain = this->parent->transform.chain * this->transform.getMatrix();
	else
		this->transform.chain = this->transform.getMatrix();
	for (Node* child : this->children)
		child->update(dt);
}

void s3de::Node::render(Renderer & renderer)
{
	singleRender(renderer);
	for (Node* child : this->children)
		child->render(renderer);
}

void s3de::Node::addChild(Node * child)
{
	child->parent = this;
	this->children.push_back(child);
}

s3de::Node* s3de::Node::removeChild(Node * child)
{
	for(unsigned int i = 0; i < this->children.size(); i++)
		if (this->children[i] == child)
			return removeChild(i);
	return nullptr;
}

s3de::Node* s3de::Node::removeChild(unsigned int index)
{
	Node* childToRemove = this->children[index];
	childToRemove = this->children[this->children.size() - 1];
	this->children.pop_back();
	return this->children[index];
}

void s3de::Node::deleteChildren()
{
	for (unsigned int i = 0; i < this->children.size(); i++)
		delete this->children[i];
}

bool s3de::Node::deleteChild(Node * child)
{
	for (unsigned int i = 0; i < this->children.size(); i++)
		if (this->children[i] == child)
		{
			deleteChild(i);
			return true;
		}
	return false;
}

void s3de::Node::deleteChild(unsigned int index)
{
	delete this->children[index];
	this->children[index] = this->children[this->children.size() - 1];
	this->children.pop_back();
}

s3de::Node * s3de::Node::getParent() const
{
	return this->parent;
}

s3de::Node * s3de::Node::getChild(unsigned int index) const
{
	return this->children[index];
}

std::vector<s3de::Node*>& s3de::Node::getChildren()
{
	return this->children;
}

void s3de::Node::setName(const std::string & name)
{
	this->name = name;

	// Find all occurrences of %id and replace them with the node´s id.
	size_t index = 0;
	std::string re(std::to_string(getId()));
	while (true)
	{
		index = this->name.find("%id", index);
		if (index == std::string::npos) break;
		this->name.replace(index, 3, re.c_str());
		index += re.size();
	}
}

std::string s3de::Node::getName() const
{
	return this->name;
}

s3de::Transform & s3de::Node::getTransform()
{
	return this->transform;
}

unsigned int s3de::Node::getId()
{
	return this->id;
}

void s3de::Node::printHierarchy(const std::string& prefix) const
{
	printf("%s> %s\n", prefix.c_str(), getName().c_str());
	for (Node* child : this->children)
		child->printHierarchy(prefix+"\t");
}

void s3de::Node::generateId()
{
	// An ID can not begin at 0.
	static unsigned int counter = 1;
	if (this->id == 0) this->id = counter++;
}
