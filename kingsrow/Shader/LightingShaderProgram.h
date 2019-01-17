#pragma once

#include "../Shader/ShaderProgram.h"

class LightingShaderProgram : public ShaderProgram
{
public:
	LightingShaderProgram(GLuint shaderProgramID);
	~LightingShaderProgram();

	virtual void loadUniformLocations();
	virtual void fillUniformLocation(MeshNode* node, std::vector<LightNode*> lights);

	GLuint getLocationMVP();
	GLuint getLocationTexture();
	
private:
	GLuint locationMVP;
	GLuint locationV;
	GLuint locationM;
	GLuint locationLightInvDirection_worldspace;
	GLuint locationDepthBiasMVP;
	

};

