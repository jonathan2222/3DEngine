#include "Game.h"

#include "S3DE\Utils\Error.h"
#include "S3DE\Game\ECS\Components\PositionComponent.h"
#include "S3DE\Game\ECS\Components\BoolComponent.h"
#include "S3DE\Game\ECS\Systems\TestSystem.h"
#include "S3DE\Game\ECS\Systems\HealthSystem.h"
#include <random>
#include <time.h>

Game::Game() : IGame()
{
	std::srand(time(NULL));
}

Game::Game(const std::string & title, unsigned int width, unsigned int height) : IGame(title, width, height)
{
}

Game::~Game()
{
}

void Game::OnInitiate()
{
	// ------------------ ADD ENTITIES -----------------
	s3de::Entity* entity = this->ecs->makeEntity<s3de::PositionComponent, s3de::BoolComponent>();
	s3de::Entity* entity2 = this->ecs->makeEntity<s3de::BoolComponent>();
	s3de::Entity* entity3 = this->ecs->makeEntity<s3de::PositionComponent>();
	s3de::Entity* entity4 = this->ecs->makeEntity<s3de::HealthComponent>();

	// ----------------- TEST ENTITIES -----------------
	s3de::PositionComponent* comp = entity->getComponent<s3de::PositionComponent>();
	comp->position = sm::Vec3(1.0f, 1.0f, 1.0f);
	entity->getComponent<s3de::BoolComponent>()->b = false;

	// ------------------ ADD SYSTEMS ------------------
	s3de::TestSystem* sys = new s3de::TestSystem();
	this->ecs->addSystem(sys);
	s3de::HealthSystem* sys2 = new s3de::HealthSystem();
	this->ecs->addSystem(sys2);

	// ------------------ INIT SYSTEMS -----------------
	this->ecs->initSystems();
}

void Game::OnFrameUpdate(float dt)
{
	this->ecs->updateSystems(dt);
}
