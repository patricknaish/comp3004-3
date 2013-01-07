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

class Scene {
	private:
		int running;	
	public:
		Scene() {};
		void run();
};

GLchar *vertexsource, *fragmentsource;
GLuint vertexshader, fragmentshader;
GLuint objectShaderProgram, skyboxShaderProgram;

Camera camera = Camera();

Scene scene = Scene();

bool increasingVelocity = false;
bool decreasingVelocity = false;
bool rotatingLeft = false;
bool rotatingRight = false;
bool rotatingUp = false;
bool rotatingDown = false;

const float speed = 10;

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

void Scene::run() {

	Model skybox1("models/skybox1.obj");
	skybox1.load();
	skybox1.loadTexture("textures/sky512.tga");

	Model skybox2("models/skybox2.obj");
	skybox2.load();
	skybox2.loadTexture("textures/skyempty512.tga");

	Model skybox3("models/skybox3.obj");
	skybox3.load();
	skybox3.loadTexture("textures/skyempty512.tga");

	Model skybox4("models/skybox4.obj");
	skybox4.load();
	skybox4.loadTexture("textures/skyempty512.tga");

	Model ceiling1("models/ceiling1.obj");
	ceiling1.load();
	ceiling1.loadTexture("textures/ceiling.tga");

	Model beacon1("models/beacon1.obj");
	beacon1.load();
	beacon1.loadTexture("textures/beacon.tga");

	Model beacon2("models/beacon2.obj");
	beacon2.load();
	beacon2.loadTexture("textures/beacon.tga");

	Model beacon3("models/beacon3.obj");
	beacon3.load();
	beacon3.loadTexture("textures/beacon.tga");

	Model beacon4("models/beacon4.obj");
	beacon4.load();
	beacon4.loadTexture("textures/beacon.tga");

	Model beam1("models/beam1.obj");
	beam1.load();
	beam1.loadTexture("textures/strut.tga");

	Model beam2("models/beam2.obj");
	beam2.load();
	beam2.loadTexture("textures/strut.tga");

	Model dome1("models/dome1.obj");
	dome1.load();
	dome1.loadTexture("textures/dome.tga");

	Model dome2("models/dome2.obj");
	dome2.load();
	dome2.loadTexture("textures/dome.tga");

	Model dome3("models/dome3.obj");
	dome3.load();
	dome3.loadTexture("textures/dome.tga");

	Model panelsupport1("models/panelsupport1.obj");
	panelsupport1.load();
	panelsupport1.loadTexture("textures/strut.tga");

	Model panelsupport2("models/panelsupport2.obj");
	panelsupport2.load();
	panelsupport2.loadTexture("textures/strut.tga");

	Model solarpanel1("models/solarpanel1.obj");
	solarpanel1.load();
	solarpanel1.loadTexture("textures/sunbattery.tga");

	Model solarpanel2("models/solarpanel2.obj");
	solarpanel2.load();
	solarpanel2.loadTexture("textures/sunbattery.tga");

	Model strut1("models/strut1.obj");
	strut1.load();
	strut1.loadTexture("textures/strut.tga");

	Model strut2("models/strut2.obj");
	strut2.load();
	strut2.loadTexture("textures/strut.tga");

	Model strut3("models/strut3.obj");
	strut3.load();
	strut3.loadTexture("textures/strut.tga");

	Model strut4("models/strut4.obj");
	strut4.load();
	strut4.loadTexture("textures/strut.tga");

	Model walkway1("models/walkway1.obj");
	walkway1.load();
	walkway1.loadTexture("textures/sunbattery.tga");

	Model walkway2("models/walkway2.obj");
	walkway2.load();
	walkway2.loadTexture("textures/sunbattery.tga");

	Model landscape("models/landscape.obj");
	landscape.load();
	landscape.loadTexture("textures/mars.tga");

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
	double old_time = 0, current_time = 0, time_diff = 0;
	ostringstream title;
	float rate = 0.f;
	while( running ) { 
		current_time = glfwGetTime();
		time_diff = current_time-old_time;
		rate = (float)(time_diff * speed);
		old_time = current_time;
		if (increasingVelocity) {
			camera.increaseVelocity(time_diff);
		}
		if (decreasingVelocity) {
			camera.decreaseVelocity(time_diff);
		}
		camera.move(time_diff);
		if (rotatingLeft) {
			camera.turnLeft(time_diff);
		}
		if (rotatingRight) {
			camera.turnRight(time_diff);
		}
		if (rotatingUp) {
			camera.increaseElevation(time_diff/2);
		}
		if (rotatingDown) {
			camera.decreaseElevation(time_diff/2);
		}
		/*landscape->rotate(rate, vec3(0,1,0));
		dome->rotate(rate, vec3(0,1,0));
		skybox->rotate(rate, vec3(0,1,0));*/
		glClearColor(0,0,0,0);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glUseProgram(skyboxShaderProgram);
		mat4 MVP = camera.getMVP(skybox1.getMatrix());
		glUniformMatrix4fv(SkyboxMatrixID, 1, GL_FALSE, &MVP[0][0]);
		skybox1.render();

		MVP = camera.getMVP(skybox2.getMatrix());
		glUniformMatrix4fv(SkyboxMatrixID, 1, GL_FALSE, &MVP[0][0]);
		skybox2.render();

		MVP = camera.getMVP(skybox3.getMatrix());
		glUniformMatrix4fv(SkyboxMatrixID, 1, GL_FALSE, &MVP[0][0]);
		skybox3.render();

		MVP = camera.getMVP(skybox4.getMatrix());
		glUniformMatrix4fv(SkyboxMatrixID, 1, GL_FALSE, &MVP[0][0]);
		skybox4.render();

		MVP = camera.getMVP(ceiling1.getMatrix());
		glUniformMatrix4fv(SkyboxMatrixID, 1, GL_FALSE, &MVP[0][0]);
		ceiling1.render();

		glUseProgram(objectShaderProgram);
		MVP = camera.getMVP(landscape.getMatrix());
		glUniformMatrix4fv(ObjectMatrixID, 1, GL_FALSE, &MVP[0][0]);
		landscape.render();
				
		MVP = camera.getMVP(beacon1.getMatrix());
		glUniformMatrix4fv(ObjectMatrixID, 1, GL_FALSE, &MVP[0][0]);
		beacon1.render();

		MVP = camera.getMVP(beacon2.getMatrix());
		glUniformMatrix4fv(ObjectMatrixID, 1, GL_FALSE, &MVP[0][0]);
		beacon2.render();

		MVP = camera.getMVP(beacon3.getMatrix());
		glUniformMatrix4fv(ObjectMatrixID, 1, GL_FALSE, &MVP[0][0]);
		beacon3.render();

		MVP = camera.getMVP(beacon4.getMatrix());
		glUniformMatrix4fv(ObjectMatrixID, 1, GL_FALSE, &MVP[0][0]);
		beacon4.render();

		MVP = camera.getMVP(beam1.getMatrix());
		glUniformMatrix4fv(ObjectMatrixID, 1, GL_FALSE, &MVP[0][0]);
		beam1.render();

		MVP = camera.getMVP(beam2.getMatrix());
		glUniformMatrix4fv(ObjectMatrixID, 1, GL_FALSE, &MVP[0][0]);
		beam2.render();

		MVP = camera.getMVP(dome1.getMatrix());
		glUniformMatrix4fv(ObjectMatrixID, 1, GL_FALSE, &MVP[0][0]);
		dome1.render();

		MVP = camera.getMVP(dome2.getMatrix());
		glUniformMatrix4fv(ObjectMatrixID, 1, GL_FALSE, &MVP[0][0]);
		dome2.render();

		MVP = camera.getMVP(dome3.getMatrix());
		glUniformMatrix4fv(ObjectMatrixID, 1, GL_FALSE, &MVP[0][0]);
		dome3.render();

		MVP = camera.getMVP(panelsupport1.getMatrix());
		glUniformMatrix4fv(ObjectMatrixID, 1, GL_FALSE, &MVP[0][0]);
		panelsupport1.render();

		MVP = camera.getMVP(panelsupport2.getMatrix());
		glUniformMatrix4fv(ObjectMatrixID, 1, GL_FALSE, &MVP[0][0]);
		panelsupport2.render();

		MVP = camera.getMVP(solarpanel1.getMatrix());
		glUniformMatrix4fv(ObjectMatrixID, 1, GL_FALSE, &MVP[0][0]);
		solarpanel1.render();

		MVP = camera.getMVP(solarpanel2.getMatrix());
		glUniformMatrix4fv(ObjectMatrixID, 1, GL_FALSE, &MVP[0][0]);
		solarpanel2.render();

		MVP = camera.getMVP(strut1.getMatrix());
		glUniformMatrix4fv(ObjectMatrixID, 1, GL_FALSE, &MVP[0][0]);
		strut1.render();

		MVP = camera.getMVP(strut2.getMatrix());
		glUniformMatrix4fv(ObjectMatrixID, 1, GL_FALSE, &MVP[0][0]);
		strut2.render();

		MVP = camera.getMVP(strut3.getMatrix());
		glUniformMatrix4fv(ObjectMatrixID, 1, GL_FALSE, &MVP[0][0]);
		strut3.render();

		MVP = camera.getMVP(strut4.getMatrix());
		glUniformMatrix4fv(ObjectMatrixID, 1, GL_FALSE, &MVP[0][0]);
		strut4.render();

		MVP = camera.getMVP(walkway1.getMatrix());
		glUniformMatrix4fv(ObjectMatrixID, 1, GL_FALSE, &MVP[0][0]);
		walkway1.render();

		MVP = camera.getMVP(walkway2.getMatrix());
		glUniformMatrix4fv(ObjectMatrixID, 1, GL_FALSE, &MVP[0][0]);
		walkway2.render();

		glFlush();
		glfwSwapBuffers();
		if (!glfwGetWindowParam(GLFW_OPENED)) {
			running = GL_FALSE;
		}
	}
}

void GLFWCALL keyHandler(int key, int action) {
	if (action == GLFW_PRESS) {
		if (key == GLFW_KEY_ESC || key == 'Q' || key == 'q') {
			glfwTerminate();
			exit(EXIT_SUCCESS);
		}
		switch(key) {
			case GLFW_KEY_UP: increasingVelocity = true; break;
			case GLFW_KEY_DOWN: decreasingVelocity = true; break;
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
			case GLFW_KEY_UP: increasingVelocity = false; break;
			case GLFW_KEY_DOWN: decreasingVelocity = false; break;
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

	scene.run();
}