#include "DirectionalLightNode.h"


DirectionalLightNode::DirectionalLightNode(int uuid, glm::vec3 position, GLfloat intensity, glm::vec3 color, glm::vec3 direction, LightType type) : LightNode(uuid, position, intensity, color, LightType::DIRECTIONAL_LIGHT)
{
	this->direction = direction;
}


DirectionalLightNode::~DirectionalLightNode()
{
}

glm::vec3 DirectionalLightNode::getDirection()
{
	return direction;
}

glm::vec2 DirectionalLightNode::getCutOff()
{
	return glm::vec2();
}