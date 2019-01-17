#pragma once
#include <glad/glad.h>
//#include <GL/glew.h>

//forward declaration
#include "../SceneGraph/MeshNode.h"
#include "../SceneGraph/LightNode/LightNode.h"

class MeshNode;
class Text;
class Framebuffer;


class ShaderProgram
{
public:
	
	ShaderProgram(GLuint shaderProgramID);

	GLuint getShaderId();

	ShaderProgram();
	~ShaderProgram();

	virtual void loadUniformLocations() = 0;
	virtual void fillUniformLocation(MeshNode* node, std::vector<LightNode*> lights) = 0;

protected:
	GLuint programId;
};

