#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/rotate_vector.hpp>


class Camera {
	public:
		Camera();
		void turnLeft();
		void turnRight();
		void increaseElevation();
		void decreaseElevation();
		void increaseVelocity();
		void decreaseVelocity();
		void resetVelocity();
		void jumpTo();
		void lookAt();
		void followPath();
		glm::mat4 getMVP();
};

