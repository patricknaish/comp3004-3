#pragma once
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/rotate_vector.hpp>


class Camera {
	private:
		glm::mat4 projection, view, mvp;
		glm::vec3 pos, target, direction;
		float yaw;
		double velocity;
	public:
		Camera();
		void turnLeft(float rotation);
		void turnRight(float rotation);
		void increaseElevation(float delta);
		void decreaseElevation(float delta);
		void increaseVelocity(float delta);
		void decreaseVelocity(float delta);
		void resetVelocity();
		void move();
		void jumpTo();
		void lookAt();
		void followPath();
		glm::mat4 getMVP(glm::mat4 model);
};

