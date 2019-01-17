#include "SceneNode.h"

#include <rpc.h>

#include <iostream>

SceneNode::SceneNode(int uuid, NodeType type) : uuid(uuid), nodeType(type)
{
	parent = nullptr;
}

SceneNode::~SceneNode()
{
	for (SceneNode* child : childList)
	{
		delete child;
	}
}

void SceneNode::update(double timeStep, InputHandler* input)
{
	for (SceneNode* child : childList)
	{
		child->update(timeStep, input);
	}
}

void SceneNode::attachChild(SceneNode* child)
{
	childList.push_back(child);
	child->setParent(this);
} 

//This leaves the empty transform nodes hanging which is kind of bad, should be refactored to also take out the empty transform nodes.
bool SceneNode::detachChild(SceneNode* deleteChild)
{
	for (std::vector<SceneNode*>::iterator iter = childList.begin(); iter != childList.end(); iter++)
	{
		if (*iter == deleteChild)
		{
			childList.erase(iter);
			delete *iter;
			return true;
		}
		return (*iter)->detachChild(deleteChild);
	}
	return false;
}

glm::highp_mat4 SceneNode::propagateMatrix()
{
	return glm::highp_mat4();
}

void SceneNode::setParent(SceneNode* parent)
{
	this->parent = parent;
}

NodeType SceneNode::getType()
{
	return nodeType;
}

int* SceneNode::getUuid()
{
	return &uuid;
}

std::vector<SceneNode*> SceneNode::getChildren()
{
	return childList;
}

SceneNode* SceneNode::getParent()
{
	return parent;
}