#pragma once
#include <iostream>

enum POINTPOSITION {
	ON_PLANE,
	IN_FRONT,
	BEHIND,
	INVALID
};

enum LINECOLLISIONTYPE {
	BETWEEN_POINTS,
	AT_END_POINT,
	AT_START_POINT,
	BEFORE_START_POINT,
	AFTER_END_POINT,
	PARALLEL_ON_PLANE,
	PARALLEL
};

//Check Result overload for Line Plane Collision
void CheckResult(LINECOLLISIONTYPE _result) {
	std::cout << "\n";
	switch (_result) {
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
	case PARALLEL_ON_PLANE:
		std::cout << "Line is on and parallel to the plane.";
		break;
	case PARALLEL:
		std::cout << "Line is parallel to the plane.";
		break;
	default:break;
	}
}

//Check Result overload for Plane Point Collision
void CheckResult(POINTPOSITION _result) {
	switch (_result) {
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
	};
}

//Check Result overload for Triangle Plane Collision

void CheckResult(bool _Result) {
	if (_Result == true) std::cout << "Triangle is colliding with the plane.";
	else std::cout << "Triangle is not colliding with the plane.";
}