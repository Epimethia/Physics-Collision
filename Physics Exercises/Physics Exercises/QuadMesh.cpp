#include "QuadMesh.h"

QuadMesh::QuadMesh(){}

QuadMesh::~QuadMesh(){}

void QuadMesh::Init(){
	const GLuint gridSize = 5;
	GLfloat spacing = 1.0f / gridSize;
	GLfloat PlaneVerts[gridSize * (gridSize * 6)];
	int i = 0;
	for (int row = 0; row<gridSize; row++){
		for (int col = 0; col<gridSize; col++){
			PlaneVerts[i++] = (float) col * 100.0f;
			PlaneVerts[i++] = (float) row * 100.0f;
			PlaneVerts[i++] = 0.0f;

			PlaneVerts[i++] = 1.0f;
			PlaneVerts[i++] = 1.0f;
			PlaneVerts[i++] = 1.0f;
		}
	}
	//const int numinds = gridSize * gridSize * 6;
	GLuint PlaneIndices[gridSize * gridSize * 6];
	// Iterate over each quad and compute indices.
	int k = 0;
	for (UINT i = 0; i < gridSize - 1; ++i){
		for (UINT j = 0; j < gridSize - 1; ++j){
			PlaneIndices[k] = i * gridSize + j;
			PlaneIndices[k + 1] = i * gridSize + j + 1;
			PlaneIndices[k + 2] = (i + 1)*gridSize + j;

			PlaneIndices[k + 3] = (i + 1)*gridSize + j;
			PlaneIndices[k + 4] = i * gridSize + j + 1;
			PlaneIndices[k + 5] = (i + 1)*gridSize + j + 1;

			k += 6; // next quad
		}
	}
	NumIndices = sizeof(PlaneIndices);

	//Generating buffers
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);

	//Binding and setting buffer data
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(PlaneVerts), PlaneVerts, GL_STATIC_DRAW);

	//Generating EBO
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(PlaneIndices), PlaneIndices, GL_STATIC_DRAW);

	//Enabling the positional floats
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat),
		(GLvoid*) 0);
	glEnableVertexAttribArray(0);


	//Enabling Color Floats
	glVertexAttribPointer(
		1,
		3,
		GL_FLOAT,
		GL_FALSE,
		6 * sizeof(GLfloat),
		(GLvoid*) (3 * sizeof(GLfloat))
	);
	glEnableVertexAttribArray(1);

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void QuadMesh::Render(GLuint _Program){
	glUseProgram(_Program);
	glBindVertexArray(VAO);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glDrawElements(GL_TRIANGLES, NumIndices, GL_UNSIGNED_INT, 0);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glBindVertexArray(0);
	return;
}
