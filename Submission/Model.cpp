#include "Model.h"

using namespace std;
using namespace glm;

Model::Model(string sourceFile) {
	path = sourceFile;
	mtllib = name = "None";
	isTriangles = isQuads = false;
}

void Model::load(void) {
	string line, buffer;
	size_t match;
	stringstream stream;
	vector<string> parts;

	int lineIndex = 1;

	ifstream file;

	file.open(path);
	if (file.is_open()) {

		vector<vec3> tempvertices;
		vector<vec2> temptextures;
		vector<vec3> tempnormals;

		vector<int> vertexIndices;
		vector<int> uvIndices;
		vector<int> normalIndices;

		int vertIndex, uvIndex, normIndex;
		float x, y, z;

		cout << "Loading " << path << "... \r";

		while(file.good()) {

			lineIndex++;

			parts.clear();
			
			getline(file, line);

			//Comment lines
			match = line.find('#', 0);
			if (match != string::npos) {
				continue;
			}

			//Material library
			match = line.find("mtllib", 0);
			if (match != string::npos) {
				mtllib = line.substr(match+7);
				continue;
			}

			//Object
			match = line.find("o", 0);
			if (match != string::npos) {
				name = line.substr(match+2);
				continue;
			}

			//Face
			match = line.find("f", 0);
			if (match != string::npos) {
				line = line.substr(match+2);
				stream = stringstream(line);
				while (stream >> buffer) {
					parts.push_back(buffer);
				}
				for (int i = 0; i < parts.size(); i++) {
					sscanf(parts[i].c_str(), "%d/%d/%d", &vertIndex, &uvIndex, &normIndex);
					vertexIndices.push_back(vertIndex);
					uvIndices.push_back(uvIndex);
					normalIndices.push_back(normIndex);
				}
				if (parts.size() == 3) {
					isTriangles = true;
				}
				else if (parts.size() == 4) {
					isQuads = true;
				}
				continue;
			}

			//Texture
			match = line.find("vt", 0);
			if (match != string::npos) {
				line = line.substr(match+2);
				sscanf(line.c_str(), "%f %f", &x, &y);
				temptextures.push_back(vec2(x, y));
				continue;
			}

			//Normal
			match = line.find("vn", 0);
			if (match != string::npos) {
				line = line.substr(match+2);
				sscanf(line.c_str(), "%f %f %f", &x, &y, &z);
				tempnormals.push_back(vec3(x, y, z));
				continue;
			}

			//Vertex
			match = line.find("v", 0);
			if (match != string::npos) {
				line = line.substr(match+2);
				sscanf(line.c_str(), "%f %f %f", &x, &y, &z);
				tempvertices.push_back(vec3(x, y, z));
				continue;
			}
			
		}

		vec3 vertex, normal;
		vec2 uv;
		for (int i = 0; i < vertexIndices.size(); i++) {
			vertIndex = vertexIndices[i];
			vertex = tempvertices[vertIndex-1];
			vertices.push_back(vertex);
		}
		for (int i = 0; i < uvIndices.size(); i++) {
			uvIndex = uvIndices[i];
			uv = temptextures[uvIndex-1];
			textures.push_back(uv);
		}
		for (int i = 0; i < normalIndices.size(); i++) {
			normIndex = normalIndices[i];
			normal = tempnormals[normIndex-1];
			normals.push_back(normal);
		}

		glGenBuffers(3, vbo);
		glGenVertexArrays(1, vao);

		glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
		glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(vec3), &vertices[0], GL_STATIC_DRAW); 
		glBindVertexArray(vao[0]); 
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vec3), (const GLvoid*)0);

		glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
		glBufferData(GL_ARRAY_BUFFER, textures.size() * sizeof(vec2), &textures[0], GL_STATIC_DRAW); 
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(vec2), (const GLvoid*)0);

		glBindBuffer(GL_ARRAY_BUFFER, vbo[2]);
		glBufferData(GL_ARRAY_BUFFER, normals.size() * sizeof(vec3), &normals[0], GL_STATIC_DRAW); 
		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(vec3), (const GLvoid*)0);

		cout << "Loaded " << path << " [" << lineIndex << "]" << endl;

		return;
	}

	cout << "Could not load " << path << endl;
}

GLuint Model::loadTexture(string texPath) {
	glEnable(GL_TEXTURE_2D);
	glGenTextures(1, textureID);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, textureID[0]);
	glfwLoadTexture2D(texPath.c_str(), 0);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glGenerateMipmap(GL_TEXTURE_2D);
	return textureID[0];
}

void Model::rotate(float rotation, vec3 axes) {
	model = glm::rotate(model, rotation, axes);
}

void Model::translate(vec3 translations) {
	model = glm::translate(model, translations);
}

void Model::scale(vec3 scales) {
	model = glm::scale(model, scales);
}

void Model::render(void) {
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glBindTexture(GL_TEXTURE_2D, textureID[0]);
	glBindVertexArray(vao[0]);
	glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
	if (isTriangles) {
		glDrawArrays(GL_TRIANGLES, 0, vertices.size());
	}
	if (isQuads) {
		glDrawArrays(GL_QUADS, 0, vertices.size());
	}
}

void Model::setMatrix(mat4 newMatrix) {
	model = newMatrix;
}

mat4 Model::getMatrix(void) {
	return model;
}