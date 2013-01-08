#include "Camera.h"

using namespace glm;

Camera::Camera() {
	pos = vec3(0.4f, 0.05f, 0.4f);
	yaw = 180.f;
	direction = vec3(glm::cos(yaw), 0, glm::sin(yaw));
	target = pos + direction;
	velocity = 0.f;
	projection = perspective(45.0f, 1.0f, 0.0001f, 100.0f);
	view = glm::lookAt(pos, target, vec3(0,1,0));
}

void Camera::turnLeft(float rotation) {
	yaw -= rotation;
	if (yaw > 360.f) {
		yaw = 0.f;
	}
	direction = vec3(glm::cos(yaw), 0, glm::sin(yaw));
	target = pos + direction;
	view = glm::lookAt(pos, target, vec3(0,1,0));
}

void Camera::turnRight(float rotation) {
	yaw += rotation;
	if (yaw > 360.f) {
		yaw = 0.f;
	}
	direction = vec3(glm::cos(yaw), 0, glm::sin(yaw));
	target = pos + direction;
	view = glm::lookAt(pos, target, vec3(0,1,0));
}

void Camera::increaseElevation(float delta) {
	float height = pos.y + delta;
	if (height > 2.8f) {
		height = 2.8f;
	}
	pos = vec3(pos.x, height, pos.z);
	direction = vec3(glm::cos(yaw), 0, glm::sin(yaw));
	target = pos + direction;
	view = glm::lookAt(pos, target, vec3(0,1,0));
}

void Camera::decreaseElevation(float delta) {
	float height = pos.y - delta;
	if (height < 0.f) {
		height = 0.f;
	}
	pos = vec3(pos.x, height, pos.z);
	direction = vec3(glm::cos(yaw), 0, glm::sin(yaw));
	target = pos + direction;
	view = glm::lookAt(pos, target, vec3(0,1,0));
}

void Camera::increaseVelocity(float delta) {
	delta /= 10;
	if (velocity + delta > 1) {
		velocity = 1;
	}
	else {
		velocity += delta;
	}
}

void Camera::decreaseVelocity(float delta) {
	delta /= 10;
	if (velocity - delta < 0.0) {
		velocity = 0.0;
	}
	else {
		velocity -= delta;
	}
}

void Camera::resetVelocity() {
	velocity = 0.f;
}

void Camera::move(float delta) {
	pos = pos + vec3(direction.x*velocity*delta, direction.y*velocity*delta, direction.z*velocity*delta);
	direction = vec3(glm::cos(yaw), 0, glm::sin(yaw));
	target = pos + direction;
	view = glm::lookAt(pos, target, vec3(0,1,0));
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
