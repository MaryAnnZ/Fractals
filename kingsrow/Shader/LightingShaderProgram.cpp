#include "LightingShaderProgram.h"


LightingShaderProgram::LightingShaderProgram(GLuint shaderProgramID) : ShaderProgram(shaderProgramID)
{
}


LightingShaderProgram::~LightingShaderProgram()
{
}

void LightingShaderProgram::loadUniformLocations()
{
	locationMVP = glGetUniformLocation(programId, "MVP");
	locationMVP = glGetUniformLocation(programId, "MV");
	locationV = glGetUniformLocation(programId, "V");
	locationM = glGetUniformLocation(programId, "M");
	locationLightInvDirection_worldspace = glGetUniformLocation(programId, "LightInvDirection_worldspace");
	locationDepthBiasMVP = glGetUniformLocation(programId, "DepthBiasMVP");

}

GLuint LightingShaderProgram::getLocationMVP()
{
	return locationMVP;
}

GLuint LightingShaderProgram::getLocationTexture()
{
	return -1;
}

void LightingShaderProgram::fillUniformLocation(MeshNode* node, std::vector<LightNode*> lights)
{
	glUniformMatrix4fv(locationMVP, 1, GL_FALSE, &node->getModelViewProjectionMatrix()[0][0]);
	//glUniformMatrix4fv(locationMVP, 1, GL_FALSE, node->getMV());
	glUniformMatrix4fv(locationV, 1, GL_FALSE, &node->getViewMatrix()[0][0]);
	glUniformMatrix4fv(locationM, 1, GL_FALSE, &glm::mat4(node->propagateMatrix())[0][0]);
	//glUniform3fv(locationLightInvDirection_worldspace, 1, GL_FALSE, node->getLightDirection());
	//glUniformMatrix4fv(locationDepthBiasMVP, 1, GL_FALSE, node->getDepthBiasMVP());
}
