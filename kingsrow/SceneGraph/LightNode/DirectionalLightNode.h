#pragma once

#include "LightNode.h"

class DirectionalLightNode : public LightNode
{
public:
	DirectionalLightNode(int uuid, glm::vec3 position, GLfloat intensity, glm::vec3 color, glm::vec3 direction, LightType type);
	~DirectionalLightNode();

	glm::vec3 getDirection();
	glm::vec2 getCutOff();

private:

	glm::vec3 direction;
};

