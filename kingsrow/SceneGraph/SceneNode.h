#pragma once

#include <windows.h>
#include <vector>
#include <glm\glm.hpp>
#include <rpc.h>

#include "SceneGraphEnum.h"
#include "../InputHandler.h"

class SceneNode
{
public:
	SceneNode(int id, NodeType nodeType);
	~SceneNode();

	void setParent(SceneNode* parent);
	SceneNode* getParent();
	virtual void update(double timeStep, InputHandler* input);
	//virtual void draw();
	virtual glm::highp_mat4 propagateMatrix();
	void attachChild(SceneNode* child);
	bool detachChild(SceneNode* child);

	NodeType getType();

	int* getUuid();

	std::vector<SceneNode*> getChildren();
	
	SceneNode* parent;

private:
	std::vector<SceneNode*> childList;	

	int uuid;
	const NodeType nodeType;

};

