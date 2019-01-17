#include "SimpleLightingShaderProgram.h"

#include <iostream>
#include <sstream>
#include <glm\glm.hpp>
#include "..\SceneGraph\LightNode\LightsEnum.h"

SimpleLightingShaderProgram::SimpleLightingShaderProgram(GLuint shaderProgramID) : ShaderProgram(shaderProgramID)
{
}


SimpleLightingShaderProgram::~SimpleLightingShaderProgram()
{
}

void SimpleLightingShaderProgram::loadUniformLocations()
{
	locationMVP = glGetUniformLocation(programId, "MVP");
	locationTexture = glGetUniformLocation(programId, "myTextureSampler");
	locationV = glGetUniformLocation(programId, "V");
	locationM = glGetUniformLocation(programId, "M");
}

void SimpleLightingShaderProgram::fillUniformLocation(MeshNode* node, std::vector<LightNode*> lights)
{
	this->useLights(lights);
	glm::mat4 MVP = node->getModelViewProjectionMatrix();
	glUniformMatrix4fv(locationMVP, 1, GL_FALSE, &MVP[0][0]);
	this->bindTextures(node);
	glm::mat4 M = node->getModelMatrix();
	glUniformMatrix4fv(locationM, 1, GL_FALSE, &M[0][0]);
	glm::mat4 V = node->getViewMatrix();
	glUniformMatrix4fv(locationV, 1, GL_FALSE, &V[0][0]);

}

void SimpleLightingShaderProgram::bindTextures(MeshNode* node)
{
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, node->getTexture()->getTextureID());
	glUniform1i(locationTexture, 0);
}

void SimpleLightingShaderProgram::useLights(std::vector<LightNode*> lights)
{
	for (int i = 0; i < lights.size(); i++) {
		std::stringstream position;
		position << "lights[";
		position << i;
		position << "].position";
		//auto loc = glGetUniformLocation(programId, position.str().c_str());
		glUniform3f(glGetUniformLocation(programId, position.str().c_str()), lights.at(i)->getPosition().x, lights.at(i)->getPosition().y, lights.at(i)->getPosition().z);
		std::stringstream intensity;
		intensity << "lights[";
		intensity << i;
		intensity << "].intensity";
		//auto loc2 = glGetUniformLocation(programId, intensity.str().c_str());
		glUniform1f(glGetUniformLocation(programId, intensity.str().c_str()), lights.at(i)->getIntensity());
		std::stringstream color;
		color << "lights[";
		color << i;
		color << "].color";
		//auto loc3 = glGetUniformLocation(programId, color.str().c_str());
		glUniform3f(glGetUniformLocation(programId, color.str().c_str()), lights.at(i)->getColor().x, lights.at(i)->getColor().y, lights.at(i)->getColor().z);
		std::stringstream type;
		type << "lights[";
		type << i;
		type << "].type";
		//auto loc4 = glGetUniformLocation(programId, type.str().c_str());
		if (lights.at(i)->getLightType() == POINT_LIGHT) {
			glUniform1f(glGetUniformLocation(programId, type.str().c_str()), 1.0f);
		}
		else if (lights.at(i)->getLightType() == DIRECTIONAL_LIGHT) {
			glUniform1f(glGetUniformLocation(programId, type.str().c_str()), 2.0f);
			std::stringstream direction;
			direction << "lights[";
			direction << i;
			direction << "].direction";
			//auto loc5 = glGetUniformLocation(programId, direction.str().c_str());
			glUniform3f(glGetUniformLocation(programId, direction.str().c_str()), lights.at(i)->getDirection().x, lights.at(i)->getDirection().y, lights.at(i)->getDirection().z);
			//std::cout << lights.at(i)->getDirection().x << " " << lights.at(i)->getDirection().y << " " << lights.at(i)->getDirection().z << std::endl;
		}	
		else if (lights.at(i)->getLightType() == SPOT_LIGHT) {
			glUniform1f(glGetUniformLocation(programId, type.str().c_str()), 3.0f);
			std::stringstream direction;
			direction << "lights[";
			direction << i;
			direction << "].direction";
			//auto loc5 = glGetUniformLocation(programId, direction.str().c_str());
			glUniform3f(glGetUniformLocation(programId, direction.str().c_str()), lights.at(i)->getDirection().x, lights.at(i)->getDirection().y, lights.at(i)->getDirection().z);
			std::stringstream cutOff;
			cutOff << "lights[";
			cutOff << i;
			cutOff << "].cutOff";
			glUniform2f(glGetUniformLocation(programId, cutOff.str().c_str()), lights.at(i)->getCutOff().x, lights.at(i)->getCutOff().y);
		}
	}
}