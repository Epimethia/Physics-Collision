#pragma once
#include "Dependencies\glew\glew.h"
#include "Dependencies\freeglut\freeglut.h"
#include "Dependencies\glm\glm.hpp"
#include "Dependencies\glm\gtx\string_cast.hpp"

#include <vector>

class Line {
public:
	void Render(GLuint _Program) {
		if (isValid == true) {
			glUseProgram(_Program);
			glBindVertexArray(VAO);
			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			glDrawArrays(GL_LINES, 0, 2);
			glBindVertexArray(0);
		};
	};

	void ResetPoints() {
		Points.clear();
		isValid = false;
	};

	void Process() {
		//if there are the required number of floats to make a tri
		if (Points.size() == 12 && isValid == false) {
			isValid = true;
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
		if (Points.size() <= 12) {
			//adding the three positional points
			Points.push_back(_Point.x);	//x
			Points.push_back(_Point.y);	//y
			Points.push_back(0.0f);							//z

															//adding the color floats (for white)
			Points.push_back(1.0f);	//r
			Points.push_back(1.0f);	//g
			Points.push_back(1.0f);	//b
		}
	};

	std::vector<float> GetPoints() { return Points; };

	bool isValid = false;

private:
	GLuint VBO;
	GLuint VAO;

	std::vector<float> Points;
	float verts[12];
};