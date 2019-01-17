#include "Texture.h"
#include <iostream>
#include <stb_image.h>


Texture::Texture(const char* path)
{
	//FREE_IMAGE_FORMAT formato = FreeImage_GetFileType(path, 0);
	//FIBITMAP* image = FreeImage_Load(formato, path);
	//

	//if (!image) {
	//	std::cout << "errorT_T : " << path << std::endl;
	//}

	//FIBITMAP* temp = image;
	//image = FreeImage_ConvertTo32Bits(image);
	//FreeImage_Unload(temp);

	//int w = FreeImage_GetWidth(image);
	//int h = FreeImage_GetHeight(image);
	//if (w == 0 || h == 0) {
	//	std::cout << "Error image loading : " << path << " size is  " << w << "*" << h << std::endl; //Some debugging code
	//}

	//texture = new GLubyte[4 * w*h];
	//char* pixeles = (char*)FreeImage_GetBits(image);
	////FreeImage loads in BGR format, so you need to swap some bytes(Or use GL_BGR).

	//for (int j = 0; j<w*h; j++){
	//	texture[j * 4 + 0] = pixeles[j * 4 + 2];
	//	texture[j * 4 + 1] = pixeles[j * 4 + 1];
	//	texture[j * 4 + 2] = pixeles[j * 4 + 0];
	//	texture[j * 4 + 3] = pixeles[j * 4 + 3];
	//}

	////Now generate the OpenGL texture object 

	//glGenTextures(1, &textureID);
	////glActiveTexture(GL_TEXTURE0);
	//glBindTexture(GL_TEXTURE_2D, textureID);
	//glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, (GLvoid*)texture);
	//glGenerateMipmap(GL_TEXTURE_2D);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);
	// set the texture wrapping parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// load image, create texture and generate mipmaps
	int width, height, nrChannels;
	stbi_set_flip_vertically_on_load(true); // tell stb_image.h to flip loaded texture's on the y-axis.
											// The FileSystem::getPath(...) is part of the GitHub repository so we can find files on any IDE/platform; replace it with your own image path.
	unsigned char *data = stbi_load(path, &width, &height, &nrChannels, 0);
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}
	stbi_image_free(data);

	samplerState = LINEAR;
	mipmapState = TRILINEAR;
	/*GLenum huboError = glGetError();
	if (huboError){

		std::cout << "There was an error loading the texture"  << huboError << std::endl;
	}*/
}

Texture::Texture(int width, int height)
{
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT16, width, height, 0, GL_DEPTH_COMPONENT, GL_FLOAT, 0);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_FUNC, GL_LEQUAL);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_MODE, GL_COMPARE_R_TO_TEXTURE);	
}

Texture::~Texture()
{
	glDeleteTextures(1, &textureID);
}

GLuint Texture::getTextureID()
{
	return textureID;
}

void Texture::setSamplerState()
{
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, textureID);
	switch (samplerState)
	{
	case NEAREST_N :
		samplerState = LINEAR;
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		break;
	case LINEAR :
		samplerState = NEAREST_N;
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		break;
	}
}

SamplerState Texture::getSamplerState()
{
	return samplerState;
}

void Texture::setMipmapState()
{
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, textureID);
	switch (mipmapState)
	{
	case NEAREST :
		mipmapState = BILINEAR;
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
		break;
	case BILINEAR :
		mipmapState = TRILINEAR;
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		break;
	case TRILINEAR :
		mipmapState = NEAREST;
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		break;
	}
}

MipmapState Texture::getMipmapState()
{
	return mipmapState;
}
