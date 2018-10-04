#include "Game.h"

#include "S3DE\Utils\Error.h"
#include "S3DE\Game\ECS\Components\PositionComponent.h"
#include "S3DE\Game\ECS\Components\BoolComponent.h"
#include "S3DE\Game\ECS\Systems\TestSystem.h"

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
	s3de::Entity* entity = this->ecs->makeEntity<s3de::PositionComponent, s3de::BoolComponent>();
	s3de::PositionComponent* comp = entity->getComponent<s3de::PositionComponent>(this->ecs);
	comp->position = sm::Vec3(1.0f, 1.0f, 1.0f);
	entity->getComponent<s3de::BoolComponent>(this->ecs)->b = false;

	s3de::Entity* entity2 = this->ecs->makeEntity<s3de::BoolComponent>();

	s3de::Entity* entity3 = this->ecs->makeEntity<s3de::PositionComponent>();

	s3de::TestSystem* sys = new s3de::TestSystem();
	this->ecs->addSystem(sys);
}

void Game::OnFrameUpdate()
{
}
