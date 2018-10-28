#include "NodeGame.h"

#include "S3DE/Game/Node/Node.h"
#include "S3DE/Game/Node/Nodes/ModelNode.h"
#include "S3DE/Scene/Camera/FPSCamera.h"

#include "S3DE/Utils/ModelGenerator.h"

#include "S3DE/Physics/Physics.h"
#include "S3DE/Physics/Projectile.h"

#define TIME_STEP_FACTOR 1.0f

NodeGame::NodeGame()
{
}

NodeGame::NodeGame(const std::string & title, unsigned int width, unsigned int height)
{
}

NodeGame::~NodeGame()
{
}

void NodeGame::OnInitiate()
{
	this->sphere.radius = 0.25f;

	sm::Vec3 virtSize(0.0f, 10.f, 0.0f);

	// ----------------------------- TOP BALL -----------------------------
	s3de::Projectile* ball1 = new s3de::Projectile();
	ball1->vel = sm::Vec3(0.0f, 0.0f, 0.0f);
	ball1->pos = sm::Vec3(0.0f, virtSize.y - sphere.radius, 0.15f);
	ball1->angVel = sm::Vec3(0.0f, 0.0f, 0.0f);
	ball1->area = sphere.radius*sphere.radius*sm::MathsConstatns::PI;
	ball1->mass = 1.0f;
	ball1->cd = 0.4f;
	ball1->geometry = &sphere;
	ball1->setName("Ball[%id]");
	this->physics.addProjectile(ball1);
	s3de::ModelNode* ballModel = new s3de::ModelNode(s3de::ModelGenerator::generateSphere(((s3de::Sphere*)ball1->geometry)->radius), true);
	ball1->addChild(ballModel);
	this->root->addChild(ball1);
	// ----------------------------------------------------------------------

	// ---------------------------- BOTTOM BALL ----------------------------
	s3de::Projectile* ball2 = new s3de::Projectile();
	ball2->vel = sm::Vec3(0.0f, 30.0f, 0.0f);
	ball2->pos = sm::Vec3(0.0f, sphere.radius, 0.0f);
	ball2->angVel = sm::Vec3(0.0f, 0.0f, 0.0f);
	ball2->area = sphere.radius*sphere.radius*sm::MathsConstatns::PI;
	ball2->mass = 1.0f;
	ball2->cd = 0.4f;
	ball2->geometry = &sphere;
	ball2->setName("Ball2[%id]");
	this->physics.addProjectile(ball2);
	s3de::ModelNode* ballModel2 = new s3de::ModelNode(s3de::ModelGenerator::generateSphere(((s3de::Sphere*)ball2->geometry)->radius), true);
	ball2->addChild(ballModel2);
	this->root->addChild(ball2);
	// ----------------------------------------------------------------------

	// ---------------------------- TESTING NODE ----------------------------
	s3de::Node* object = new s3de::Node("Object[%id]");
	this->root->addChild(object);
	s3de::ModelNode* modelNode = new s3de::ModelNode(s3de::ModelGenerator::generateSphere(), true);
	modelNode->getTransform().setPosition({ -2.0f, 0.0f, 0.0f });
	s3de::ModelNode* modelNode2 = new s3de::ModelNode("./../3DEngine/S3DE/Resources/Models/Barrel.fbx");
	modelNode2->getTransform().setScale(0.5f);
	modelNode2->getTransform().rotateLocal(sm::MathsConstatns::PI / 2.f, sm::Vec3::VEC3_X);
	modelNode2->getTransform().setPosition({0.0f, 1.0f, 0.0f});
	modelNode->addChild(modelNode2);
	object->addChild(modelNode);
	// ----------------------------------------------------------------------

	s3de::Node* axis = new s3de::Node("Axis[%id]");
	this->root->addChild(axis);
	s3de::ModelNode* axisModel = new s3de::ModelNode("./../3DEngine/S3DE/Resources/Models/3DAxis.fbx");
	axisModel->getModel()->getMaterials()[0].ambientColor = sm::Vec4(0.2f);
	axisModel->getModel()->getMaterials()[0].diffuseColor = sm::Vec4(0.25f);
	axisModel->getModel()->getMaterials()[0].specularColor = sm::Vec4(0.2f);
	axisModel->getTransform().setPosition({ 0.0f, 0.0f, 0.0f });
	axis->addChild(axisModel);

	// ------------------------------- PLAYER -------------------------------
	this->player = new s3de::Node("Player[%id]");
	this->camera = new s3de::FPSCamera(sm::Vec3(0.0f, 0.0f, -1.0f), sm::Vec3(0.0f, 5.0f, 30.0f), display->getAspectRatio());
	this->renderer.setCamera(this->camera);
	this->player->addChild(this->camera);
	this->root->addChild(this->player);
	// ----------------------------------------------------------------------

	this->root->printHierarchy();

	this->renderer.resetMaterial();
}

void NodeGame::OnFrameUpdate(float dt)
{
	this->physics.update(dt*TIME_STEP_FACTOR);

	this->camera->update(display->getWindowPtr(), dt, display->getWidth(), display->getHeight());
	this->root->render(this->renderer);
}
