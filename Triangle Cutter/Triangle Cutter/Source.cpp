#include "InputManager.h"
#include "ShaderLoader.h"

#include "Triangle.h"
#include "Line.h"

ShaderLoader* SL = new ShaderLoader;
InputManager* IM = new InputManager;
GLuint shaderProgram;
int CurrentPoint = 0;

Triangle* tri0 = new Triangle;
Line* line0 = new Line;

//the three resulting triangles
Triangle* tri1 = new Triangle;
Triangle* tri2 = new Triangle;
Triangle* tri3 = new Triangle;


void GenerateResultingTris(Line _line, Triangle _tri) {
	glm::vec3 LinePoint_0 = glm::vec3(_line.GetPoints()[0], _line.GetPoints()[1], 0.0f);
	glm::vec3 LinePoint_1 = glm::vec3(_line.GetPoints()[6], _line.GetPoints()[7], 0.0f);

	//getting triangle points
	glm::vec3 TriPoint_0 = glm::vec3(_tri.GetPoints()[0], _tri.GetPoints()[1], 0.0f);
	glm::vec3 TriPoint_1 = glm::vec3(_tri.GetPoints()[6], _tri.GetPoints()[7], 0.0f);
	glm::vec3 TriPoint_2 = glm::vec3(_tri.GetPoints()[12], _tri.GetPoints()[13], 0.0f);

	//t = ((q - p) cross s) / r cross s
	//Line with side tripoint_0 -> tripoint_1
	glm::vec3 r = (LinePoint_0 - LinePoint_1);
	glm::vec3 s0 = (TriPoint_0 - TriPoint_1);
	float a = (glm::cross((LinePoint_0 - TriPoint_0), r) / glm::cross(r, s0)).z;

	//Line with side tripoint_1 -> tripoint_2
	glm::vec3 s1 = (TriPoint_1 - TriPoint_2);
	float b = (glm::cross((LinePoint_0 - TriPoint_1), r) / glm::cross(r, s1)).z;

	//Line with side tripoint_2 -> tripoint_0
	glm::vec3 s2 = (TriPoint_2 - TriPoint_0);
	float c = (glm::cross((LinePoint_0 - TriPoint_2), r) / glm::cross(r, s2)).z;
	
	glm::vec3 p0;
	glm::vec3 p1;
	glm::vec3 p2;

	//if any points are between 0.0f and 1.0f, they are colliding
	if (a <= 1.0f && a >= 0.0f) p0 = TriPoint_0 - (s0 * a);
	if (b <= 1.0f && b >= 0.0f) p1 = TriPoint_1 - (s1 * b);
	if (c <= 1.0f && c >= 0.0f) p2 = TriPoint_2 - (s2 * c);

	//if side a and b are colliding
	if (p0 != glm::vec3() && p1 != glm::vec3()) {

		glm::vec3 Color(0.87f, 0.16f, 0.2f);
		tri1->AddPoint(glm::vec2(TriPoint_0.x, TriPoint_0.y), Color);
		tri1->AddPoint(glm::vec2(p0.x, p0.y), Color);
		tri1->AddPoint(glm::vec2(TriPoint_2.x, TriPoint_2.y), Color);

		Color = { 0.14f, 0.42f, 1.0f };
		tri2->AddPoint(glm::vec2(p0.x, p0.y), Color);
		tri2->AddPoint(glm::vec2(TriPoint_1.x, TriPoint_1.y), Color);
		tri2->AddPoint(glm::vec2(p1.x, p1.y), Color);

		Color = { 0.04f, 0.58f, 0.09f };
		tri3->AddPoint(glm::vec2(p0.x, p0.y), Color);
		tri3->AddPoint(glm::vec2(p1.x, p1.y), Color);
		tri3->AddPoint(glm::vec2(TriPoint_2.x, TriPoint_2.y), Color);
	}

	//if side b and c are colliding
	if (p0 != glm::vec3() && p2 != glm::vec3()) {

		glm::vec3 Color(0.87f, 0.16f, 0.2f);
		tri1->AddPoint(glm::vec2(TriPoint_0.x, TriPoint_0.y), Color);
		tri1->AddPoint(glm::vec2(p0.x, p0.y), Color);
		tri1->AddPoint(glm::vec2(p2.x, p2.y), Color);


		Color = { 0.14f, 0.42f, 1.0f };
		tri2->AddPoint(glm::vec2(TriPoint_1.x, TriPoint_1.y), Color);
		tri2->AddPoint(glm::vec2(p0.x, p0.y), Color);
		tri2->AddPoint(glm::vec2(p2.x, p2.y), Color);

		Color = { 0.04f, 0.58f, 0.09f };
		tri3->AddPoint(glm::vec2(p2.x, p2.y), Color);
		tri3->AddPoint(glm::vec2(TriPoint_1.x, TriPoint_1.y), Color);
		tri3->AddPoint(glm::vec2(TriPoint_2.x, TriPoint_2.y), Color);
	}

	//if side c and a are colliding
	if (p2 != glm::vec3() && p1 != glm::vec3()) {

		glm::vec3 Color(0.87f, 0.16f, 0.2f);
		tri1->AddPoint(glm::vec2(TriPoint_0.x, TriPoint_0.y), Color);
		tri1->AddPoint(glm::vec2(TriPoint_1.x, TriPoint_1.y), Color);
		tri1->AddPoint(glm::vec2(p2.x, p2.y), Color);


		Color = { 0.14f, 0.42f, 1.0f };
		tri2->AddPoint(glm::vec2(TriPoint_1.x, TriPoint_1.y), Color);
		tri2->AddPoint(glm::vec2(p2.x, p2.y), Color);
		tri2->AddPoint(glm::vec2(p1.x, p1.y), Color);


		Color = { 0.04f, 0.58f, 0.09f };
		tri3->AddPoint(glm::vec2(p2.x, p2.y), Color);
		tri3->AddPoint(glm::vec2(p1.x, p1.y), Color);
		tri3->AddPoint(glm::vec2(TriPoint_2.x, TriPoint_2.y), Color);
	}
}

void Render() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	tri1->Render(shaderProgram);
	tri2->Render(shaderProgram);
	tri3->Render(shaderProgram);
	tri0->Render(shaderProgram);
	line0->Render(shaderProgram);
	glutSwapBuffers();
}

void Update() {
	//Processing key input;
	char Result = IM->ProcessKeys();
	if (Result == 't') {
		std::cout << "Resetting triangle\n";
		tri0->ResetPoints();
		tri1->ResetPoints();
		tri2->ResetPoints();
		tri3->ResetPoints();
		line0->ResetPoints();
		CurrentPoint = 0;
	}
	else if (Result == 'l') {
		std::cout << "Resetting line\n";
		line0->ResetPoints();
		tri1->ResetPoints();
		tri2->ResetPoints();
		tri3->ResetPoints();
		CurrentPoint = 3;
	}

	else if (line0->isValid && tri0->isValid) {
		GenerateResultingTris(*line0, *tri0);
	}

	//if the input is valid
	else if (IM->ProcessMouse() == true) {
		//drawing the triangle
		if (CurrentPoint < 3) {
			tri0->AddPoint(IM->GetMousePos(), glm::vec3(1.0f, 1.0f, 1.0f));
			CurrentPoint++;
		}

		//drawing the line
		else if (CurrentPoint < 6) {
			line0->AddPoint(IM->GetMousePos());
			CurrentPoint++;
		};
		tri0->Process();
		line0->Process();
	}
	tri1->Process();
	tri2->Process();
	tri3->Process();
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

void exit() {
	delete SL; SL = nullptr;
	delete IM; IM = nullptr;
	shaderProgram = 0;
	delete line0; line0 = nullptr;
	delete tri0; tri0 = nullptr;
	delete tri1; tri1 = nullptr;
	delete tri2; tri2 = nullptr;
	delete tri3; tri3 = nullptr;
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

