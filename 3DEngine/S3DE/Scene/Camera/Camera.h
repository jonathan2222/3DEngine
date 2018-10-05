#ifndef S3DE_CAMERA_H
#define S3DE_CAMERA_H

#include "GLFW\glfw3.h"

#include "SM/Vectors/Vec3.h"
#include "SM/Matrices/Mat4.h"

namespace s3de
{
	class Camera
	{
	public:
		Camera();
		Camera(const sm::Vec3& direction, float aspectRatio);
		Camera(const sm::Vec3& direction, const sm::Vec3& position, float aspectRatio);
		virtual ~Camera();

		virtual void update(GLFWwindow* window, float dt, int windowWidth, int windowHeight) {};

		void create(const sm::Vec3& direction, const sm::Vec3& position, float aspectRatio);

		void updateVP(const sm::Vec3& worldUp);
		void updateProj();
		void updateView(const sm::Vec3& worldUp);

		void lookAt(const sm::Vec3& target);
		void lookIn(const sm::Vec3& direction);

		void setAspectRatio(float aspectRatio);
		void setFOV(float fov);
		void setZNear(float zNear);
		void setZFar(float zFar);
		void setPosition(const sm::Vec3& position);

		const sm::Mat4& getProj() const;
		const sm::Mat4& getView() const;
		sm::Mat4 getVP() const;

		float getAspectRatio() const;
		float getFOV() const;
		float getZNear() const;
		float getZFar() const;
		const sm::Vec3& getPosition() const;
		const sm::Vec3 getDirection() const;
		const sm::Vec3 getUp() const;
		const sm::Vec3 getRight() const;

	private:
		void init(const sm::Vec3& direction, const sm::Vec3& position, const sm::Vec3& worldUp, float fov, float aspectRatio, float zNear, float zFar);

	private:
		sm::Mat4 projMat;
		sm::Mat4 viewMat;

		sm::Vec3 position;

		float aspectRatio;
		float fov;
		float zNear;
		float zFar;
	};
}

#endif

