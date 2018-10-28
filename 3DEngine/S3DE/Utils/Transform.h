#ifndef S3DE_TRANSFORM_H
#define S3DE_TRANSFORM_H

#include "SM/Matrices/Mat4.h"
#include "SM/Quaternion/Quaternion.h"

namespace s3de
{
	struct Transform
	{
		sm::Mat4 model;
		sm::Mat4 world;
		sm::Mat4 chain;

		void setScale(float scale)
		{
			this->model[0][0] = scale;
			this->model[1][1] = scale;
			this->model[2][2] = scale;
		}

		void setPosition(const sm::Vec3& pos)
		{
			world[3][0] = pos.x;
			world[3][1] = pos.y;
			world[3][2] = pos.z;
		}

		void rotateLocal(float angle, const sm::Vec3& axis)
		{
			sm::Quaternion q(angle, axis);
			this->model *= q.getMatrix4();
		}

		void rotate(float angle, const sm::Vec3& axis)
		{
			sm::Quaternion q(angle, axis);
			this->world *= q.getMatrix4();
		}

		sm::Mat4& getMatrix()
		{
			this->matrix = this->world * this->model;
			return this->matrix;
		}

	private:
		sm::Mat4 matrix;
	};
}

#endif
