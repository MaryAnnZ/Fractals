#include "ShaderProgram.h"

ShaderProgram::ShaderProgram(GLuint shaderProgramID)
{
	programId = shaderProgramID;
}

GLuint ShaderProgram::getShaderId()
{
	return programId;
}

ShaderProgram::~ShaderProgram()
{
}
