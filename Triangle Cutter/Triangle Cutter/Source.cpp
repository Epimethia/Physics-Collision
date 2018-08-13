#include "InputManager.h"
#include "ShaderLoader.h"

#include "Triangle.h"
#include "Line.h"

ShaderLoader* SL = new ShaderLoader;
InputManager* IM = new InputManager;
GLuint shaderProgram;
glm::vec2 TrianglePoints[3];
int CurrentPoint = 0;

Triangle* tri0 = new Triangle;
Line* line = new Line;

//the three resulting triangles
Triangle* tri1 = new Triangle;
Triangle* tri2 = new Triangle;
Triangle* tri3 = new Triangle;


void Render() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	tri0->Render(shaderProgram);
	line->Render(shaderProgram);
	glutSwapBuffers();
}

void Update() {
	char Result = IM->ProcessKeys();
	if (Result == 't') {
		std::cout << "Resetting triangle\n";
		tri0->ResetPoints();
		line->ResetPoints();
		CurrentPoint = 0;
	}
	else if (Result == 'l') {
		std::cout << "Resetting line\n";
		line->ResetPoints();
		CurrentPoint = 3;
	}

	//if the input is valid
	if (IM->ProcessMouse() == true) {
		//drawing the triangle
		if (CurrentPoint < 3) {
			tri0->AddPoint(IM->GetMousePos());
			CurrentPoint++;
		}

		//drawing the line
		else if (CurrentPoint < 6) {
			line->AddPoint(IM->GetMousePos());
			CurrentPoint++;
		};
	}
	tri0->Process();
	line->Process();
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
	glutMainLoop();
	glutExit();
	return 0;
}

