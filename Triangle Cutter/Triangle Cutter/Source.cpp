#include "InputManager.h"
#include "ShaderLoader.h"

#include "Capsule.h"
#include "Triangle.h"
#include "Line.h"
#include "Text.h"

#include "Collision Checker.h"

ShaderLoader* SL = new ShaderLoader;
InputManager* IM = new InputManager;
GLuint shaderProgram;

Capsule* cap = new Capsule;
Capsule* cap1 = new Capsule;
Line* l1 = new Line;

Text* t = new Text;

int CurrentPoint = 0;

void Render() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	cap->Render(shaderProgram);
	cap1->Render(shaderProgram);
	l1->Render(shaderProgram);
	glutSwapBuffers();
}

void Update() {
	switch (CurrentPoint) {
		case 0: {
			cap->PointA = glm::vec2(IM->GetMousePos());
			cap->PointB = glm::vec2(IM->GetMousePos());
			cap->PointC = glm::vec2(IM->GetMousePos());
			break;
		}
		case 1: {
			cap->PointB = glm::vec2(IM->GetMousePos());
			cap->PointC = glm::vec2(IM->GetMousePos());
			break;
		}
		case 2: {
			cap->PointC = glm::vec2(IM->GetMousePos());
			break;
		}
		case 3: {
			cap1->PointA = glm::vec2(IM->GetMousePos());
			cap1->PointB = glm::vec2(IM->GetMousePos());
			cap1->PointC = glm::vec2(IM->GetMousePos());
			break;
		}
		case 4: {
			cap1->PointB = glm::vec2(IM->GetMousePos());
			cap1->PointC = glm::vec2(IM->GetMousePos());
			break;
		}
		case 5: {
			cap1->PointC = glm::vec2(IM->GetMousePos());
			break;
		}
		default: break;
	}

	if (CurrentPoint > 5) {
		*l1 = CollisionChecker::CheckCollisions(*cap, *cap1, t);
		l1->Init();
	}

	if (IM->ProcessMouse() == true) {
		CurrentPoint++;
	}

	char Result = IM->ProcessKeys();

	if (Result == 'r') {
		CurrentPoint = 0;
		cap->Reset();
		cap1->Reset();
		l1->ResetPoints();
	}

	cap->Update();
	cap1->Update();
	l1->Process();
	t->Render();
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

	t = new Text("R to Reset", "Dependencies/freetype/arial.ttf", glm::vec2(50.0f, -300.0f), 40);
	t->SetScale(100000.0f);
	cap->Init();
	cap1->Init();
	l1->Init();
}

void exit() {
	delete SL; SL = nullptr;
	delete IM; IM = nullptr;
	shaderProgram = 0;
	delete cap; cap = nullptr;
	delete cap1; cap1 = nullptr;
}


int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutSetOption(GLUT_MULTISAMPLE, 8);
	glEnable(GL_MULTISAMPLE);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA | GLUT_MULTISAMPLE);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(600, 600);
	glutCreateWindow("Capsule Collisions");
	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
	glewInit();
	init();
	glutDisplayFunc(Render);
	glutIdleFunc(Update);
	glutIgnoreKeyRepeat(1);
	glutCloseFunc(exit);
	glutMainLoop();
	return 0;
}

