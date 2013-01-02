#pragma once
#include <vector>

class Face
{
	public:
		Face(void);
		void addVertex(Vertex vertex, Vertex uv, Vertex normal);
		bool isTriangle();
		bool isQuad();
		std::vector<Vertex> get(int i);
};

