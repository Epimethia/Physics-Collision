#pragma once
#include "Shapes.h"

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

	if (LHS == RHS) {
		std::cout << "LHS is equal to RHS.";
	}
	else std::cout << "LHS is not equal to RHS.";

};

//##########################//
//EX 1.2: PLANE VS POINT    //
//##########################//
POINTPOSITION PlanePointCollision(glm::vec3 _PointLocation, Plane _Plane) {
	POINTPOSITION result;
	std::cout << "Point Position: " << glm::to_string(_PointLocation) << std::endl;

	//Calculating the distance d from the point to the plane
	float d = glm::dot(_Plane.Normal, _Plane.Pos);

	//Checking the point against the plane
	float r = glm::dot(_Plane.Normal, _PointLocation) - d;

	if (r == 0) return result = ON_PLANE;
	else if (r > 0) return result = IN_FRONT;
	else if (r < 0) return result = BEHIND;
	else return result = INVALID;
};

//##########################//
//EX 1.3: LINE SEG VS PLANE //
//##########################//
LINECOLLISIONTYPE LinePlaneCollision(Line _Line, Plane _Plane) {
	LINECOLLISIONTYPE result;

	float r = glm::dot(_Plane.Normal, (_Line.Point_1 - _Line.Point_0));
	//if dot between the plane normal and the line is 0, it means it is perpendicular (and thus parallel to the plane)
	if (r == 0.0f) {
		if (PlanePointCollision(_Line.Point_0, _Plane) == ON_PLANE) return result = PARALLEL_ON_PLANE;
		else return PARALLEL;
	}
		
	float x = glm::dot(_Plane.Normal, (_Plane.Pos - _Line.Point_0)) / r;

	if (x < 1.0f && x > 0.0f) return  result = BETWEEN_POINTS;
	else if (x == 0.0f) return result = AT_START_POINT;
	else if (x == 1.0f) return result = AT_END_POINT;
	else if (x > 1.0f) return result = AFTER_END_POINT;
	else return result = BEFORE_START_POINT;
};

//##########################//
//EX 1.3: TRIANGLE VS PLANE //
//##########################//
bool TrianglePlaneCollision(Triangle _Tri, Plane _Plane) {
	LINECOLLISIONTYPE sideA = LinePlaneCollision(_Tri.SideA, _Plane);
	LINECOLLISIONTYPE sideB = LinePlaneCollision(_Tri.SideB, _Plane);
	LINECOLLISIONTYPE sideC = LinePlaneCollision(_Tri.SideC, _Plane);
	
	if (sideA == AT_END_POINT || sideA == AT_START_POINT || sideA == BETWEEN_POINTS) {
		std::cout << "Side A is colliding\n"; 
		return true;
	}
	else if (sideB == AT_END_POINT || sideB == AT_START_POINT || sideB == BETWEEN_POINTS) {
		std::cout << "Side B is colliding\n";
		return true;
	}
	else if (sideC == AT_END_POINT || sideC == AT_START_POINT || sideC == BETWEEN_POINTS) {
		std::cout << "Side C is colliding\n";
		return true;
	}
	else return false;
};