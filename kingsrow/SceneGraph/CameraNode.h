#pragma once


#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include "..\SceneGraph\SceneNode.h"

class CameraNode : 
	public SceneNode
{
public:
	CameraNode(int uuid, int viewPortResX, int viewPortResY);
	~CameraNode();

	glm::highp_mat4 propagateMatrix();

	virtual void update(double timeStep, InputHandler* input);
		
	glm::mat4 getViewMatrix();
	glm::mat4 getProjectionMatrix();
	glm::vec3 getPosition();

private:
	glm::vec3 position;
	glm::vec3 direction;
	glm::vec3 right;
	glm::vec3 up;
	glm::mat4 viewMatrix;
	glm::mat4 projectionMatrix;

	float horizontalAngle = 3.14f;
	float verticalAngle = 0.0f;
	float speed = 3.0f;
	float turnSpeed = 0.1f;
};

