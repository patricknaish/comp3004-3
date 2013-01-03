#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/rotate_vector.hpp>


class Camera {
	private:
		glm::mat4 projection, view, mvp;
	public:
		Camera();
		void turnLeft(float rotation);
		void turnRight(float rotation);
		void increaseElevation(float rotation);
		void decreaseElevation(float rotation);
		void increaseVelocity();
		void decreaseVelocity();
		void resetVelocity();
		void jumpTo();
		void lookAt();
		void followPath();
		glm::mat4 getMVP(glm::mat4 model);
};

