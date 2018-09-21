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
	s3de::Entity* entity = this->ecs->makeEntity<s3de::PositionComponent>();
	s3de::PositionComponent* comp = entity->getComponent<s3de::PositionComponent>(this->ecs);
	comp->position = sm::Vec3(1.0f, 0.0f, 0.5f);
}

void Game::OnFrameUpdate()
{
}
