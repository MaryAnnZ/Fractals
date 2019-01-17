//#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm\glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#pragma once
class Camera
{
public:
	Camera(glm::vec3 position, glm::vec3 target, glm::vec3 up, int speed);
	~Camera();

	void setMovementX(bool right);
	void setMovmentZ(bool front);
	glm::mat4 getViewMatrix() { return glm::lookAt(mPosition, mPosition+mDirection, mUp); }

private:
	glm::vec3 mPosition;
	glm::vec3 mTarget;
	glm::vec3 mDirection;
	glm::vec3 mUp;
	glm::vec3 mRight;
	int mSpeed;

};

