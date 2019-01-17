#include "LightNode.h"


LightNode::LightNode(int uuid, glm::vec3 position, GLfloat intensity, glm::vec3 color, LightType type) : SceneNode(uuid, NodeType::LIGHT_NODE)
{
	this->position = position;
	this->intensity = intensity;
	this->color = color;
	this->type = type;
}

LightNode::~LightNode()
{
}

glm::highp_mat4 LightNode::propagateMatrix()
{
	return parent->propagateMatrix();
}

glm::vec3 LightNode::getPosition()
{
	return position;
}

GLfloat LightNode::getIntensity()
{
	return intensity;
}

glm::vec3 LightNode::getColor()
{
	return color;
}

LightType LightNode::getLightType()
{
	return type;
}

