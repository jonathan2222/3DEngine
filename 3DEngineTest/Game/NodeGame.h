#ifndef NODE_GAME_H
#define NODE_GAME_H

#include "S3DE\Game\IGame.h"
#include "S3DE\Utils\ModelLoader.h"
#include "S3DE\Graphics\Rendering\Renderer.h"
#include "S3DE/Scene/Camera/FPSCamera.h"

#include "S3DE/Physics/Physics.h"

class NodeGame : public s3de::IGame
{
public:
	NodeGame();
	NodeGame(const std::string& title, unsigned int width, unsigned int height);
	virtual ~NodeGame();

	void OnInitiate() override;
	void OnFrameUpdate(float dt) override;

private:
	s3de::Sphere sphere;
	s3de::Physics physics;
	s3de::Model* model;
	s3de::Node* player;
	s3de::Renderer renderer;
	s3de::FPSCamera* camera;
};

#endif