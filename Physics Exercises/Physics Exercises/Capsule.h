#pragma once
#include "Dependencies\glew\glew.h"
#include "Dependencies\freeglut\freeglut.h"
#include "Dependencies\glm\glm.hpp"

//#include "Dependencies\Visual Leak Detector\include\vld.h"


class Capsule {
public:
	Capsule();
	void Render(GLuint _Program);;
	void Init();
	void Update();
	void GenerateCapsule();
	void Reset();

	glm::vec2 PointA = { -300.0f, -300.0f };
	glm::vec2 PointB = { -300.0f, -300.0f };
	glm::vec2 PointC = { -300.0f, -300.0f };

	float radius;

private:
	GLuint VAO;
	GLuint VBO;

	float verts[216];
};