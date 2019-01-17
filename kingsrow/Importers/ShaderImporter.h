#pragma once
#include <glad/glad.h>
//#include <GL\glew.h>
#include <vector>
#include <string>
#include <map>

#include "../shader/ShaderProgram.h"
#include "MeshLoadInfo.h"

class ShaderImporter
{
public:

	//GLuint loadShaderArray(std::vector<std::string> shaderPaths);
	

	ShaderProgram* loadShaderProgram(const MeshLoadInfo::ShaderLoadInfo* shader);
	static ShaderImporter* getInstance();
	~ShaderImporter();

private:
	ShaderImporter();
	ShaderImporter(ShaderImporter const&);
	void operator=(ShaderImporter const&);

	GLuint loadShader(std::string shaderPath);
	
	std::map<const MeshLoadInfo::ShaderLoadInfo*, ShaderProgram*> shaderPrograms;

	
};

