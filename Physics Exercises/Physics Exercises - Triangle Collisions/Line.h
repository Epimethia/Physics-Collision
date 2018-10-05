#pragma once
#include "Dependencies\glew\glew.h"
#include "Dependencies\freeglut\freeglut.h"
#include "Dependencies\glm\glm.hpp"
#include "Dependencies\glm\gtx\string_cast.hpp"

#include <vector>

class Line {
public:
	Line();
	~Line();
	void Init();
	void Render(GLuint _Program);

	void Process();

	void AddPoint(glm::vec2 _Point);

	void ResetPoints() {
		for (int i = 0; i < 12; ++i) {
			verts[i] = 0.0f;
		}
		Points.clear();
		AddPoint(glm::vec2(-300.0f, -300.0f));
		AddPoint(glm::vec2(-300.0f, -300.0f));
		Init();
	};

	std::vector<float> GetPoints() { return Points; };

private:
	GLuint VBO;
	GLuint VAO;

	std::vector<float> Points;
	float verts[12];
};