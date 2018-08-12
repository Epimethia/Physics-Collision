#pragma once
#include <iostream>

#include "Dependencies\glm\vec3.hpp"
#include "Dependencies\glm\glm.hpp"
#include "Dependencies\glm\gtx\string_cast.hpp"

struct Plane {
	glm::vec3 Pos;
	glm::vec3 Normal;

	Plane() {};
	Plane(glm::vec3 _Pos, glm::vec3 _Normal) : Pos(_Pos), Normal(_Normal) {
		std::cout << "Plane created with:\n[Pos] " << glm::to_string(_Pos) << "\n[Normal] " << glm::to_string(_Normal) << "\n\n";
	}
};

struct Line {
	glm::vec3 Point_0;
	glm::vec3 Point_1;
	Line() {};
	Line(glm::vec3 _PointA, glm::vec3 _PointB) {
		Point_0 = _PointA;
		Point_1 = _PointB;

		std::cout << "Line Created between:\n[0] " << glm::to_string(Point_0) << "\n[1] " << glm::to_string(Point_1) << "\n";
		std::cout << "\n";
	};
};

struct Triangle {
	Line SideA;
	Line SideB;
	Line SideC;
	Triangle() {};
	Triangle(glm::vec3 _A, glm::vec3 _B, glm::vec3 _C) {
		std::cout << "Triangle Created with lines:\n";
		std::cout << "	";
		SideA = Line(_A, _B);
		std::cout << "	";
		SideB = Line(_B, _C);
		std::cout << "	";
		SideC = Line(_C, _A);
	};
};

