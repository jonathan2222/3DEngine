#ifndef S3DE_IGAME_H
#define S3DE_IGAME_H

#include "../Graphics/GUI/Display.h"
#include "ECS\Ecs.h"
#include "Node/Node.h"

namespace s3de
{
	class IGame
	{
	public:
		IGame();
		IGame(const std::string& title, unsigned int width, unsigned int height);
		virtual ~IGame();

		void run();

		virtual void OnInitiate() {}
		virtual void OnFrameUpdate(float dt) {}

	private:
		void init();
		void loop();

	protected:
		Ecs* ecs;
		Node* root;
		Display * display;
	};
}

#endif
