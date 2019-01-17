#include <glad/glad.h>

#include <GLFW/glfw3.h>
//#include <GL\glew.h>
#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>


#include <stdio.h>
#include <stdlib.h>
#include <GLFW\glfw3.h>
#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <map>
#include <sstream>

#include "InputHandler.h"
#include "Render\Renderer.h"
#include "Util\UuidHelper.h"
#include "Importers\MeshImporter.h"
#include "SceneGraph\TransformNode.h"
#include "SceneGraph\LightNode\LightsEnum.h"
#include "SceneGraph\CameraNode.h"
#include "SceneGraph\PlayerNode.h"
#include "SceneGraph\LightNode\PointLightNode.h"
#include "SceneGraph\LightNode\DirectionalLightNode.h"
#include "SceneGraph\LightNode\SpotLightNode.h"
#include "Texture\SamplerStateEnum.h"
#include "Texture\MipmapStateEnum.h"


int main() {

	int viewPortResX = 1024;
	int viewPortResY = 756;
	Renderer* renderer = Renderer::getInstance();
	if (renderer->init(viewPortResX, viewPortResY) == -1) {
		return -1;
	}

	InputHandler* input = new InputHandler();


	//Texture* rainbowTexture = new Texture("../kingsrow/Assets/Models/duck_textures/rainbow.jpg");

	std::map<std::string, CameraNode*> cameraList;

	//start of part that should be in a scene loader
	CameraNode* activeCamera = new CameraNode(generateUuid(), viewPortResX, viewPortResY);


	//this way we have a list of cameras and can switch between them as we want just by doing activeCamera = cameraList.find("whichever camera we want")->second;
	cameraList.insert(std::pair<std::string, CameraNode*>(std::string("player camera"), activeCamera));


	std::vector<LightNode*> lights1;
	//room 1
	LightNode* firstLight = new PointLightNode(generateUuid(), glm::vec3(0, 2, 0), 1.0f, glm::vec3(1, 1, 1), LightType::POINT_LIGHT);

	lights1.push_back(firstLight);

	renderer->setLights(lights1);

	MeshNode* tableMesh = MeshImporter::getInstance()->getMesh(MeshLoadInfo::CYLINDER);

	tableMesh->prepareForRendering();

	std::vector<MeshNode*> drawArray;
	drawArray.push_back(tableMesh);

	SceneNode* sceneGraph = new SceneNode(generateUuid(), NodeType::ROOT_NODE);
	sceneGraph->setParent(nullptr);


	SceneNode* transformNodeTable = new TransformNode(generateUuid(), glm::mat4(
		1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, 1, 0,
		0, 0, 0, 1));
	
	transformNodeTable->attachChild(tableMesh);
	sceneGraph->attachChild(transformNodeTable);

	SceneNode* playerTransform = new TransformNode(generateUuid(), glm::mat4(
		1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, 1, 0,
		0, 0, 0, 1));

	PlayerNode* player = new PlayerNode(generateUuid());
	player->setCamera(activeCamera);
	playerTransform->attachChild(activeCamera);
	playerTransform->attachChild(player);
	sceneGraph->attachChild(playerTransform);

	//should probably done recursively in sceneNode		

	//end of part that should be in a scene loader

	double time = glfwGetTime();
	double oldTime = glfwGetTime();
	double timeStep = 1.0 / 60.0;
	double timeOld = 0;

	//gameloop
	while (!input->esc && glfwWindowShouldClose(renderer->getWindow()) == 0) {
		input->update(renderer->getWindow());

		glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

		time = glfwGetTime();
		double deltaTime = time - oldTime;
		while (deltaTime > timeStep)
		{
			deltaTime -= timeStep;
			sceneGraph->update(timeStep, input);
		}
		oldTime = time - deltaTime;

		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		


		glm::mat4 projectionMatrix = activeCamera->getProjectionMatrix();
		glm::mat4 viewMatrix = activeCamera->getViewMatrix();
		glm::mat4 viewProjectionMatrix = projectionMatrix * viewMatrix;
		glm::vec3 playerPosition = glm::vec3(glm::inverse(viewMatrix)[0][3], glm::inverse(viewMatrix)[1][3], glm::inverse(viewMatrix)[2][3]);

		//draw meshes
		for (MeshNode* node : drawArray) {
			//-------------draw-------------------
			node->draw(viewMatrix, projectionMatrix, viewProjectionMatrix, player->getPosition());
		}

		glfwSwapBuffers(renderer->getWindow());
		glfwPollEvents();
	}

	glfwTerminate();

	return 0;
}


