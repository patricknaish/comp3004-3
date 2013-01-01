#include "Face.h"

using namespace std;

typedef struct {
	Vertex vertex;
	Vertex uv;
	Vertex normal;
} FaceVertex;

vector<FaceVertex> vertices;

Face::Face(void) {

}

void Face::addVertex(Vertex vertex, Vertex uv, Vertex normal) {
	FaceVertex fv = {vertex, uv, normal};
	vertices.push_back(fv);
}

bool Face::isTriangle() {
	return (vertices.size() == 3);
}

bool Face::isQuad() {
	return (vertices.size() == 4);
}

vector<Vertex> Face::get(int i) {
	vector<Vertex> result = vector<Vertex>();
	result.push_back(vertices[i].vertex);
	result.push_back(vertices[i].uv);
	result.push_back(vertices[i].normal);
	return result;
}