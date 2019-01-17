#include "InputHandler.h"
#include <iostream>


InputHandler::InputHandler()
{
	esc = false;
}


InputHandler::~InputHandler()
{
}

void InputHandler::update(GLFWwindow* window)
{
	glfwGetCursorPos(window, &xPos, &yPos);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	w = glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS;
	s = glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS;
	d = glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS;
	a = glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS;
	esc = glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS;
}

