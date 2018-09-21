#ifndef S3DE_IGAME_H
#define S3DE_IGAME_H

#include "../Graphics/GUI/Display.h"
#include "ECS\Ecs.h"

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
		virtual void OnFrameUpdate() {}

	protected:
		Ecs* ecs;

	private:
		void init();
		void loop();

		Display * display;
	};
}

#endif
