#include <iostream>

#include "SM\Maths.h"

int main()
{
	sm::Quaternion q(0.5f, sm::Vec3::VEC3_Y);
	std::cout << "Hello World!" << std::endl;
	std::cout << "[Quaternion] Angle: " << q.getAngle() << ", Axis: (" << q.getAxis().x << ", " << q.getAxis().y << ", " << q.getAxis().z << ") " << std::endl;
	std::cin.get();
	return 0;
}