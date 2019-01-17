#include "MeshNode.h"

#include <iostream>
#include <glm\gtc\quaternion.hpp>

#include "../Render/Renderer.h"
#include "../Importers/MeshImporter.h"
#include "../Importers/ShaderImporter.h"
#include "TransformNode.h"

MeshNode::MeshNode(int uuid, aiMesh* triangleMesh, const MeshLoadInfo::LoadInfo* meshLoadInfo) : SceneNode(uuid, NodeType::MESH_NODE)
{
	this->triangleMesh = triangleMesh;
	loadInfo = meshLoadInfo;
	textureInit = false;
}


MeshNode::~MeshNode()
{
	glDeleteBuffers(1, &vertexBuffer);
	glDeleteBuffers(1, &indexBuffer);
	//glDeleteProgram(programID);
	glDeleteVertexArrays(1, &vao);
}

glm::highp_mat4 MeshNode::propagateMatrix()
{
	return parent->propagateMatrix();
}

void MeshNode::prepareForRendering()
{
	Renderer* renderer = Renderer::getInstance();
	renderer->generateVertexArray(&vao);
	renderer->generateBufferObject(&vertexBuffer);
	renderer->generateBufferObject(&indexBuffer);
	renderer->generateBufferObject(&normalBuffer);
	renderer->generateBufferObject(&uvBuffer);
	renderer->generateBufferObject(&textureBuffer);

	vertexAttribPointer = 0;
	normalAttribPointer = 1;
	textureAttribPointer = 2;

	renderer->bindVertexArray(vao);
	unsigned int* indexArray = (unsigned int*)malloc(sizeof(unsigned int)* triangleMesh->mNumFaces * 3);
	unsigned int index = 0;

	for (unsigned int t = 0; t < triangleMesh->mNumFaces; ++t)
	{
		const struct aiFace* face = &triangleMesh->mFaces[t];
		memcpy(&indexArray[index], face->mIndices, 3 * sizeof(float));
		index += 3;
	}
	renderer->fillBuffer(indexBuffer, GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int)* triangleMesh->mNumFaces * 3, indexArray, GL_STATIC_DRAW);

	if (triangleMesh->HasPositions()){
		renderer->fillBuffer(vertexBuffer, GL_ARRAY_BUFFER, sizeof(float) * 3 * triangleMesh->mNumVertices, triangleMesh->mVertices, GL_STATIC_DRAW);
		renderer->setVertexAttribPointer(vertexAttribPointer, 3, GL_FLOAT, GL_FALSE, 0, 0);
	}

	if (triangleMesh->HasNormals()){
		renderer->fillBuffer(normalBuffer, GL_ARRAY_BUFFER, sizeof(float) * 3 * triangleMesh->mNumVertices, triangleMesh->mNormals, GL_STATIC_DRAW);
		renderer->setVertexAttribPointer(normalAttribPointer, 3, GL_FLOAT, GL_FALSE, 0, 0);
	}

	float* texCoords = texCoords = (float*)malloc(sizeof(float)* 2 * triangleMesh->mNumVertices);
	if (triangleMesh->HasTextureCoords(0)){
		for (unsigned int k = 0; k < triangleMesh->mNumVertices; ++k){
			texCoords[k * 2] = triangleMesh->mTextureCoords[0][k].x;
			texCoords[k * 2 + 1] = triangleMesh->mTextureCoords[0][k].y;
		}
		renderer->fillBuffer(textureBuffer, GL_ARRAY_BUFFER, sizeof(float) * 2 * triangleMesh->mNumVertices, texCoords, GL_STATIC_DRAW);
		renderer->setVertexAttribPointer(textureAttribPointer, 2, GL_FLOAT, GL_FALSE, 0, 0);
	}

	/**/
	shaderProgram = ShaderImporter::getInstance()->loadShaderProgram(loadInfo->shaderInfo);
	shaderProgram->loadUniformLocations();
	myTexture = new Texture((loadInfo->texturePath).c_str());
	activeTexture = myTexture;
	/**/

	renderer->bindVertexArray(0);
	renderer->bindBuffer(GL_ARRAY_BUFFER, 0);
	renderer->bindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	delete indexArray;
	delete texCoords;
}


void MeshNode::draw(glm::mat4 viewMatrix, glm::mat4 projectionMatrix, glm::mat4 viewProjectionMatrix, glm::vec3 playerPosition)
{
	this->viewMatrix = viewMatrix;
	this->projectionMatrix = projectionMatrix;
	this->viewProjectionMatrix = viewProjectionMatrix;
	this->playerPosition = playerPosition;
	Renderer::getInstance()->draw(this);
}

GLuint MeshNode::getVao()
{
	return vao;
}

GLuint MeshNode::getUV()
{
	return uvBuffer;
}

int MeshNode::getDrawSize()
{
	return triangleMesh->mNumFaces * 3;
}

Texture* MeshNode::getTexture()
{
	return  activeTexture;
}

glm::mat4 MeshNode::getModelViewProjectionMatrix()
{
	return projectionMatrix * viewMatrix * glm::mat4(propagateMatrix());
}
glm::mat4 MeshNode::getViewMatrix()
{
	return viewMatrix;
}

glm::mat4 MeshNode::getProjectionMatrix()
{
	return projectionMatrix;
}

glm::mat4 MeshNode::getViewProjectionMatrix()
{
	return viewProjectionMatrix;
}

glm::mat4 MeshNode::getModelMatrix()
{
	return glm::mat4(propagateMatrix());
}

ShaderProgram* MeshNode::getShaderProgram()
{
	return shaderProgram;
}

const MeshLoadInfo::LoadInfo* MeshNode::getLoadInfo()
{
	return loadInfo;
}

glm::vec3 MeshNode::getPlayerPosition()
{
	return playerPosition;
}

void MeshNode::setLightSet(int i)
{
	lightSet = i;
}

int MeshNode::getLightSet()
{
	return lightSet;
}

void MeshNode::setActiveTexture(Texture* texture)
{
	if (texture == nullptr)
	{
		activeTexture = myTexture;
	}
	else {
		activeTexture = texture;
	}
}
