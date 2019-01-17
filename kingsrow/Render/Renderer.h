#pragma once
#include <glad/glad.h>
//#include <GL/glew.h>
#include <GLFW\glfw3.h>

#include "../InputHandler.h"
#include "../Texture/Texture.h"
#include "../SceneGraph/PlayerNode.h"
#include "../SceneGraph/SceneGraphEnum.h"
#include "../SceneGraph/SceneNode.h"
#include "../SceneGraph/TransformNode.h"
#include "../SceneGraph/MeshNode.h"
#include "../SceneGraph/CameraNode.h"
#include "../SceneGraph/LightNode/LightNode.h"


class Renderer
{
public:
	static Renderer* getInstance();
	~Renderer();

	int init(int viewPortResX, int viewPortResY);

	void generateBufferObject(GLuint* bufferID);
	void generateFrameBuffer(GLuint* bufferID);
	
	void fillBuffer(GLuint bufferID, GLenum bufferType, int bufferSize, GLvoid* bufferData, GLenum bufferUsage);
	void fillFrameBuffer(GLuint bufferID, GLenum bufferType, GLenum attachment, GLuint texture, GLuint level, int viewPortSizeX, int viewPortSizeY);
	void bindBuffer(GLenum bufferType, GLuint bufferID);

	void generateVertexArray(GLuint* vertexBufferID);
	void bindVertexArray(GLuint vertexArrayId);

	void enableVertexAttribArray(int id);
	void disableVertexAttribArray(int id);
	void setVertexAttribPointer(int id, int size, GLenum type, GLboolean normalized, int stride, const GLvoid* pointer);

	void linkShader(ShaderProgram* shader);
	
	void draw(MeshNode* node);

	GLFWwindow* getWindow();
	void setLights(std::vector<LightNode*> lights);

private:
	//singleton
	Renderer();
	Renderer(Renderer const&);
	void operator=(Renderer const&);	
	
	GLFWwindow* window;
	std::vector<LightNode*> lights;
	std::vector<LightNode*> getLights(MeshNode* node);

	void useShader(MeshNode* node, std::vector<LightNode*> lights);

	int viewPortResX;
	int viewPortResY;
};

