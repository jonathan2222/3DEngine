#ifndef S3DE_NODE_H
#define S3DE_NODE_H

#include <vector>
#include <string>
#include "../../Graphics/Rendering/Renderer.h"
#include "../../Utils/Transform.h"

namespace s3de
{
	class Node
	{
	public:
		Node();
		Node(const std::string& name);
		virtual ~Node();

		void init();
		void update(float dt);
		void render(Renderer& renderer);

		virtual void singleInit() {};
		virtual void singleUpdate(float dt) {};
		virtual void singleRender(Renderer& renderer) {};

		void addChild(Node* child);
		// All the [remove] function will remove it from the list but not delete it, instead the function will return the pointer to that node. 
		Node* removeChild(Node* child);
		Node* removeChild(unsigned int index);
		// All the [delete] functions will delete all the child´s children too, and so on.
		void deleteChildren();
		bool deleteChild(Node* child);
		void deleteChild(unsigned int index);

		Node* getParent() const;
		Node* getChild(unsigned int index = 0) const;
		std::vector<Node*>& getChildren();

		void setName(const std::string& name);
		std::string getName() const;

		Transform& getTransform();

		unsigned int getId();

		void printHierarchy(const std::string& prefix = "") const;

	private:
		void generateId();

		unsigned int id;
		std::string name;
		Node* parent;
		std::vector<Node*> children;
		Transform transform;
	};
}

#endif
