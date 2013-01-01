#include "Vertex.h"

double _x, _y, _z;
double _nx, _ny, _nz;

Vertex::Vertex(double x, double y, double z) {
	_x = x;
	_y = y;
	_z = z;
}

void Vertex::addNormal(double nx, double ny, double nz) {
	_nx = nx;
	_ny = ny;
	_nz = nz;
}

double Vertex::x() {
	return _x;
}

double Vertex::y() {
	return _y;
}

double Vertex::z() {
	return _z;
}

double Vertex::nx() {
	return _x;
}

double Vertex::ny() {
	return _y;
}

double Vertex::nz() {
	return _z;
}