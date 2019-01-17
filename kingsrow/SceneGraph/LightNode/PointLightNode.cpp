#include "PointLightNode.h"


PointLightNode::PointLightNode(int uuid, glm::vec3 position, GLfloat intensity, glm::vec3 color, LightType type) : LightNode(uuid, position, intensity, color, LightType::POINT_LIGHT)
{
}


PointLightNode::~PointLightNode()
{
}

glm::vec3 PointLightNode::getDirection()
{
	return glm::vec3();
}

glm::vec2 PointLightNode::getCutOff()
{
	return glm::vec2();
}
