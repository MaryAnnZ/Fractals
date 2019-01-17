#pragma once

#include "LightNode.h"

class PointLightNode : public LightNode
{
public:
	PointLightNode(int uuid, glm::vec3 position, GLfloat intensity, glm::vec3 color, LightType type);
	~PointLightNode();

	glm::vec3 getDirection();
	glm::vec2 getCutOff();
};

