#include "Camera.h"

#include "CameraConfig.h"
#include "SM/MathsTransform.h"

s3de::Camera::Camera()
{
	this->fov = DEFAULT_FOV;
	this->aspectRatio = 0.0f;
	this->zNear = DEFAULT_ZNEAR;
	this->zFar = DEFAULT_ZFAR;
	this->position = sm::Vec3();
}

s3de::Camera::Camera(const sm::Vec3 & direction, float aspectRatio)
{
	init(direction, sm::Vec3(), sm::Vec3(0.0f, 1.0f, 0.0f), DEFAULT_FOV, aspectRatio, DEFAULT_ZNEAR, DEFAULT_ZFAR);
}

s3de::Camera::Camera(const sm::Vec3 & direction, const sm::Vec3 & position, float aspectRatio)
{
	init(direction, position, sm::Vec3(0.0f, 1.0f, 0.0f), DEFAULT_FOV, aspectRatio, DEFAULT_ZNEAR, DEFAULT_ZFAR);
}

s3de::Camera::~Camera()
{
}

void s3de::Camera::create(const sm::Vec3 & direction, const sm::Vec3 & position, float aspectRatio)
{
	init(direction, position, sm::Vec3(0.0f, 1.0f, 0.0f), DEFAULT_FOV, aspectRatio, DEFAULT_ZNEAR, DEFAULT_ZFAR);
}

void s3de::Camera::updateVP(const sm::Vec3 & worldUp)
{
	updateView(worldUp);
	updateProj();
}

void s3de::Camera::updateProj()
{
	sm::MathsTransform::perspective(this->projMat, this->fov, this->aspectRatio, this->zNear, this->zFar);
}

void s3de::Camera::updateView(const sm::Vec3& worldUp)
{
	sm::MathsTransform::initCamera(this->viewMat, sm::Vec3(-this->viewMat[0][2], -this->viewMat[1][2], -this->viewMat[2][2]), worldUp, position);
}

void s3de::Camera::lookAt(const sm::Vec3 & target)
{
	sm::MathsTransform::initCamera(this->viewMat, sm::Maths::normalize(target - this->position), sm::Vec3(0.0f, 1.0f, 0.0f), this->position);
}

void s3de::Camera::lookIn(const sm::Vec3 & direction)
{
	sm::MathsTransform::initCamera(this->viewMat, direction, sm::Vec3(0.0f, 1.0f, 0.0f), this->position);
}

void s3de::Camera::setAspectRatio(float aspectRatio)
{
	this->aspectRatio = aspectRatio;
}

void s3de::Camera::setFOV(float fov)
{
	this->fov = fov;
}

void s3de::Camera::setZNear(float zNear)
{
	this->zNear = zNear;
}

void s3de::Camera::setZFar(float zFar)
{
	this->zFar = zFar;
}

void s3de::Camera::setPosition(const sm::Vec3 & position)
{
	this->position = position;
	this->viewMat[3][0] = -sm::Maths::dot(position, sm::Vec3(this->viewMat[0][0], this->viewMat[1][0], this->viewMat[2][0]));
	this->viewMat[3][1] = -sm::Maths::dot(position, sm::Vec3(this->viewMat[0][1], this->viewMat[1][1], this->viewMat[2][1]));
	this->viewMat[3][2] = sm::Maths::dot(position, sm::Vec3(-this->viewMat[0][2], -this->viewMat[1][2], -this->viewMat[2][2]));
}

const sm::Mat4 & s3de::Camera::getProj() const
{
	return this->projMat;
}

const sm::Mat4 & s3de::Camera::getView() const
{
	return this->viewMat;
}

sm::Mat4 s3de::Camera::getVP() const
{
	return this->projMat*this->viewMat;
}

float s3de::Camera::getAspectRatio() const
{
	return this->aspectRatio;
}

float s3de::Camera::getFOV() const
{
	return this->fov;
}

float s3de::Camera::getZNear() const
{
	return this->zNear;
}

float s3de::Camera::getZFar() const
{
	return this->zFar;
}

const sm::Vec3& s3de::Camera::getPosition() const
{
	return this->position;
}

const sm::Vec3 s3de::Camera::getDirection() const
{
	return sm::Vec3(-this->viewMat[0][2], -this->viewMat[1][2], -this->viewMat[2][2]);
}

const sm::Vec3 s3de::Camera::getUp() const
{
	return sm::Vec3(this->viewMat[0][1], this->viewMat[1][1], this->viewMat[2][1]);
}

const sm::Vec3 s3de::Camera::getRight() const
{
	return sm::Vec3(this->viewMat[0][0], this->viewMat[1][0], this->viewMat[2][0]);
}

void s3de::Camera::init(const sm::Vec3 & direction, const sm::Vec3 & position, const sm::Vec3 & worldUp, float fov, float aspectRatio, float zNear, float zFar)
{
	this->fov = fov;
	this->aspectRatio = aspectRatio;
	this->zNear = zNear;
	this->zFar = zFar;
	this->position = position;
	
	sm::MathsTransform::initCamera(this->viewMat, direction, worldUp, position);
	sm::MathsTransform::perspective(this->projMat, fov, aspectRatio, zNear, zFar);
}
