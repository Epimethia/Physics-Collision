#pragma once
#include "Dependencies\glew\glew.h"
#include "Dependencies\freeglut\freeglut.h"
#include "Dependencies\glm\glm.hpp"
#include "Dependencies\glm\gtx\string_cast.hpp"
#include "Capsule.h"
#include "Line.h"
#include "Text.h"
#include "Triangle.h"


class CollisionChecker {
public: 
	static Line CheckCollisions(Capsule& _cap0, Capsule& _cap1);
	static bool CheckCollisions(glm::vec2 _Point, Triangle _tri);
private:
	GLuint VAO;
	GLuint VBO;

};