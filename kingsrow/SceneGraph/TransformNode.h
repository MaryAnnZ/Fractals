#pragma once

#include <glm\glm.hpp>

#include "../SceneGraph/SceneNode.h"

class TransformNode : public SceneNode
{
public:
	
	TransformNode(int uuid, glm::mat4 transform);
	~TransformNode();

	virtual glm::highp_mat4 propagateMatrix();

	glm::highp_mat4 getTransform();
	glm::mat4 getTransformMat4() { return glm::mat4(transformMatrix); }
	void setNewTransform(glm::highp_mat4 newTransformMatrix);

private:
	glm::highp_mat4 transformMatrix;

};

