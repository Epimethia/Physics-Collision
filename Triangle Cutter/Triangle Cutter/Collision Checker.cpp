#include "Collision Checker.h"

void Limit(float& _f) {
	//if the value is more than one, limit it to 1
	if (_f > 1.0f) _f = 1.0f;
	else if (_f < 0.0f) _f = 0.0f;
}

Line CollisionChecker::CheckCollisions(Capsule& _cap0, Capsule& _cap1, Text* _text) {
	glm::vec2 p1 = _cap0.PointA;
	glm::vec2 n1 = _cap0.PointB - _cap0.PointA;


	glm::vec2 p2 = _cap1.PointA;
	glm::vec2 n2 = _cap1.PointB - _cap1.PointA;

	glm::vec2 r = (p1 - p2);

	float d = (glm::dot(n1, n1) * glm::dot(n2, n2)) - (glm::dot(n2, n1) * glm::dot(n1, n2));

	float s = ((glm::dot(n1, n2) * glm::dot(n2, r)) - (glm::dot(n1, r) * glm::dot(n2, n2))) / d;
	float t = ((glm::dot(n1, n1) * glm::dot(n2, r)) - (glm::dot(n1, n2) * glm::dot(n1, r))) / d;

	Limit(s);
	Limit(t);

	Line l;
	glm::vec2 A = (p1 + (s * n1));		//point on the first capsule
	glm::vec2 B = (p2 + (t * n2));		//point on the second capsule

	//vector from p1->B
	glm::vec2 a = B - p1;
	glm::vec2 b = glm::normalize(n1);
	float a1 = glm::dot(a, b);

	//vector from p2->A
	a = A - p2;
	b = glm::normalize(n2);
	float a2 = glm::dot(a, b);

	if (a1 / glm::length(n1) <= 1.0f && a1 / glm::length(n1) >= 0.0f) {
		A = p1 + (a1 * glm::normalize(n1));
	}
	else if (a2 / glm::length(n2) <= 1.0f && a2 / glm::length(n2) >= 0.0f) {
		B = p2 + (a2 * glm::normalize(n2));
	}

	//checking if the capsules are intersecting
	if (!(glm::length(B - A) <= (_cap0.radius + _cap1.radius))) {
		A = A - (glm::normalize(A - B) * _cap0.radius);
		B = B - (glm::normalize(B - A) * _cap1.radius);
		l.AddPoint(A);
		l.AddPoint(B);
	}


	return l;
}
