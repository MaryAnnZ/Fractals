#pragma once

#include "..\Shader\ShaderProgram.h"
#include "..\Texture\Texture.h"

class SimpleLightingShaderProgram : public ShaderProgram
{
public:
	SimpleLightingShaderProgram(GLuint shaderProgramID);
	~SimpleLightingShaderProgram();

	virtual void loadUniformLocations();
	virtual void fillUniformLocation(MeshNode* node, std::vector<LightNode*> lights);

private:
	GLuint locationMVP;
	GLuint locationV;
	GLuint locationM;
	GLuint locationTexture;
	GLuint locationLight;
	
	void useLights(std::vector<LightNode*> lights);
	void bindTextures(MeshNode* node);
};

