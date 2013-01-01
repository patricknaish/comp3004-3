#pragma once

class Vertex {
	public:
		Vertex(double x, double y, double z);
		void addNormal(double nx, double ny, double nz);
		double x();
		double y();
		double z();
		double nx();
		double ny();
		double nz();
};

