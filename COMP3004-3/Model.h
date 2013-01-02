#pragma once
#include <string>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <GL/glew.h>
#include <GL/glfw.h>

class Model {
	public:
		Model(std::string sourceFile);
		void load(void);
		GLuint Model::loadTexture(std::string texPath);
		void rotate(float rotation, glm::vec3 axes);
		void translate(glm::vec3 translations);
		void scale(glm::vec3 scales);
		void render(void);
		glm::mat4 getMatrix(void);
};

