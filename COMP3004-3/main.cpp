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

using namespace std; 
using namespace glm;

typedef struct {
	Vertex v[4];
} Face;

GLuint vao[4], vbo[4];
GLchar *vertexsource, *fragmentsource;
GLuint vertexshader, fragmentshader;
GLuint wireframeShaderProgram, normalShaderProgram;

Camera camera = Camera();

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

/*class Sphere: public IModel {
	protected:
		vector<Vertex> sphereVerts, sphereDisplayNormals;
		vector<GLushort> sphereIndices;
		int vboIndex;
		Vertex centre;
		double rad;
	public:
		Sphere(double rad, Vertex centre, int slices, int sectors, int vboIndex) {
			this->vboIndex = vboIndex;
			this->centre = centre;
			this->rad = rad;

			double phi, theta;
			double x, y, z;
			double nx, ny, nz; //Normals

			for (int i = 0; i <= slices; i++) {
				phi = 2*M_PI*((double)i/(double)slices);
				for (int j = 0; j <= sectors; j++) {
					theta = M_PI * ((double)j/(double)sectors);
					x = (double)(rad * sin(theta) * cos(phi)) + centre.x;
					y = (double)(rad * sin(theta) * sin(phi)) + centre.y;
					z = (double)(rad * cos(theta)) + centre.z;
					nx = (x - centre.x)/rad;
					ny = (y - centre.y)/rad;
					nz = (z - centre.z)/rad;
					Vertex vals = {x, y, z, nx, ny, nz};
					sphereVerts.push_back(vals);
					sphereDisplayNormals.push_back(vals);
					vals.x -= centre.x;
					vals.y -= centre.y;
					vals.z -= centre.z;
					vals.x *= 1.1*rad;
					vals.y *= 1.1*rad;
					vals.z *= 1.1*rad;
					vals.x += centre.x;
					vals.y += centre.y;
					vals.z += centre.z;
					sphereDisplayNormals.push_back(vals);
					sphereIndices.push_back(i * sectors + j);
					if ((i+1) * sectors + j+1 < (slices+1) * (sectors+1)) {
						sphereIndices.push_back((i+1) * sectors + j+1);
					}
				}
			}
			
			glBindBuffer(GL_ARRAY_BUFFER, vbo[vboIndex]);
			glBufferData(GL_ARRAY_BUFFER, sphereVerts.size() * sizeof(Vertex), &sphereVerts[0], GL_STATIC_DRAW); 

			glBindVertexArray(vao[vboIndex]); 
			glEnableVertexAttribArray(0);
			glBindBuffer(GL_ARRAY_BUFFER, vbo[vboIndex]);
			glVertexAttribPointer(0, 3, GL_DOUBLE, GL_FALSE, sizeof(Vertex), (const GLvoid*)offsetof(Vertex, x));
		}
		void render() {
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

			glBindVertexArray(vao[vboIndex]);
			glDrawElements(GL_QUAD_STRIP, sphereIndices.size(), GL_UNSIGNED_SHORT, &sphereIndices[0]);
			glBindVertexArray(0);
		}
		void translate(double x, double y, double z) {
			for (size_t i = 0; i < sphereVerts.size(); i++) {
				sphereVerts[i].x += x;
				sphereVerts[i].y += y;
				sphereVerts[i].z += z;
				sphereVerts[i].nx = (sphereVerts[i].x - centre.x)/rad;
				sphereVerts[i].ny = (sphereVerts[i].y - centre.y)/rad;
				sphereVerts[i].nz = (sphereVerts[i].z - centre.z)/rad;
			}
			for (size_t i = 0; i < sphereDisplayNormals.size(); i++) {
				sphereDisplayNormals[i].x += x;
				sphereDisplayNormals[i].y += y;
				sphereDisplayNormals[i].z += z;
			}
			glBindBuffer(GL_ARRAY_BUFFER, vbo[vboIndex]);
			glBufferData(GL_ARRAY_BUFFER, sphereVerts.size() * sizeof(Vertex), &sphereVerts[0], GL_STATIC_DRAW); 

			glBindVertexArray(vao[vboIndex]); 
			glEnableVertexAttribArray(0);
			glBindBuffer(GL_ARRAY_BUFFER, vbo[vboIndex]);
			glVertexAttribPointer(0, 3, GL_DOUBLE, GL_FALSE, sizeof(Vertex), (const GLvoid*)offsetof(Vertex, x));
		}
};
*/

/*class SceneA: public IScene {
	private:
		int running;	
	public:
		SceneA() {}
		void run() {
			glUseProgram(wireframeShaderProgram);

			Vertex centre = {0,0,0};

			Sphere sphere = Sphere(1, centre, 30, 30, 0);

			mat4 Projection = perspective(45.0f, 1.0f, 0.1f, 100.0f);
			mat4 View = lookAt(vec3(0,2,1), vec3(0,0,0), vec3(0,1,0));
			View = scale(View, vec3(0.7f));
			mat4 Model = mat4(1.0f);
			mat4 MVP;
			GLuint MatrixID = glGetUniformLocation(wireframeShaderProgram, "MVP");

			//Running stuff
			running = GL_TRUE;
			double old_time = 0, current_time = 0;
			ostringstream title;
			float rotation = 0.f;
			while( running ) { 
				current_time = glfwGetTime();
				rotation = (float)((current_time - old_time) * speed);
				if (rotation >= 360.f) {
					rotation = 0.f;
				}
				old_time = current_time;
				
				View = rotate(View, rotation, vec3(1, 1, 1));
				MVP = Projection * View * Model;
				glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP[0][0]);
		
				glClearColor(0,0,0,0);
				glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
				sphere.render();
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
*/

void GLFWCALL keyHandler(int key, int action) {
	if (action == GLFW_PRESS) {
		if (key == GLFW_KEY_ESC || key == 'Q' || key == 'q') {
			glfwTerminate();
			exit(EXIT_SUCCESS);
		}
		switch(key) {
			case GLFW_KEY_UP: camera.increaseVelocity(); break;
			case GLFW_KEY_DOWN: camera.decreaseVelocity(); break;
			case GLFW_KEY_RIGHT: camera.turnRight(); break;
			case GLFW_KEY_LEFT: camera.turnLeft(); break;
			case GLFW_KEY_PAGEUP: camera.increaseElevation(); break;
			case GLFW_KEY_PAGEDOWN: camera.decreaseElevation(); break;
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
		printf("OpenGL 4.2 not supported\n\n");
		exit(EXIT_FAILURE);
	}

	glfwSetKeyCallback(keyHandler);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	glGenBuffers(4, vbo);
	glGenVertexArrays(4, vao);
	if (glGetError() != 0) {
		printf("Could not create vbos or vaos\n");
		exit(EXIT_FAILURE);
	}
	else {
		printf("Generated vbos and vaos\n\n");
	}

	//wireframeShaderProgram = setupShaders("wireshader.vert", "wireshader.frag");
	//normalShaderProgram = setupShaders("normshader.vert", "normshader.frag");
}