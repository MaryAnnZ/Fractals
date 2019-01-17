#include "ShaderImporter.h"

#include <fstream>
#include <iostream>
#include <string>

#include "..\Shader\LightingShaderProgram.h"
#include "..\Shader\TextureShaderProgram.h"
#include "..\Shader\SimpleLightingShaderProgram.h"

ShaderImporter::ShaderImporter()
{
		
}

ShaderImporter* ShaderImporter::getInstance()
{
	static ShaderImporter INSTANCE;
	return &INSTANCE;
}

GLuint ShaderImporter::loadShader(std::string shaderPath)
{
	
	GLuint shaderID = -1;
		if (shaderPath.find("Vertex") != std::string::npos)
			shaderID = glCreateShader(GL_VERTEX_SHADER);
		else if (shaderPath.find("Fragment") != std::string::npos)
			shaderID = glCreateShader(GL_FRAGMENT_SHADER);
		else if (shaderPath.find("Geometry") != std::string::npos)
			shaderID = glCreateShader(GL_GEOMETRY_SHADER);
	
	std::string shaderCode = "";
	std::ifstream codeStream(shaderPath, std::ios::in);
	if (codeStream.is_open())
	{
		std::string line = "";
		while (getline(codeStream, line))
			shaderCode += "\n" + line;
		codeStream.close();
	}

	std::cerr << "compiling shader: " << shaderPath << std::endl;
	char const * sourcePointer = shaderCode.c_str();
	glShaderSource(shaderID, 1, &sourcePointer, NULL);
	glCompileShader(shaderID);

	GLint result = GL_FALSE;
	int logLength;

	// Check Shader
	glGetShaderiv(shaderID, GL_COMPILE_STATUS, &result);
	glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &logLength);
	if (logLength > 0){
		std::vector<char> shaderErrorMessage(logLength);
		glGetShaderInfoLog(shaderID, logLength, NULL, shaderErrorMessage.data());
		fprintf(stdout, "%s\n", &shaderErrorMessage[0]);	
	}
	return shaderID;
}

ShaderProgram* ShaderImporter::loadShaderProgram(const MeshLoadInfo::ShaderLoadInfo* shader)
{
	if (shaderPrograms.find(shader) != shaderPrograms.end()) {
		return shaderPrograms.find(shader)->second;
	}
	GLuint vertexShaderID = loadShader(shader->vertexShaderPath);
	GLuint fragmentShaderID = loadShader(shader->fragmentShaderPath);
	GLuint geometryShaderID = 100;
	if (!shader->geometryShaderPath.empty()) {
		geometryShaderID = loadShader(shader->geometryShaderPath);
	}
	GLuint shaderProgramID = glCreateProgram();
	glAttachShader(shaderProgramID, vertexShaderID);
	if (geometryShaderID != 100) {
		glAttachShader(shaderProgramID, geometryShaderID);
	}
	glAttachShader(shaderProgramID, fragmentShaderID);
	glLinkProgram(shaderProgramID);
	
	GLint isLinked = 0;
	glGetProgramiv(shaderProgramID, GL_LINK_STATUS, &isLinked);
	if (isLinked == GL_FALSE)
	{
		GLint maxLength = 0;
		glGetProgramiv(shaderProgramID, GL_INFO_LOG_LENGTH, &maxLength);

		//The maxLength includes the NULL character
		std::vector<GLchar> shaderErrorMessage(maxLength);
		glGetProgramInfoLog(shaderProgramID, maxLength, &maxLength, &shaderErrorMessage[0]);
		fprintf(stdout, "%s\n", &shaderErrorMessage[0]);
		//std::cerr << infoLog << std::endl;
	}	

	ShaderProgram* result = nullptr;
	if (shader == MeshLoadInfo::LIGHTING_SHADER)
	{
		result = new LightingShaderProgram(shaderProgramID);
	}
	else if (shader == MeshLoadInfo::TEXTURE_SHADER)
	{
		result = new TextureShaderProgram(shaderProgramID);
	}
	else if (shader == MeshLoadInfo::SIMPLE_LIGHTING_SHADER)
	{
		result = new SimpleLightingShaderProgram(shaderProgramID);
	}
	shaderPrograms.insert(std::pair<const MeshLoadInfo::ShaderLoadInfo*, ShaderProgram*>(shader, result));
	return result;
}

ShaderImporter::~ShaderImporter()
{
}
