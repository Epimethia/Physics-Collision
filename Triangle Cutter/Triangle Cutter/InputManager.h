#pragma once
#include "Dependencies\glew\glew.h"
#include "Dependencies\freeglut\freeglut.h"
#include "Dependencies\glm\glm.hpp"
#include "Dependencies\glm\gtx\string_cast.hpp"
#include <iostream>

enum KEYSTATE {
	FIRST_PRESSED,
	HELD,
	RELEASED
};

enum MOUSE_INPUT {
	MOUSE_LEFT,
	MOUSE_RIGHT,
	MOUSE_MIDDLE
};



class InputManager {
public:

	//Initializes all the keys in the array to "Released" state
	InputManager() {
		for (int i = 0; i < 255; ++i) KeyArray[i] = RELEASED;
		for (int i = 0; i < 3; ++i) MouseArray[i] = RELEASED;
	}

	glm::vec2 GetMousePos() { return MousePos; }

	unsigned char ProcessKeys() {
		glutKeyboardFunc(InputManager::NormKeyDown);
		glutKeyboardUpFunc(InputManager::NormKeyUp);

		if (KeyArray['t'] == FIRST_PRESSED) {
			KeyArray['t'] = HELD;
			return 't';
		}
		else if (KeyArray['l'] == FIRST_PRESSED) {
			KeyArray['l'] = HELD;
			return 'l';
		}
		else return 'm';
	}

	bool ProcessMouse() {
		glutMouseFunc(MouseButton);
		glutMotionFunc(MouseMovement);
		glutPassiveMotionFunc(MouseMovement);

		if (MouseArray[MOUSE_LEFT] == FIRST_PRESSED) {
			std::cout << "Left MB Pressed. Pos: " << glm::to_string(MousePos) << "\n";
			
			MouseArray[MOUSE_LEFT] = HELD;
			return true;
		}
		else return false;
	}

private:
	//Contains an array of all normal characters on a keyboard
	static unsigned char KeyArray[255];

	//Contains an array of the 3 mouse buttons
	static unsigned int MouseArray[3];

	static glm::vec2 MousePos;


	static void NormKeyDown(unsigned char key, int x, int y) {
		KeyArray[key] = FIRST_PRESSED;
	};

	static void NormKeyUp(unsigned char key, int x, int y) {
		KeyArray[key] = RELEASED;
	};

	static void MouseButton(int button, int state, int x, int y) {
		if (button < 3) {
			if (state == GLUT_DOWN) MouseArray[button] = FIRST_PRESSED;
			else if (state == GLUT_UP) MouseArray[button] = RELEASED;
		}
	}

	static void MouseMovement(int x, int y) {
		MousePos = glm::vec2(x, y);
	}

};

unsigned char InputManager::KeyArray[255];
unsigned int InputManager::MouseArray[3];
glm::vec2 InputManager::MousePos = glm::vec2();