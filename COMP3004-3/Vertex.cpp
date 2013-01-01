#include "Vertex.h"

double _x, _y, _z;

Vertex::Vertex(double x, double y, double z) {
	_x = x;
	_y = y;
	_z = z;
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