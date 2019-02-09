#pragma once

#include <string>
#include <vector>
#include <map>

class Rule
{
public:
	/*
	command: turtle command
	rule: conditions
	result: output if the condition(s) are true
	*/
	Rule(std::string command, std::string rule, std::string result);
	~Rule();

	void addParam(float value) { params.push_back(value); }
	std::string process();
	char getFunction() { return function; }
	int getAttributes() { return attributes.size(); }

private:

	std::string getResult();
	float getParam(std::string currentRule);
	bool processRulePart(std::string rulePart);

	std::vector<char> commands{ 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H' };
	char function;
	std::string rule;
	//conditions which are connected with AND
	std::vector<std::string> andRules;
	//conditions which are connected with OR
	std::vector<std::string> orRules;
	std::string result;
	std::vector<char> insertionOrder;
	std::map<char, std::vector<std::string> >resultSegments;

	//the variables of the commands
	std::vector<char> attributes;
	//the values of the variables of a specific command
	std::vector<float> params;

};

