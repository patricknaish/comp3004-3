#include "Model.h"
#include "Vertex.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>

using namespace std;

string path;
string mtllib;
string name;

vector<Vertex> vertices;
vector<Vertex> textures;
vector<Vertex> normals;

Model::Model(string sourceFile) {
	path = sourceFile;
	mtllib = name = "None";
}

void Model::load() {
	string line, buffer;
	size_t match;
	stringstream stream;
	vector<string> parts;

	ifstream file;

	file.open(path);
	if (file.is_open()) {
		while(file.good()) {
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

			//Vertex
			match = line.find("v", 0);
			if (match != string::npos) {
				line = line.substr(match+2);
				stream = stringstream(line);
				while (stream >> buffer) {
					parts.push_back(buffer);
				}
				double x = atof(parts[0].c_str());
				double y = atof(parts[1].c_str());
				double z = atof(parts[2].c_str());
				vertices.push_back(Vertex(x, y, z));
				continue;
			}

			//Texture
			match = line.find("vt", 0);
			if (match != string::npos) {
				line = line.substr(match+2);
				stream = stringstream(line);
				while (stream >> buffer) {
					parts.push_back(buffer);
				}
				double x = atof(parts[0].c_str());
				double y = atof(parts[1].c_str());
				textures.push_back(Vertex(x, y, 0));
				continue;
			}

			//Normal
			match = line.find("vn", 0);
			if (match != string::npos) {
				line = line.substr(match+2);
				stream = stringstream(line);
				while (stream >> buffer) {
					parts.push_back(buffer);
				}
				double x = atof(parts[0].c_str());
				double y = atof(parts[1].c_str());
				double z = atof(parts[2].c_str());
				normals.push_back(Vertex(x, y, z));
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
				
				continue;
			}
		}
	}
}

void Model::rotate() {
}

void Model::translate() {
}

void Model::scale() {
}

void Model::render() {
}