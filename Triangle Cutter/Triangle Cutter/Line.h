#pragma once
#include "Dependencies\glew\glew.h"
#include "Dependencies\freeglut\freeglut.h"
#include "Dependencies\glm\glm.hpp"
#include "Dependencies\glm\gtx\string_cast.hpp"

#include <vector>

class Line {
public:
	Line();
	void Init();
	void Render(GLuint _Program);

	void Process();

	void AddPoint(glm::vec2 _Point);

	void ResetPoints() {
		Points.clear();
		for (int i = 0; i < 12; ++i) {
			verts[i] = 0.0f;
		}
	};

	std::vector<float> GetPoints() { return Points; };

private:
	GLuint VBO;
	GLuint VAO;

	std::vector<float> Points;
	float verts[12];
};