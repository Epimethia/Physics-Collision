#include <iostream>
#include <conio.h>
#include <time.h>

#include "Dependencies\glm\vec3.hpp"
#include "Dependencies\glm\glm.hpp"
#include "Dependencies\glm\gtx\string_cast.hpp"

//Function to randomly generate a vector
glm::vec3 GenerateVector() {
	auto Vec = glm::vec3(rand() % 101, rand() % 101, rand() % 101);
	return Vec;
}


//##########################//
//EX 1.1: LAGRANGE'S FORMULA//
//##########################//
void CalcTripleProd(glm::vec3 _A, glm::vec3 _B, glm::vec3 _C) {
	std::cout << "Vector A: " << glm::to_string(_A) << std::endl;
	std::cout << "Vector B: " << glm::to_string(_B) << std::endl;
	std::cout << "Vector C: " << glm::to_string(_C) << std::endl;

	std::cout << "\n";
	glm::vec3 LHS;
	glm::vec3 RHS;

	LHS = glm::cross(_A, glm::cross(_B, _C));									//Calculating left hand side using crossprod
	std::cout << "LHS Result: " << glm::to_string(LHS) << std::endl;

	RHS = (glm::dot(_A, _C) * _B) - (glm::dot(_A, _B) * _C);					//Calculating right hand side using dotprod
	std::cout << "RHS Result: " << glm::to_string(RHS) << std::endl;

	if (LHS == RHS) std::cout << "LHS is equal to RHS.";
	else std::cout << "LHS is not equal to RHS.";
}


//##########################//
//EX 1.2: PLANE VS POINT    //
//##########################//
enum POINTPOSITION {
	ON_PLANE,
	IN_FRONT,
	BEHIND,
	INVALID
};



void PlanePointCollision(glm::vec3 _PointLocation, glm::vec3 _PlanePosition, glm::vec3 _PlaneNormal) {
	POINTPOSITION result;
	std::cout << "Point Position: " << glm::to_string(_PointLocation) << std::endl;
	std::cout << "Plane Position: " << glm::to_string(_PlanePosition) << std::endl;
	std::cout << "Plane Normal: " << glm::to_string(_PlaneNormal) << std::endl;

	//Calculating the distance d from the point to the plane
	float d = glm::dot(_PlaneNormal, _PlanePosition);
	
	//Checking the point against the plane
	float r = glm::dot(_PlaneNormal, _PointLocation) - d;

	if (r == 0) result = ON_PLANE;
	else if (r > 0) result = IN_FRONT;
	else if (r < 0) result = BEHIND;
	else result = INVALID;

	switch (result) {
		case ON_PLANE:
			std::cout << "The point is on the plane.";
			break;
		case IN_FRONT:
			std::cout << "The point is in front of the plane.";
			break;
		case BEHIND:
			std::cout << "The point is behind the plane.";
			break;
		case INVALID:
			std::cout << "Invalid Calculation.";
			break;
		default:break;
	}
}


//##########################//
//EX 1.3: LINE SEG VS PLANE //
//##########################//
struct Line {
	glm::vec3 Point_0;
	glm::vec3 Point_1;

	Line(glm::vec3 _PointA, glm::vec3 _PointB) {
		Point_0 = _PointA;
		Point_1 = _PointB;

		std::cout << "Line Created between:\n[0] " << glm::to_string(Point_0) << "\n[1] " << glm::to_string(Point_1) << "\n";
	};
};

enum LINECOLLISIONTYPE {
	BETWEEN_POINTS,
	AT_END_POINT,
	AT_START_POINT,
	BEFORE_START_POINT,
	AFTER_END_POINT
};

void LinePlaneCollision(Line _Line, glm::vec3 _PlanePosition, glm::vec3 _PlaneNormal) {
	LINECOLLISIONTYPE result;
	std::cout << "Plane Position: " << glm::to_string(_PlanePosition) << std::endl;
	std::cout << "Plane Normal: " << glm::to_string(_PlaneNormal) << std::endl;

	float r = glm::dot(_PlaneNormal, (_Line.Point_1 - _Line.Point_0));
	float x;
	if (r != 0.0f) {
		 x = glm::dot(_PlaneNormal, (_PlanePosition - _Line.Point_0)) / r;
	}
	else x = 0.0f;

	if (x < 1.0f && x > 0.0f) result = BETWEEN_POINTS;
	else if (x == 0.0f) result = AT_END_POINT;
	else if (x == 1.0f) result = AT_START_POINT;
	else if (x > 1.0f) result = AFTER_END_POINT;
	else if (x < 0.0f) result = BEFORE_START_POINT;

	std::cout << "\n";
	switch (result) {
	case BETWEEN_POINTS:
		std::cout << "Collision between points detected.";
		break;
	case AT_END_POINT:
		std::cout << "Collision at end point detected.";
		break;
	case AT_START_POINT:
		std::cout << "Collision at start point detected.";
		break;
	case BEFORE_START_POINT:
		std::cout << "No collision with line segment. Collides before the start point.";
		break;
	case AFTER_END_POINT:
		std::cout << "No collision with line segment. Collides after the end point.";
		break;
	default:break;
	}
}

//##########################//
//EX 1.3: TRIANGLE VS PLANE //
//##########################//
void TrianglePlaneCollision() {

}

int main() {

	//Seeding the random generator
	srand(static_cast<int>(time(NULL)));

	//EX 1.1: LAGRANGES FORMULA
	CalcTripleProd(GenerateVector(), GenerateVector(), GenerateVector());

	std::cout << "\n\n-------------------------------------------------------------------\n\n";


	//EX 1.2: PLANE POINT COLLISION
	std::cout << "Point is on the Plane test case.\n";
	PlanePointCollision(glm::vec3(), glm::vec3(), glm::vec3(1.0f, 0.0f, 0.0f));
	std::cout << "\n\n-----------------------------\n\n";

	std::cout << "Point is in front test case.\n";
	PlanePointCollision(glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(), glm::vec3(1.0f, 0.0f, 0.0f));
	std::cout << "\n\n-----------------------------\n\n";

	std::cout << "Point is behind test case.\n";
	PlanePointCollision(glm::vec3(-1.0f, 0.0f, 0.0f), glm::vec3(), glm::vec3(1.0f, 0.0f, 0.0f));
	std::cout << "\n\n-----------------------------\n\n";

	std::cout << "Random Test Case\n";
	PlanePointCollision(GenerateVector(), GenerateVector(), GenerateVector());

	std::cout << "\n\n-------------------------------------------------------------------\n\n";

	std::cout << "No collision (collides before the start point) test.\n";
	Line l0(glm::vec3(1.0f, 1.0f, 0.0f), glm::vec3(3.0f, 3.0f, 0.0f));
	LinePlaneCollision(l0, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	std::cout << "\n\n-----------------------------\n\n";

	std::cout << "No collision (collides after the end point) test.\n";
	Line l1(glm::vec3(3.0f, 3.0f, 0.0f), glm::vec3(1.0f, 1.0f, 0.0f));
	LinePlaneCollision(l1, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	std::cout << "\n\n-----------------------------\n\n";

	std::cout << "Collision (start point collides with plane) test.\n";
	Line l2(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	LinePlaneCollision(l2, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	std::cout << "\n\n-----------------------------\n\n";

	std::cout << "Collision (end point collides with plane) test.\n";
	Line l3(glm::vec3(.0f, 1.0f, 1.0f), glm::vec3(0.0f, 0.0f, 0.0f));
	LinePlaneCollision(l3, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f));
	std::cout << "\n\n-----------------------------\n\n";


	_getch();
	return 0;

}