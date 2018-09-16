#ifndef S3DE_MODEL_LOADER_H
#define S3DE_MODEL_LOADER_H

#include <string>
#include <vector>
#include "../Graphics/Objects/Model.h"

namespace s3de
{
	class ModelLoader
	{
	public:
		ModelLoader();
		~ModelLoader();

		static Model* loadModel(const std::string& pathName);

	private:

	};
}

#endif
