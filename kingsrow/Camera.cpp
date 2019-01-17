#include "Camera.h"



Camera::Camera(glm::vec3 position, glm::vec3 target, glm::vec3 up, int speed)
{
	mPosition = position;
	mTarget = target;
	mDirection = glm::normalize(mPosition-mTarget);
	mRight = glm::normalize(glm::cross(up, mDirection));
	mUp = glm::cross(mDirection, mRight);
	mSpeed = speed;
}


Camera::~Camera()
{
}

void Camera::setMovementX(bool right)
{
	if (right) {
		mPosition += glm::normalize(glm::cross(mDirection, mUp)) * (float) mSpeed;
	}
	else {
		mPosition -= glm::normalize(glm::cross(mDirection, mUp)) * (float) mSpeed;
	}
}

void Camera::setMovmentZ(bool front)
{
	if (front) {
		mPosition += (float) mSpeed * mDirection;
	}
	else {
		mPosition -= (float) mSpeed * mDirection;
	}
}
