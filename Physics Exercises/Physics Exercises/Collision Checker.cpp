#include "Collision Checker.h"

void Limit(float& _f) {
	//if the value is more than one, limit it to 1
	if (_f > 1.0f) _f = 1.0f;
	else if (_f < 0.0f) _f = 0.0f;
}

Line CollisionChecker::CheckCollisions(Capsule& _cap0, Capsule& _cap1) {
	/*This is just simply getting the points and the magnitudes that make up a line.*/
	/*These are important for the parametric line equations							*/

	/*Point A*/
	glm::vec2 p1 = _cap0.PointA;
	glm::vec2 n1 = _cap0.PointB - _cap0.PointA;

	/*Point B*/
	glm::vec2 p2 = _cap1.PointA;
	glm::vec2 n2 = _cap1.PointB - _cap1.PointA;

	/*The direction from the start of the lineA to lineB. Not 100% certain on this, */
	/*but I assume this is important because of the fact that the dot product		*/
	/*two orthogonal vectors must be zero, and thus is important in the calculations*/
	/*for s & t?																	*/	
	glm::vec2 r = (p1 - p2);

	/*Again, not entirely sure what d value is equal to, but my assumption is that  */
	/*is that d is some limiting value to make sure that the dot product of the		*/
	/*orthogonal vectors is zero.													*/		
	float d = (glm::dot(n1, n1) * glm::dot(n2, n2)) - (glm::dot(n2, n1) * glm::dot(n1, n2));

	/*Using the values above, we can calculate at what ratio along the line from the*/
	/*starting point and ending point of each line that the closes point lies. This */
	/*is found by multiplying the normalized direction vector of each line by its	*/
	/*respective value (s or t)														*/
	float s = ((glm::dot(n1, n2) * glm::dot(n2, r)) - (glm::dot(n1, r) * glm::dot(n2, n2))) / d;
	float t = ((glm::dot(n1, n1) * glm::dot(n2, r)) - (glm::dot(n1, n2) * glm::dot(n1, r))) / d;

	/*limiting the value between 0 - 1, as values over and under this range are		*/
	/*still on the same line, but no longer on the same line segment				*/
	Limit(s);
	Limit(t);

	/*A is the point on lineA that is closes to lineB. Likewise for B.				*/
	glm::vec2 A = (p1 + (s * n1));
	glm::vec2 B = (p2 + (t * n2));

	/*Getting the angle between the direction of the beginning of lineA -> Point B	*/
	/*and the direction of lineA.													*/
	glm::vec2 a = B - p1;
	glm::vec2 b = glm::normalize(n1);
	float a1 = glm::dot(a, b);

	/*Likewise for the direction of the beginning of lineB -> Point A, and the		*/
	/*direction of lineB. Excuse the reuse of glm::vec2 variables.					*/
	a = A - p2;
	b = glm::normalize(n2);
	float a2 = glm::dot(a, b);

	/*Heres where the magic happens I guess? There is one thing to note here. When	*/
	/*calculating the shortest point between two line segments, it will result in	*/
	/*two scenarios: a) an endpoint of a line will be closest to some point along	*/
	/*the other line, or b) all points will be equidistant as the two lines are		*/
	/*parallel. So, using this logic, we check if either of the ratios are 0 or 1,  */
	/*as this will give us the line with the the closest point being an end point.  */

	/*This checks if the closest point on lineA is at 0 or 1						*/
	if (a1 / glm::length(n1) <= 1.0f && a1 / glm::length(n1) >= 0.0f) {
		A = p1 + (a1 * glm::normalize(n1));
	}
	/*Likewise with lineB															*/
	else if (a2 / glm::length(n2) <= 1.0f && a2 / glm::length(n2) >= 0.0f) {
		B = p2 + (a2 * glm::normalize(n2));
	}

	/*Thus, the closests point between lineA and lineB is the line segment between  */
	/*pointA and pointB.															*/

	/*This is creating a line entity to indicate the closest point. the A and B		*/
	/*values are modified so that the line starts on the edge of the capsule, rather*/
	/*than the line that the capsule is based upon.									*/

	Line l;
	/*checking if the capsules are intersecting. If they are, dont draw the line	*/
	if (!(glm::length(B - A) <= (_cap0.radius + _cap1.radius))) {
		A = A - (glm::normalize(A - B) * _cap0.radius);
		B = B - (glm::normalize(B - A) * _cap1.radius);
		l.AddPoint(A);
		l.AddPoint(B);
	}
	return l;
}
