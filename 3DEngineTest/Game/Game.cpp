#include "Game.h"

#include "S3DE\Utils\Error.h"
#include "S3DE\Game\ECS\Components\PositionComponent.h"

Game::Game() : IGame()
{
}

Game::Game(const std::string & title, unsigned int width, unsigned int height) : IGame(title, width, height)
{
}

Game::~Game()
{
}

void Game::OnInitiate()
{
	// TODO: Make makeEntity work without using geComponent!
	s3de::PositionComponent comp;
	comp.position = sm::Vec3(1.0f, 1.0f, 1.0f);
	s3de::Entity* entity = this->ecs->makeEntity<s3de::PositionComponent>();
	//s3de::PositionComponent* comp = entity->getComponent<s3de::PositionComponent>(this->ecs);
	//comp->position = sm::Vec3(1.0f, 1.0f, 1.0f);
}

void Game::OnFrameUpdate()
{
}
