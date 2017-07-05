#include "Camera.h"



Camera::Camera()
{
	position = glm::vec3(0, 1, 5);
	rot = glm::vec3(0, 0, -1);
	angle = 0;
}


Camera::~Camera()
{
}

void Camera::rotation(float deltaAngle) {
	angle += deltaAngle;
	rot.x = sin(angle);
	rot.z = -cos(angle);
}
void Camera::translation(float deltaMove) {
	position.x += deltaMove * rot.x * 0.1f;
	position.z += deltaMove * rot.z * 0.1f;
}

glm::mat4 Camera::getView() {
	return glm::lookAt(
		glm::vec3(position.x, position.y, position.z),
		glm::vec3(position.x + rot.x, position.y + rot.y, position.z + rot.z),
		glm::vec3(0.0f, 1.0f, 0.0f));
}