#pragma once

#include "../SceneNode.h"
#include "LightsEnum.h"

class LightNode : public SceneNode
{
public:
	LightNode(int uuid, glm::vec3 position, GLfloat intensity, glm::vec3 color, LightType type);
	~LightNode();

	glm::highp_mat4 propagateMatrix();

	glm::vec3 getPosition();
	GLfloat getIntensity();
	glm::vec3 getColor();
	LightType getLightType();
	virtual glm::vec3 getDirection() = 0;
	virtual glm::vec2 getCutOff() = 0;

private:
	glm::vec3 position;
	GLfloat intensity;
	glm::vec3 color;
	LightType type;
};

