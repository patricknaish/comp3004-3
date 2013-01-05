#include "Camera.h"

using namespace glm;

Camera::Camera() {
	pos = vec3(-0.4f, 0.3f, -0.4f);
	yaw = 0.f;
	direction = vec3(1.f, 0.f, 0.f);
	target = pos + direction;
	velocity = 0.f;
	projection = perspective(45.0f, 1.0f, 0.1f, 100.0f);
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
	if (height > 0.8f) {
		height = 0.8f;
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
	if (velocity + delta*0.00001 > 0.00004) {
		velocity = 0.00004;
	}
	else {
		velocity += delta*0.00001;
	}
}

void Camera::decreaseVelocity(float delta) {
	if (velocity - delta*0.00001< 0.0) {
		velocity = 0.0;
	}
	else {
		velocity -= delta*0.00001;
	}
}

void Camera::resetVelocity() {
	velocity = 0.f;
}

void Camera::move() {
	pos = pos + vec3(direction.x*velocity, direction.y*velocity, direction.z*velocity);
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
