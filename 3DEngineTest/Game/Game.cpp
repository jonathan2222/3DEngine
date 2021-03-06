#include "Game.h"

#include "S3DE\Utils\Error.h"
#include "S3DE\Game\ECS\Components\PositionComponent.h"
#include "S3DE\Game\ECS\Components\BoolComponent.h"
#include "S3DE\Game\ECS\Systems\TestSystem.h"
#include "S3DE\Game\ECS\Systems\HealthSystem.h"
#include <random>
#include <time.h>

#include "S3DE\Game\ECS\Systems\RenderSystem.h"
#include "S3DE\Game\ECS\Systems\CameraSystem.h"
#include "S3DE\Utils\ModelLoader.h"
#include "S3DE\Utils\ModelGenerator.h"
#include "SM\MathsTransform.h"

Game::Game() : IGame()
{
	std::srand(time(NULL));
}

Game::Game(const std::string & title, unsigned int width, unsigned int height) : IGame(title, width, height)
{
}

Game::~Game()
{
	delete this->model;
}

void Game::OnInitiate()
{
	this->model = s3de::ModelGenerator::generateSphere();
	//this->model = s3de::ModelLoader::loadModel("./../3DEngine/S3DE/Resources/Models/Barrel.fbx");

	// ------------------ ADD ENTITIES -----------------
	s3de::CameraComponent camComp;
	camComp.position = sm::Vec3(0.0f, 0.0f, 5.0f);
	camComp.direction = sm::Vec3(0.0f, 0.0f, -1.0f);
	camComp.fov = sm::MathsConstatns::PI / 4.f;
	camComp.zNear = 0.1f;
	camComp.zFar = 100.f;
	s3de::Entity* player = this->ecs->makeEntity<s3de::CameraComponent>(camComp);
	s3de::CameraComponent* cam = player->getComponent<s3de::CameraComponent>();
	renderer.setCamera(&cam->matrix, &cam->position);

	s3de::Entity* entity = this->ecs->makeEntity<s3de::PositionComponent, s3de::BoolComponent>();
	s3de::Entity* entity2 = this->ecs->makeEntity<s3de::BoolComponent>();
	s3de::Entity* entity3 = this->ecs->makeEntity<s3de::PositionComponent>();
	s3de::Entity* entity4 = this->ecs->makeEntity<s3de::HealthComponent>();
	
	s3de::RenderableComponent renderableComponent;
	renderableComponent.model = this->model;
	s3de::TransformComponent transformComponent;
	transformComponent.model = sm::MathsTransform::rotationMat(sm::MathsConstatns::PI*.5f, 0.0f, 0.0f);
	transformComponent.world = sm::MathsTransform::translate(0.0f, 0.0f, -2.0f);
	s3de::Entity* barrelEntity = this->ecs->makeEntity<s3de::RenderableComponent, s3de::TransformComponent>(renderableComponent, transformComponent);
	
	s3de::HealthComponent healthComp;
	const unsigned int SIDE = 10;
	for (unsigned int i = 0; i < SIDE*SIDE; i++)
	{
		float x = (float)(i % SIDE);
		float y = (float)i / SIDE;
		s3de::TransformComponent transform;
		//transformComponent.model = sm::MathsTransform::rotationMat(sm::MathsConstatns::PI*.5f, 0.0f, 0.0f);
		transform.world = sm::MathsTransform::translate(x-(float)SIDE*.5f, y-(float)SIDE*.5f, 0.0f);
		this->ecs->makeEntity<s3de::RenderableComponent, s3de::TransformComponent, s3de::HealthComponent>(renderableComponent, transform, healthComp);
	}

	// ----------------- TEST ENTITIES -----------------
	s3de::PositionComponent* comp = entity->getComponent<s3de::PositionComponent>();
	comp->position = sm::Vec3(1.0f, 1.0f, 1.0f);
	entity->getComponent<s3de::BoolComponent>()->b = false;

	// ------------------ ADD SYSTEMS ------------------
	this->ecs->addSystem(new s3de::CameraSystem(), this->display);
	this->ecs->addSystem(new s3de::TestSystem());
	this->ecs->addSystem(new s3de::HealthSystem());
	this->ecs->addRenderSystem(new s3de::RenderSystem());

	// ------------------ INIT SYSTEMS -----------------
	this->ecs->initSystems(renderer);
}

void Game::OnFrameUpdate(float dt)
{
	this->ecs->updateSystems(renderer, dt);
}
