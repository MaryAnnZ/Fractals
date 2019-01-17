#pragma once
#include <glad/glad.h>
#include <string>
//#include <GL\glew.h>
#include "SamplerStateEnum.h"
#include "MipmapStateEnum.h"

class Texture
{
public:

	Texture(const char* path);
	Texture(int width, int height);
	~Texture();

	void bind(int unit);

	GLuint getTextureID();

	void setSamplerState();
	SamplerState getSamplerState();
	void setMipmapState();
	MipmapState getMipmapState();

private:

	GLubyte* texture;
	GLuint textureID;

	SamplerState samplerState;
	MipmapState mipmapState;
};

