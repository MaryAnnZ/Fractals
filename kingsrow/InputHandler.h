#pragma once
#include <glad/glad.h>
//#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>


class InputHandler
{
public:
	InputHandler();
	~InputHandler();
	void update(GLFWwindow* window);

	bool w, a, s, d, esc;
	double xPos, yPos;
};

