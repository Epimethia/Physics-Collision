#pragma once
#include "Dependencies\glew\glew.h"
#include "Dependencies\freeglut\freeglut.h"
#include "Dependencies\glm\glm.hpp"

class QuadMesh{
public:
	QuadMesh();
	~QuadMesh();

	void Init();
	void Render(GLuint _Program);

private:
	GLuint VAO, VBO, EBO;
	int NumIndices;
};