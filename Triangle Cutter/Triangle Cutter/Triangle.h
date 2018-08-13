#pragma once
#include "Dependencies\glew\glew.h"
#include "Dependencies\freeglut\freeglut.h"
#include "Dependencies\glm\glm.hpp"
#include "Dependencies\glm\gtx\string_cast.hpp"

#include <vector>

class Triangle {
public:
	void Render(GLuint _Program) {
		if (canRender == true) {
			glUseProgram(_Program);
			glBindVertexArray(VAO);
			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			glDrawArrays(GL_LINE_LOOP, 0, 3);
			glBindVertexArray(0);
		};
	};

	void ResetPoints() {
		Points.clear();
		canRender = false;
	};

	void Process() {
		//if there are the required number of floats to make a tri
		if (Points.size() == 18 && canRender == false) {
			canRender = true;
			std::copy(Points.begin(), Points.end(), verts);

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

		}
	};

	void AddPoint(glm::vec2 _Point) {
		if (Points.size() <= 18) {
			//adding the three positional points
			Points.push_back((_Point.x / 300.0f) - 1.0f);	//x
			Points.push_back(((_Point.y / 300.0f) - 1.0f) * -1.0f);	//y
			Points.push_back(0.0f);							//z

			//adding the color floats (for white)
			Points.push_back(1.0f);	//r
			Points.push_back(1.0f);	//g
			Points.push_back(1.0f);	//b
		}
	};

private:
	GLuint VBO;
	GLuint VAO;

	std::vector<float> Points;
	float verts[18];
	bool canRender = false;
};