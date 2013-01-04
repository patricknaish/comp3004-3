#define _USE_MATH_DEFINES

#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <GL/glew.h>
#include <GL/glfw.h>
#include "Camera.h"
#include "Model.h"

using namespace std; 
using namespace glm;

GLchar *vertexsource, *fragmentsource;
GLuint vertexshader, fragmentshader;
GLuint objectShaderProgram, skyboxShaderProgram;

Camera camera = Camera();

bool rotatingLeft = false;
bool rotatingRight = false;
bool rotatingUp = false;
bool rotatingDown = false;

const float speed = 60;

//Modified from Tutorial 2
char* filetobuf(string file) { /* A simple function that will read a file into an allocated char pointer buffer */
    FILE *fptr;
    long length;
    char *buf;
    fptr = fopen(file.c_str(), "rb"); /* Open file for reading */
    if (!fptr) { /* Return NULL on failure */
        fprintf(stderr, "failed to open %s\n", file.c_str());
        return NULL;
    }
    fseek(fptr, 0, SEEK_END); /* Seek to the end of the file */
    length = ftell(fptr); /* Find out how many bytes into the file we are */
    buf = (char*)malloc(length+1); /* Allocate a buffer for the entire length of the file and a null terminator */
    fseek(fptr, 0, SEEK_SET); /* Go back to the beginning of the file */
    fread(buf, length, 1, fptr); /* Read the contents of the file in to the buffer */
    fclose(fptr); /* Close the file */
    buf[length] = 0; /* Null terminator */
	printf("%s read successfully\n", file.c_str());
    return buf; /* Return the buffer */
}

//From Tutorial 2
GLuint setupShaders(string vert, string frag) {
	GLuint programID;
	char text[1000];
    int length;
    fprintf(stderr, "Setting up shaders...\n"); /* Allocate and assign two Vertex Buffer Objects to our handle */
    vertexsource = filetobuf(vert); /* Read our shaders into the appropriate buffers */
    fragmentsource = filetobuf(frag);
    vertexshader = glCreateShader(GL_VERTEX_SHADER); /* Assign our handles a "name" to new shader objects */
    fragmentshader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(vertexshader, 1, (const GLchar**)&vertexsource, 0); /* Associate the source code buffers with each handle */
    glShaderSource(fragmentshader, 1, (const GLchar**)&fragmentsource, 0);
    glCompileShader(fragmentshader);/* Compile our shader objects */
    glCompileShader(vertexshader);
    programID = glCreateProgram();/* Assign our program handle a "name" */
    glAttachShader(programID, vertexshader); /* Attach our shaders to our program */
    glAttachShader(programID, fragmentshader);
	glBindAttribLocation(programID, 0, "position");
	glBindAttribLocation(programID, 1, "in_normal");
    glLinkProgram(programID); /* Link our program */
    glGetProgramInfoLog(programID, 1000, &length, text); // Check for errors
    if(length>0)
        fprintf(stderr, "Validating shader programs...\n%s\n",text );
	return programID;
}

class Scene {
	private:
		int running;	
	public:
		Scene() {}
		void run() {

			Model skybox("models/plane.obj");
			skybox.load();
			skybox.loadTexture("textures/sky512.tga");

			Model landscape("models/landscape.obj");
			landscape.load();
			landscape.loadTexture("textures/mars.tga");

			Model dome("models/dome.obj");
			dome.load();
			dome.loadTexture("textures/dome.tga");

			glUseProgram(skyboxShaderProgram);
			GLuint SkyboxMatrixID = glGetUniformLocation(skyboxShaderProgram, "MVP");

			glUseProgram(objectShaderProgram);
			GLuint ObjectMatrixID = glGetUniformLocation(objectShaderProgram, "MVP");

			vec4 LightV = vec4(0.f, 0.f, .8f, 1.f);
			GLuint LightVID = glGetUniformLocation(objectShaderProgram, "LightV");
			glUniform4fv(LightVID, 1, &LightV[0]);
				
			vec4 LightC = vec4(0.6f, .2f, .2f, 1.f);
			GLuint LightCID = glGetUniformLocation(objectShaderProgram, "LightC");
			glUniform4fv(LightCID, 1, &LightC[0]);
				
			vec4 Material = vec4(1.f, 0.f, 0.f, 1.f);
			GLuint MaterialID = glGetUniformLocation(objectShaderProgram, "Material");
			glUniform4fv(MaterialID, 1, &Material[0]);

			//Running stuff
			running = GL_TRUE;
			double old_time = 0, current_time = 0;
			ostringstream title;
			float rate = 0.f;
			while( running ) { 
				current_time = glfwGetTime();
				rate = (float)((current_time - old_time) * speed);
				old_time = current_time;
				if (rotatingLeft) {
					camera.turnLeft(rate);
				}
				if (rotatingRight) {
					camera.turnRight(rate);
				}
				if (rotatingUp) {
					camera.increaseElevation(rate);
				}
				if (rotatingDown) {
					camera.decreaseElevation(rate);
				}
				//landscape.rotate(rate, vec3(0,1,0));
				//skybox.rotate(rate, vec3(0,1,0));
				glClearColor(0,0,0,0);
				glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

				glUseProgram(skyboxShaderProgram);
				mat4 MVP = camera.getMVP(skybox.getMatrix());
				glUniformMatrix4fv(SkyboxMatrixID, 1, GL_FALSE, &MVP[0][0]);
				skybox.render();

				glUseProgram(objectShaderProgram);
				MVP = camera.getMVP(landscape.getMatrix());
				glUniformMatrix4fv(ObjectMatrixID, 1, GL_FALSE, &MVP[0][0]);
				landscape.render();
				
				MVP = camera.getMVP(dome.getMatrix());
				glUniformMatrix4fv(ObjectMatrixID, 1, GL_FALSE, &MVP[0][0]);
				dome.render();

				glFlush();
				glfwSwapBuffers();
				if (!glfwGetWindowParam(GLFW_OPENED)) {
					running = GL_FALSE;
				}
			}
		}
		void interrupt() {
			running = GL_FALSE;
		}
};

void GLFWCALL keyHandler(int key, int action) {
	if (action == GLFW_PRESS) {
		if (key == GLFW_KEY_ESC || key == 'Q' || key == 'q') {
			glfwTerminate();
			exit(EXIT_SUCCESS);
		}
		switch(key) {
			case GLFW_KEY_UP: camera.increaseVelocity(); break;
			case GLFW_KEY_DOWN: camera.decreaseVelocity(); break;
			case GLFW_KEY_RIGHT: rotatingRight = true; break;
			case GLFW_KEY_LEFT: rotatingLeft = true; break;
			case GLFW_KEY_PAGEUP: rotatingUp = true; break;
			case GLFW_KEY_PAGEDOWN: rotatingDown = true; break;
			case GLFW_KEY_SPACE: camera.resetVelocity(); break;
			case 'P': ;
			case 'p': camera.jumpTo(); break;
			case 'Y': ;
			case 'y': camera.jumpTo(); break;
			case 'U': ;
			case 'u': camera.jumpTo(); break;
			case 'T': ;
			case 't': camera.followPath(); break;
			case 'E': ;
			case 'e': camera.jumpTo(); break;
			case 'R': ;
			case 'r': ; break;
		}
	}
	else if (action == GLFW_RELEASE) {
		switch(key) {
			case GLFW_KEY_RIGHT: rotatingRight = false; break;
			case GLFW_KEY_LEFT: rotatingLeft = false; break;
			case GLFW_KEY_PAGEUP: rotatingUp = false; break;
			case GLFW_KEY_PAGEDOWN: rotatingDown = false; break;
		}
	}
}

int main(void) {
	printf("Initialising... \n");
	if (!glfwInit()) {
		printf("Could not initialise GLFW\n");
		exit(EXIT_FAILURE);
	}
	else {
		printf("Initialised GLFW\n");
	}
	glfwOpenWindowHint(GLFW_WINDOW_NO_RESIZE, GL_TRUE);
	if (!glfwOpenWindow(600,600,0,0,0,0,0,0,GLFW_WINDOW)) {
		printf("Could not open window");
		glfwTerminate();
		exit(EXIT_FAILURE); 
	}
	if (glewInit() != GLEW_OK) {
		printf("Could not initialise GLEW\n");
		exit(EXIT_FAILURE);
	}
	else {
		printf("Initialised GLEW\n");
	}
	if (glewIsSupported("GL_VERSION_3_2"))
		printf("Ready for OpenGL 3.2\n\n");
	else {
		printf("OpenGL 3.2 not supported\n\n");
		exit(EXIT_FAILURE);
	}

	glfwSetKeyCallback(keyHandler);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	/*glEnable(GL_CULL_FACE);
	glCullFace(GL_FRONT);*/

	objectShaderProgram = setupShaders("objshader.vert", "objshader.frag");
	skyboxShaderProgram = setupShaders("objshader.vert", "skyshader.frag");

	Scene scene;
	scene.run();
}