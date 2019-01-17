#include "CameraNode.h"
#include <iostream>


CameraNode::CameraNode(int uuid, int viewPortResX, int viewPortResY) : SceneNode(uuid, NodeType::CAMERA_NODE)
{	
	position = glm::vec3(0, 1, 0);
	glm::vec3 up = glm::vec3(0, 0.6, 0);
	direction = glm::vec3(0, 0, 1);
	viewMatrix = glm::lookAt(position, position + direction, up);
	projectionMatrix = glm::perspective(75.0f, viewPortResX/(float)viewPortResY, 0.1f, 50.0f);
}

CameraNode::~CameraNode()
{
}


void CameraNode::update(double deltaTime, InputHandler* input)
{


}
glm::mat4 CameraNode::getViewMatrix()
{
	return glm::mat4(propagateMatrix());
	/*viewMatrix = glm::lookAt(
		position,
		position + direction,
		up
		);
	return viewMatrix; */
}

glm::mat4 CameraNode::getProjectionMatrix()
{
	return projectionMatrix;
}

glm::highp_mat4 CameraNode::propagateMatrix()
{
	return parent->propagateMatrix();
}

glm::vec3 CameraNode::getPosition()
{
	return position;
}