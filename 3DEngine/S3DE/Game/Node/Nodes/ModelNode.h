#ifndef S3DE_MODEL_NODE_H
#define S3DE_MODEL_NODE_H

#include <string>

#include "../Node.h"
#include "../../../Graphics/Objects/Model.h"

namespace s3de
{
	class ModelNode : public Node
	{
	public:
		ModelNode();
		ModelNode(const std::string& pathName);
		ModelNode(Model* model, bool shouldDelete = false);
		virtual ~ModelNode();

		void singleRender(Renderer& renderer) override;

		Model* getModel();

	private:
		Model* model;
		bool shouldDelete;
	};
}

#endif
