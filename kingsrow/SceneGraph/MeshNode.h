#pragma once
#include <glad/glad.h>
#include <assimp\scene.h>
//#include <GL\glew.h>
#include <map>

#include "SceneNode.h"
#include "../Texture/Texture.h"
#include "../InputHandler.h"
#include "../Importers/MeshLoadInfo.h"
#include "../Shader/ShaderProgram.h"

class ShaderProgram;
class Framebuffer;

class MeshNode :
	public SceneNode
{
public:
	MeshNode(int uuid, aiMesh* triangleMesh, const MeshLoadInfo::LoadInfo* meshLoadInfo);
	~MeshNode();

	//TODO: should probably be moved into Renderer class (renderer->initMeshNodeForRendering(this))
	//MeshNode should only store the data and pass calls through itself.
	void prepareForRendering();
	void unprepareForRendering();

	/*virtual void update(double timeStep, InputHandler* input);*/
	//this takes both the viewprojection matrix as well as the individual matrices so that they don't have to be multiplied per object per frame.
	void draw(glm::mat4 viewMatrix, glm::mat4 projectionMatrix, glm::mat4 viewProjectionMatrix, glm::vec3 playerPosition);

	GLuint getVao();
	int getDrawSize();

	GLuint getUV();

	virtual glm::highp_mat4 propagateMatrix();

	glm::mat4 getModelViewProjectionMatrix();
	glm::mat4 getViewProjectionMatrix();
	glm::mat4 getModelMatrix();
	glm::mat4 getViewMatrix();
	glm::mat4 getProjectionMatrix();

	Texture* getTexture();
	void setActiveTexture(Texture* texture); //if nullptr->myTeyture
	glm::vec3 getPlayerPosition();

	GLuint getMVPLocation();
	GLuint getTextureLocation();
	ShaderProgram* getShaderProgram();

	const MeshLoadInfo::LoadInfo* getLoadInfo();

	SceneNode* getParent();


	
	void setLightSet(int i);
	int getLightSet();

private:
	aiMesh* triangleMesh;

	GLuint vao;
	GLuint vertexBuffer;
	GLuint indexBuffer;	
	GLuint normalBuffer;
	GLuint uvBuffer;
	GLuint textureBuffer;

	int vertexAttribPointer;
	int normalAttribPointer;
	int textureAttribPointer;

	glm::highp_mat4 modelMatrix;
	glm::mat4 viewMatrix;
	glm::mat4 projectionMatrix;
	glm::mat4 viewProjectionMatrix;
	
	GLuint myShaderID;
	Texture* activeTexture;
	Texture* myTexture;
	bool textureInit;

	const MeshLoadInfo::LoadInfo* loadInfo;
	ShaderProgram* shaderProgram;

	glm::vec3 playerPosition;
	int lightSet;
};

