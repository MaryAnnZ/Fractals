#pragma once

#include <string>
#include <vector>
#include <map>

class Rule
{
public:
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
	std::vector<std::string> andRules;
	std::vector<std::string> orRules;
	std::string result;
	std::vector<char> insertionOrder;
	std::map<char, std::vector<std::string> >resultSegments;

	std::vector<char> attributes;
	std::vector<float> params;

};

