#include "SpotLightNode.h"


SpotLightNode::SpotLightNode(int uuid, glm::vec3 position, GLfloat intensity, glm::vec3 color, glm::vec3 direction, glm::vec2 cutOff, LightType type) : LightNode(uuid, position, intensity, color, LightType::SPOT_LIGHT)
{
	this->direction = direction;
	this->cutOff = cutOff;
}


SpotLightNode::~SpotLightNode()
{
}

glm::vec3 SpotLightNode::getDirection()
{
	return direction;
}

glm::vec2 SpotLightNode::getCutOff()
{
	return cutOff;
}