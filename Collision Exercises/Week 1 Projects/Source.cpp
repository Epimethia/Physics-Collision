#include <conio.h>
#include <time.h>

#include "ResultCheckers.h"
#include "Functions.h"

//Function to randomly generate a vector
glm::vec3 GenerateVector() {
	auto Vec = glm::vec3(rand() % 101, rand() % 101, rand() % 101);
	return Vec;
};



int main() {

	//Seeding the random generator
	srand(static_cast<int>(time(NULL)));

	//EX 1.1: LAGRANGES FORMULA
	std::cout << "Lagrange's Formula Test.\n";
	CalcTripleProd(GenerateVector(), GenerateVector(), GenerateVector());

	std::cout << "\n\n-------------------------------------------------------------------\n\n";


	//EX 1.2: PLANE POINT COLLISION
	std::cout << "Point is on the Plane test.\n";
	Plane pl0(glm::vec3(), glm::vec3(1.0f, 0.0f, 0.0f));
	CheckResult(
		PlanePointCollision(glm::vec3(), pl0)
	);
	std::cout << "\n\n-----------------------------\n\n";

	std::cout << "Point is in front of the Plane test.\n";
	pl0 = Plane(glm::vec3(), glm::vec3(1.0f, 0.0f, 0.0f));
	CheckResult(
		PlanePointCollision(glm::vec3(1.0f, 0.0f, 0.0f), pl0)
	);
	std::cout << "\n\n-----------------------------\n\n";

	std::cout << "Point is behind the Plane test.\n";
	pl0 = Plane(glm::vec3(), glm::vec3(1.0f, 0.0f, 0.0f));
	CheckResult(
		PlanePointCollision(glm::vec3(-1.0f, 0.0f, 0.0f), pl0)
	);
	std::cout << "\n\n-----------------------------\n\n";

	std::cout << "Random Test\n";
	Plane pl1(GenerateVector(), GenerateVector());
	CheckResult(
		PlanePointCollision(GenerateVector(), pl1)
	);

	std::cout << "\n\n-------------------------------------------------------------------\n\n";

	//EX 1.3: LINE PLANE COLLISION
	std::cout << "No collision (collides before the start point) test.\n";
	Plane pl2(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	Line l0(glm::vec3(1.0f, 1.0f, 0.0f), glm::vec3(3.0f, 3.0f, 0.0f));
	CheckResult(
		LinePlaneCollision(l0, pl2)
	);
	std::cout << "\n\n-----------------------------\n\n";

	std::cout << "No collision (collides after the end point) test.\n";
	pl2 = Plane(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	Line l1(glm::vec3(3.0f, 3.0f, 0.0f), glm::vec3(1.0f, 1.0f, 0.0f));
	CheckResult(
		LinePlaneCollision(l1, pl2)
	);
	std::cout << "\n\n-----------------------------\n\n";

	std::cout << "Collision (start point collides with plane) test.\n";
	pl2 = Plane(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	Line l2(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	CheckResult(
		LinePlaneCollision(l2, pl2)
	);
	std::cout << "\n\n-----------------------------\n\n";

	std::cout << "Collision (end point collides with plane) test.\n";
	pl2 = Plane(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	Line l3(glm::vec3(0.0f, 1.0f, 1.0f), glm::vec3(0.0f, 0.0f, 0.0f));
	CheckResult(
		LinePlaneCollision(l3, pl2)
	);
	std::cout << "\n\n-----------------------------\n\n";

	std::cout << "No collision (line is parallel with plane) test.\n";
	pl2 = Plane(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	Line l4(glm::vec3(3.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));
	CheckResult(
		LinePlaneCollision(l4, pl2)
	);

	std::cout << "\n\n-------------------------------------------------------------------\n\n";

	//// EX 1.4: TRIANGLE PLANE COLLISION

	std::cout << "Triangle is colliding with plane test\n";
	Triangle TriA(glm::vec3(0.0f, 2.0f, 0.0f), glm::vec3(2.0f, -1.0f, 0.0f), glm::vec3(-2.0f, -1.0f, 0.0f));
	CheckResult(
		TrianglePlaneCollision(TriA, Plane(glm::vec3(), glm::vec3(0.0f, 1.0f, 0.0f)))
	);
	std::cout << "\n\n-----------------------------\n\n";

	std::cout << "Triangle not colliding with plane test\n";
	Triangle TriB(glm::vec3(0.0f, 4.0f, 0.0f), glm::vec3(2.0f, 3.0f, 0.0f), glm::vec3(-2.0f, 3.0f, 0.0f));
	CheckResult(
		TrianglePlaneCollision(TriB, Plane(glm::vec3(), glm::vec3(0.0f, 1.0f, 0.0f)))
	);

	_getch();
	return 0;

}