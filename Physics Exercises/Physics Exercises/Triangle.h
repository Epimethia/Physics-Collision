#pragma once
#include "Dependencies\glew\glew.h"
#include "Dependencies\freeglut\freeglut.h"
#include "Dependencies\glm\glm.hpp"
#include "Dependencies\glm\gtx\string_cast.hpp"

#include <vector>

class Triangle {
public:
	Triangle() {
		PointA = { -300.0f, -300.0f };
		PointB = { -300.0f, -300.0f };
		PointC = { -300.0f, -300.0f };
	}

	~Triangle() {

	}

	void Render(GLuint _Program) {
		glUseProgram(_Program);
		glBindVertexArray(VAO);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glDrawArrays(GL_LINE_LOOP, 0, 3);
		glBindVertexArray(0);
	};

	void ResetPoints() {
		
	};

	void Init() {
		GenerateTriangle();

		//generating and binding the buffers
		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(verts), verts, GL_STATIC_DRAW);
		glBindVertexArray(VAO);

		//Enabling the positional floats
		glVertexAttribPointer(
			0,
			3,
			GL_FLOAT,
			GL_FALSE,
			6 * sizeof(GLfloat),
			(GLvoid*)0
		);
		glEnableVertexAttribArray(0);

		//Enabling Color Floats
		glVertexAttribPointer(
			1,
			3,
			GL_FLOAT,
			GL_FALSE,
			6 * sizeof(GLfloat),
			(GLvoid*)(3 * sizeof(GLfloat))
		);
		glEnableVertexAttribArray(1);

		glBindVertexArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	};

	void Update() {
		GenerateTriangle();
		//Generating and binding the buffers
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(verts), verts, GL_STATIC_DRAW);
		glBindVertexArray(VAO);

		//Enabling the positional floats
		glVertexAttribPointer(
			0,
			3,
			GL_FLOAT,
			GL_FALSE,
			6 * sizeof(GLfloat),
			(GLvoid*)0
		);

		glEnableVertexAttribArray(0);

		//Enabling Color Floats
		glVertexAttribPointer(
			1,
			3,
			GL_FLOAT,
			GL_FALSE,
			6 * sizeof(GLfloat),
			(GLvoid*)(3 * sizeof(GLfloat))
		);
		glEnableVertexAttribArray(1);

		glBindVertexArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	void GenerateTriangle() {
		int CurrentIndex = 0;
		verts[CurrentIndex++] = PointA.x;
		verts[CurrentIndex++] = PointA.y;
		verts[CurrentIndex++] = 0.0f;
		verts[CurrentIndex++] = 1.0f;
		verts[CurrentIndex++] = 1.0f;
		verts[CurrentIndex++] = 1.0f;

		verts[CurrentIndex++] = PointB.x;
		verts[CurrentIndex++] = PointB.y;
		verts[CurrentIndex++] = 0.0f;
		verts[CurrentIndex++] = 1.0f;
		verts[CurrentIndex++] = 1.0f;
		verts[CurrentIndex++] = 1.0f;

		verts[CurrentIndex++] = PointC.x;
		verts[CurrentIndex++] = PointC.y;
		verts[CurrentIndex++] = 0.0f;
		verts[CurrentIndex++] = 1.0f;
		verts[CurrentIndex++] = 1.0f;
		verts[CurrentIndex++] = 1.0f;

	}

	glm::vec2 PointA;
	glm::vec2 PointB;
	glm::vec2 PointC;

private:
	GLuint VBO;
	GLuint VAO;

	float verts[18];
};