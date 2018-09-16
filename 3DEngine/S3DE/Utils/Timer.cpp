#include "Timer.h"

s3de::Timer::Timer()
{
	restart();
}

s3de::Timer::~Timer()
{
}

void s3de::Timer::restart()
{
	this->startTime = std::chrono::high_resolution_clock::now();
	this->currTime = this->startTime;
	this->preTime = this->startTime;
	this->dt = 0.0f;
}

void s3de::Timer::update()
{
	this->currTime = std::chrono::high_resolution_clock::now();
	this->dt = std::chrono::duration<float>(this->currTime - this->preTime).count();
	this->preTime = this->currTime;
}

float s3de::Timer::getTime()
{
	return std::chrono::duration<float>(this->startTime - this->currTime).count();
}

float s3de::Timer::getDeltaTime()
{
	return this->dt;
}
