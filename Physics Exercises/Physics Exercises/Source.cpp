#include "InputManager.h"
#include "ShaderLoader.h"

#include "Capsule.h"
#include "Triangle.h"
#include "Line.h"

#include "Collision Checker.h"

ShaderLoader* SL = new ShaderLoader;
InputManager* IM = new InputManager;
GLuint shaderProgram;

Triangle* Triangle0 = new Triangle;
glm::vec2 Point0;
Line* l0 = new Line;
Line* l1 = new Line;
Line* l2 = new Line;


int CurrentPoint = 0;

void Render() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	Triangle0->Render(shaderProgram);
	l0->Render(shaderProgram);
	l1->Render(shaderProgram);
	l2->Render(shaderProgram);
	glutSwapBuffers();
}

void Update() {
	switch (CurrentPoint) {
		case 0: {
			Triangle0->PointA = IM->GetMousePos();
			Triangle0->PointB = IM->GetMousePos();
			Triangle0->PointC = IM->GetMousePos();
			break;
		}
		case 1: {
			Triangle0->PointB = IM->GetMousePos();
			Triangle0->PointC = IM->GetMousePos();
			break;
		}
		case 2: {
			Triangle0->PointC = IM->GetMousePos();
			break;
		}
		case 4: {
			Point0 = IM->GetMousePos();
			if (CollisionChecker::CheckCollisions(Point0, *Triangle0)) {
				delete l0; l0 = new Line;
				l0->AddPoint(Point0, glm::vec3(0.0f, 1.0f, 0.0f)); l0->AddPoint(Triangle0->PointA, glm::vec3(0.0f, 1.0f, 0.0f));
				l0->Init();
				delete l1; l1 = new Line;

				l1->AddPoint(Point0, glm::vec3(0.0f, 1.0f, 0.0f)); l1->AddPoint(Triangle0->PointB, glm::vec3(0.0f, 1.0f, 0.0f));
				l1->Init();
				delete l2; l2 = new Line;

				l2->AddPoint(Point0, glm::vec3(0.0f, 1.0f, 0.0f)); l2->AddPoint(Triangle0->PointC, glm::vec3(0.0f, 1.0f, 0.0f));
				l2->Init();
			}
			else {
				delete l0; l0 = new Line;
				l0->AddPoint(Point0, glm::vec3(1.0f, 0.0f, 0.0f)); l0->AddPoint(Triangle0->PointA, glm::vec3(1.0f, 0.0f, 0.0f));
				l0->Init();
				delete l1; l1 = new Line;

				l1->AddPoint(Point0, glm::vec3(1.0f, 0.0f, 0.0f)); l1->AddPoint(Triangle0->PointB, glm::vec3(1.0f, 0.0f, 0.0f));
				l1->Init();
				delete l2; l2 = new Line;

				l2->AddPoint(Point0, glm::vec3(1.0f, 0.0f, 0.0f)); l2->AddPoint(Triangle0->PointC, glm::vec3(1.0f, 0.0f, 0.0f));
				l2->Init();
			}
			
			CurrentPoint++;
			break;
		}
		default: break;
	}

	if (IM->ProcessMouse() == true) {
		CurrentPoint++;
	}

	char Result = IM->ProcessKeys();

	if (Result == 'r') {
		CurrentPoint = 0;
		delete l0; l0 = new Line;
		delete l1; l1 = new Line;
		delete l2; l2 = new Line;
	}
	Triangle0->Update();
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
	Triangle0->Init();
	l0->Init();
	l1->Init();
	l2->Init();
}

void exit() {
	delete SL; SL = nullptr;
	delete IM; IM = nullptr;
	shaderProgram = 0;
	delete Triangle0; Triangle0 = nullptr;
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

