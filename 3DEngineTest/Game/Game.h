#ifndef TEST_GAME_H
#define TEST_GAME_H

#include "S3DE\Game\IGame.h"
#include "S3DE\Utils\ModelLoader.h"
#include "S3DE\Graphics\Rendering\Renderer.h"

class Game : public s3de::IGame
{
public:
	Game();
	Game(const std::string& title, unsigned int width, unsigned int height);
	virtual ~Game();

	void OnInitiate() override;
	void OnFrameUpdate(float dt) override;

private:
	s3de::Model* model;
	s3de::Renderer renderer;
};

#endif