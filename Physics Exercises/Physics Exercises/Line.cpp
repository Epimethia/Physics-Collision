#include "Line.h"

Line::Line() {

}

Line::~Line() {
	for (int i = 0; i < 12; ++i) {
		verts[i] = 0.0f;
	}
	Points.clear();
}

void Line::Init() {
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

void Line::Render(GLuint _Program) {
	glUseProgram(_Program);
	glBindVertexArray(VAO);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDrawArrays(GL_LINES, 0, 2);
	glBindVertexArray(0);
}

void Line::Process() {
	
}

void Line::AddPoint(glm::vec2 _Point, glm::vec3 _Color) {
	if (Points.size() <= 12) {
		//adding the three positional points
		Points.push_back(_Point.x);	//x
		Points.push_back(_Point.y);	//y
		Points.push_back(0.0f);							//z
														//adding the color floats (for white)
		Points.push_back(_Color.x);	//r
		Points.push_back(_Color.y);	//g
		Points.push_back(_Color.z);	//b
	}
}

