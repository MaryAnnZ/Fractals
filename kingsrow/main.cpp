#include <glad/glad.h>

#include <GLFW/glfw3.h>
//#include <GL\glew.h>
#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>
#include <math.h>


#include <stdio.h>
#include <stdlib.h>
#include <GLFW\glfw3.h>
#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <map>
#include <sstream>
#include <fstream>

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
#include "Rule.h"

#define PI 3.14159265
#define ITERATIONS 5

std::string w;
SceneNode* sceneGraph;
std::vector<MeshNode*> drawArray;
std::vector<glm::mat4> transformationsStack;
glm::mat4 turtlePosition =  glm::mat4(
	1, 0, 0, 0,
	0, 1, 0, 0,
	0, 0, 1, 0,
	0, 0, 0, 1);
std::vector<Rule> rules;
std::vector<char> commands{ 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H' };

void createCylinder(int length, float radius, bool col = true);
void translateH(float length);
void rotateU(float angle);
void rotateR(float angle);
void rotateH(float angle);
void turn();
void saveTransformation();
void resetTransformation();
void printMatrix(glm::mat4 matrix);
void callFunction(char function, float attr1, float attr2);
void iterateW();


int main() {

	int viewPortResX = 1024;
	int viewPortResY = 756;
	Renderer* renderer = Renderer::getInstance();
	if (renderer->init(viewPortResX, viewPortResY) == -1) {
		return -1;
	}

	InputHandler* input = new InputHandler();

	sceneGraph = new SceneNode(generateUuid(), NodeType::ROOT_NODE);
	sceneGraph->setParent(nullptr);

	//Texture* rainbowTexture = new Texture("../kingsrow/Assets/Models/duck_textures/rainbow.jpg");

	std::map<std::string, CameraNode*> cameraList;

	//start of part that should be in a scene loader
	CameraNode* activeCamera = new CameraNode(generateUuid(), viewPortResX, viewPortResY);


	//this way we have a list of cameras and can switch between them as we want just by doing activeCamera = cameraList.find("whichever camera we want")->second;
	cameraList.insert(std::pair<std::string, CameraNode*>(std::string("player camera"), activeCamera));


	std::vector<LightNode*> lights1;
	//room 1
	LightNode* firstLight = new PointLightNode(generateUuid(), glm::vec3(0, 2, 0), 10.0f, glm::vec3(1, 1, 1), LightType::POINT_LIGHT);
	lights1.push_back(firstLight);
	renderer->setLights(lights1);

	std::ifstream inputFile("../kingsrow/Assets/first.txt");
	std::string line;
	int countLines = 0;
	while (std::getline(inputFile, line)) {
		if (countLines == 0) { // first string
			w = line;
		}
		else { // rules
			//A(x, y) :y <= 3#A(x * 1, x + y)
			std::size_t loc1 = line.find(":");
			std::size_t loc2 = line.find("#");
			std::string command = line.substr(0,  loc1);
			std::string comparison = line.substr(loc1 + 1, loc2 - (loc1 + 1));
			std::string result = line.substr(loc2 + 1);
			Rule rule = Rule(command, comparison, result);
			rules.push_back(rule);
		}
		countLines++;
	}
	/* Alphabet
	A - Create
	B - TranslateH
	C - RotateU
	D - RotateR
	E - RotateH
	F - Turn
	G - [
	H - ]
	*/
	std::cout << w << std::endl;
	for (int i = 0; i < ITERATIONS; i++) {
		iterateW();
		std::cout << w << std::endl;
	}
	

	//createCylinder(1, 1);
	//rotateU(90);
	//rotateR(90);
	//createCylinder(1, 1, false);
	//saveTransformation();
	//createCylinder(2, 1);
	//rotateH(90);
	//createCylinder(1, 1);
	//resetTransformation();
	//rotateH(90);
	//createCylinder(1, 1, false);
	//translateH(2);
	//createCylinder(1, 1);


	//createCylinder(1, 1);
	//createCylinder(2, 2, false);
	//createCylinder(2, 1, false);
	//createCylinder(1, 1);

	MeshNode* cylinderMesh = MeshImporter::getInstance()->getMesh(MeshLoadInfo::CYLINDER);
	MeshNode* xMesh = MeshImporter::getInstance()->getMesh(MeshLoadInfo::CYLINDERX);
	MeshNode* yMesh = MeshImporter::getInstance()->getMesh(MeshLoadInfo::CYLINDERY);
	MeshNode* zMesh = MeshImporter::getInstance()->getMesh(MeshLoadInfo::CYLINDERZ);

	cylinderMesh->prepareForRendering();
	xMesh->prepareForRendering();
	yMesh->prepareForRendering();
	zMesh->prepareForRendering();

	drawArray.push_back(cylinderMesh);
	drawArray.push_back(xMesh);
	drawArray.push_back(yMesh);
	drawArray.push_back(zMesh);

	SceneNode* transformNodeCylinder = new TransformNode(generateUuid(), glm::mat4(
		1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, 1, 0,
		6, 0, 1, 1));
	//SceneNode* rotateY = new TransformNode(generateUuid(), glm::mat4(
	//	cos(90 *PI / 180),0, sin(90 * PI / 180), 0,
	//	0, 1, 0, 0,
	//	-sin(90 * PI / 180), 0, cos(90 * PI / 180), 0,
	//	0, 0, 0, 1));
	//SceneNode* rotateY2 = new TransformNode(generateUuid(), glm::mat4(
	//	cos(90 * PI / 180), 0, sin(90 * PI / 180), 0,
	//	0, 1, 0, 0,
	//	-sin(90 * PI / 180), 0, cos(90 * PI / 180), 0,
	//	0, 0, 0, 1));
	//SceneNode* rotateX = new TransformNode(generateUuid(), glm::mat4(
	//	1, 0, 0, 0,
	//	0, cos(90 * PI / 180), -sin(90 * PI / 180), 0,
	//	0, sin(90 * PI / 180), cos(90 * PI / 180), 0,
	//	0, 0, 0, 1));
	//SceneNode* scale = new TransformNode(generateUuid(), glm::mat4(
	//	2, 0, 0, 0,
	//	0, 1, 0, 0,
	//	0, 0, 1, 0,
	//	0, 0, 0, 1));
	SceneNode* transformNodeX = new TransformNode(generateUuid(), glm::mat4(
		1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, 1, 0,
		8, 0, 1, 1));
	//SceneNode* transformNodeX2 = new TransformNode(generateUuid(), glm::mat4(
	//	1, 0, 0, 0,
	//	0, 1, 0, 0,
	//	0, 0, 1, 0,
	//	1, 0, 0, 1));
	SceneNode* transformNodeY = new TransformNode(generateUuid(), glm::mat4(
		1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, 1, 0,
		10, 0, 1, 1));
	SceneNode* transformNodeZ = new TransformNode(generateUuid(), glm::mat4(
		1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, 1, 0,
		12, 0, 1, 1));
	
	//rotateY->attachChild(transformNodeCylinder);
	////rotateX->attachChild(rotateY);
	//transformNodeX2->attachChild(scale);
	//scale->attachChild(xMesh);
	//rotateY2->attachChild(transformNodeX2);
	transformNodeCylinder->attachChild(cylinderMesh);
	transformNodeX->attachChild(xMesh);
	transformNodeY->attachChild(yMesh);
	transformNodeZ->attachChild(zMesh);
	sceneGraph->attachChild(transformNodeCylinder);
	sceneGraph->attachChild(transformNodeX);
	sceneGraph->attachChild(transformNodeY);
	sceneGraph->attachChild(transformNodeZ);

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

void createCylinder(int length, float radius, bool col)
{
	if (length == 0 || radius == 0) {
		return;
	}
	//radius = 1;
	while (length > 0) {
		MeshNode* mesh = 0;
		if (col) {
			mesh = MeshImporter::getInstance()->getMesh(MeshLoadInfo::CYLINDER);
		}
		else {
			mesh = MeshImporter::getInstance()->getMesh(MeshLoadInfo::CYLINDERZ);
		}
		mesh->prepareForRendering();
		drawArray.push_back(mesh);

		SceneNode* meshTransform = new TransformNode(generateUuid(), glm::mat4(
			1.0, 0.0, 0.0, 0.0,
			0.0, radius, 0.0, 0.0,
			0.0, 0.0, radius, 0.0,
			0.0, 0.0, 0.0, 1.0));

		SceneNode* turtleTransform = new TransformNode(generateUuid(), glm::mat4(
			turtlePosition));
		
		turtlePosition = glm::translate(turtlePosition, glm::vec3(1, 0, 0));

		meshTransform->attachChild(mesh);
		turtleTransform->attachChild(meshTransform);
		sceneGraph->attachChild(turtleTransform);
		length--;
	}

}

void translateH(float length)
{
	turtlePosition = glm::translate(turtlePosition, glm::vec3(length, 0, 0));
}

void rotateU(float angle)
{
	if (angle == 0) {
		angle = 90;
	}
	turtlePosition = glm::rotate(turtlePosition, (float)angle, glm::vec3(turtlePosition[0][1], turtlePosition[1][1], turtlePosition[2][1]));
}

void rotateR(float angle)
{
	turtlePosition = glm::rotate(turtlePosition, (float)angle, glm::vec3(turtlePosition[0][0], turtlePosition[1][0], turtlePosition[2][0]));
}

void rotateH(float angle)
{
	turtlePosition = glm::rotate(turtlePosition, (float)angle, glm::vec3(turtlePosition[0][2], turtlePosition[1][2], turtlePosition[2][2]));
}

void turn()
{
	rotateH(180);
}

void saveTransformation()
{
	transformationsStack.push_back(glm::mat4(turtlePosition));
}

void resetTransformation()
{
	if (transformationsStack.size() == 0) {
		std::cout << "Transformation stack is empty, there is nothing to return to" << std::endl;
		return;
	}
	turtlePosition = transformationsStack.back();
	transformationsStack.pop_back();
}

void printMatrix(glm::mat4 matrix)
{
	std::cout << matrix[0][0] << matrix[0][1] << matrix[0][2] << matrix[0][3] << std::endl;
	std::cout << matrix[1][0] << matrix[1][1] << matrix[1][2] << matrix[1][3] << std::endl;
	std::cout << matrix[2][0] << matrix[2][1] << matrix[2][2] << matrix[2][3] << std::endl;
	std::cout << matrix[3][0] << matrix[3][1] << matrix[3][2] << matrix[3][3] << std::endl;
}

void callFunction(char function, float attr1, float attr2)
{
	/* Alphabet
	A - Create
	B - TranslateH
	C - RotateU
	D - RotateR
	E - RotateH
	F - Turn
	G - [
	H - ]
	*/
	switch (function)
	{
	case 'A': {
		std::cout << "Create" << std::endl;
		createCylinder(static_cast<int>(attr1), attr2);
		break;
	}
	case 'B': {
		std::cout << "Translate" << std::endl;
		translateH(attr1);
		break;
	}
	case 'C':{
		std::cout << "RotateU" << std::endl;
		rotateU(attr1);
		break;
	}
	case 'D':{
		std::cout << "RotateR" << std::endl;
		rotateR(attr1);
		break;
	}
	case 'E':{
		std::cout << "RotateH" << std::endl;
		rotateH(attr1);
		break;
		}
	case 'F': {
		std::cout << "Turn" << std::endl;
		turn();
		break;
	}
	case 'G':{
		std::cout << "save" << std::endl;
		saveTransformation();
		break;
		}
	case 'H':{
		std::cout << "restore" << std::endl;
		resetTransformation();
		break;
		}
	}
}

void iterateW()
{
	std::string updateW = "";
	char function;
	std::vector<float> attributes;
	for (unsigned int i = 0; i < w.length(); i++) {
		char currFunction = w.at(i);
		if (std::find(commands.begin(), commands.end(), currFunction) != commands.end()) { // function found!
			function = currFunction;
			attributes.clear();
			if (i < w.length() - 1) { // it is not the last element
				if (w.at(i + 1) == '(') { // list of attributes
					for (unsigned int a = i + 1; a < w.length(); a++) { //find the next ')'
						if (w.at(a) == ')') {
							std::string attrString = w.substr(i + 2, a - (i + 2)); // get string between ()
							std::stringstream sstream;
							sstream.str(attrString);
							std::string currAttr;
							while (std::getline(sstream, currAttr, ','))
							{
								attributes.push_back(std::atof(currAttr.c_str()));
							}
							//all functions and Attributes are found
							//call turtle function
							if (attributes.size() > 1) {
								callFunction(function, attributes[0], attributes[1]);
							}
							else if (attributes.size() == 1) {
								callFunction(function, attributes[0], 0.0);
							}
							else {
								callFunction(function, 0.0, 0.0);
							}
							//update w according to the rules
							bool ruleFound = false;
							for (Rule rule : rules) {
								if (rule.getFunction() == function && rule.getAttributes() == attributes.size()) { // matching rule found!
									for (int attr : attributes) {
										rule.addParam(attr);
									}
									std::string ruleOutput = rule.process();
									if (!ruleOutput.empty()) { // conditions are ok
										ruleFound = true;
										updateW.append(ruleOutput);
										break;
									}
								}
							}
							if (!ruleFound) { // no rule is satisfied so keep  the function 
								updateW.append(std::string(1, function));
								if (attributes.size() > 0) {
									updateW.append("(");
									for (int attrIndex = 0; attrIndex < attributes.size(); attrIndex++) {
										updateW.append(std::to_string(attributes[attrIndex]));
										if (attrIndex < attrIndex < attributes.size() - 1) {
											updateW.append(",");
										}
										else {
											updateW.append(")");
										}
									}
								}
							}
							i = a; // skip to the end of attributes;
							break;
						}
					}
				}
				else { //the function has no attributes
					callFunction(function, 0.0, 0.0);
					updateW.append(std::string(1, function));
				}
			}
			else { // it is the last element without attributes
				callFunction(function, 0.0, 0.0);
				updateW.append(std::string(1, function));
			}
		}
	}
	w = updateW;
}
