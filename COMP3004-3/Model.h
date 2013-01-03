#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <GL/glew.h>
#include <GL/glfw.h>

class Model {
	private:
		GLuint vao[1];
		GLuint vbo[3];
		GLuint textureID[1];
		std::string path;
		std::string mtllib;
		std::string name;

		std::vector<glm::vec3> vertices;
		std::vector<glm::vec2> textures;
		std::vector<glm::vec3> normals;

		glm::mat4 model;
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

