#include "Camera.h"

using namespace glm;

Camera::Camera() {
	projection = perspective(45.0f, 1.0f, 0.1f, 100.0f);
	view = glm::lookAt(vec3(0.4,0.4,0.4), vec3(0,0,0), vec3(0,1,0));
}

void Camera::turnLeft(float rotation) {
	projection = glm::rotate(projection, -rotation, vec3(0,1,0));
}

void Camera::turnRight(float rotation) {
	projection = glm::rotate(projection, rotation, vec3(0,1,0));
}

void Camera::increaseElevation(float rotation) {
	projection = glm::rotate(projection, -rotation, vec3(1,0,0));
}

void Camera::decreaseElevation(float rotation) {
	projection = glm::rotate(projection, rotation, vec3(1,0,0));
}

void Camera::increaseVelocity() {
	view = glm::translate(view, vec3(0,0,0.1f));
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

glm::mat4 Camera::getMVP(mat4 model) {
	mvp = projection * view * model;
	return mvp;
}
