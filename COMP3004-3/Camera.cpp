#include "Camera.h"

using namespace glm;

mat4 model, projection, view, mvp;

Camera::Camera() {
	projection = perspective(45.0f, 1.0f, 0.1f, 100.0f);
	view = glm::lookAt(vec3(0,2,1), vec3(0,0,0), vec3(0,1,0));
	model = mat4(1.0f);
}

void Camera::turnLeft() {

}

void Camera::turnRight() {

}

void Camera::increaseElevation() {

}

void Camera::decreaseElevation() {

}

void Camera::increaseVelocity() {

}

void Camera::decreaseVelocity() {

}

void Camera::resetVelocity() {

}

void Camera::jumpTo() {

}

void Camera::lookAt() {

}

void Camera::followPath() {

}

glm::mat4 Camera::getMVP() {
	mvp = projection * view * model;
	return mvp;
}
