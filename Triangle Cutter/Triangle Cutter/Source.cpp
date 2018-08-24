#include "InputManager.h"
#include "ShaderLoader.h"

#include "Capsule.h"
#include "Triangle.h"
#include "Line.h"

ShaderLoader* SL = new ShaderLoader;
InputManager* IM = new InputManager;
GLuint shaderProgram;

Capsule* cap = new Capsule;
Capsule* cap1 = new Capsule;

int CurrentPoint = 0;

void Render() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	cap->Render(shaderProgram);
	cap1->Render(shaderProgram);
	glutSwapBuffers();
}

void Update() {

	if (CurrentPoint == 1) {
		cap->PointB = glm::vec2(IM->GetMousePos());
		cap->PointC = glm::vec2(IM->GetMousePos());
	}

	else if (CurrentPoint == 0) {
		cap->PointA = glm::vec2(IM->GetMousePos());
		cap->PointB = glm::vec2(IM->GetMousePos());
		cap->PointC = glm::vec2(IM->GetMousePos());
	}
	else if (CurrentPoint == 2) {
		cap->PointC = glm::vec2(IM->GetMousePos());
	}

	if (CurrentPoint == 4) {
		cap1->PointB = glm::vec2(IM->GetMousePos());
		cap1->PointC = glm::vec2(IM->GetMousePos());
	}

	else if (CurrentPoint == 3) {
		cap1->PointA = glm::vec2(IM->GetMousePos());
		cap1->PointB = glm::vec2(IM->GetMousePos());
		cap1->PointC = glm::vec2(IM->GetMousePos());
	}
	else if (CurrentPoint == 5) {
		cap1->PointC = glm::vec2(IM->GetMousePos());
	}

	if (IM->ProcessMouse() == true) {
		CurrentPoint++;
	}

	char Result = IM->ProcessKeys();
	if (Result == 'r') {
		std::cout << "r\n";
		CurrentPoint = 0;
		cap->Reset();
		cap1->Reset();
	}


	cap->Update();
	cap1->Update();
	glutPostRedisplay();
}

void init() {
	glEnable(GL_DEPTH_TEST);
	glFrontFace(GL_CCW);
	glLineWidth(3.0f);
	//Creating the shaders
	shaderProgram = SL->CreateProgram(
		const_cast<char*>("Dependencies/shaders/Vertex Shader.vs"),
		const_cast<char*>("Dependencies/shaders/Fragment Shader.fs")
	);	

	cap->Init();
	cap1->Init();
}

void exit() {
	delete SL; SL = nullptr;
	delete IM; IM = nullptr;
	shaderProgram = 0;
	delete cap; cap = nullptr;
}


int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutSetOption(GLUT_MULTISAMPLE, 8);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA | GLUT_MULTISAMPLE);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(600, 600);
	glutCreateWindow("OpenGL First Window");
	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
	glEnable(GL_MULTISAMPLE);
	glewInit();
	init();
	glutDisplayFunc(Render);
	glutIdleFunc(Update);
	glutIgnoreKeyRepeat(1);
	glutCloseFunc(exit);
	glutMainLoop();
	return 0;
}

