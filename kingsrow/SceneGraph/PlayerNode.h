#pragma once

#include "../SceneGraph/SceneNode.h"
#include "../SceneGraph/CameraNode.h"

class PlayerNode :
	public SceneNode
{
public:
	PlayerNode(int uuid);
	~PlayerNode();

	void setCamera(CameraNode* camera);

	virtual void update(double timeStep, InputHandler* input);

	virtual glm::highp_mat4 propagateMatrix();

	glm::vec3 getPosition();

private:
	
	CameraNode* playerCamera;
	glm::vec3 position;
	glm::vec3 direction;
	glm::vec3 right;
	glm::vec3 up;

	double oldMousePosX;
	double oldMousePosY;



	float horizontalAngle = 3.14f;
	float verticalAngle = 0.0f;
	float speed = 3.0f;
	float turnSpeed = 0.001f;

	void updateDirection(double deltaTime, float hAngle, float vAngle);
	void move(float time, float speed, int dir);
};

