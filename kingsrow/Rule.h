#pragma once

#include <string>
#include <vector>
#include <map>

class Rule
{
public:
	Rule(std::string command, std::string rule, std::string result);
	~Rule();

	void addParam(int value) { params.push_back(value); }
	std::string process();
	char getFunction() { return function; }
	int getAttributes() { return attributes.size(); }

private:

	std::string getResult();
	int getParam(std::string currentRule);

	std::vector<char> commands{ 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H' };
	char function;
	std::string rule;
	std::string result;
	std::vector<char> insertionOrder;
	std::map<char, std::vector<std::string> >resultSegments;

	std::vector<char> attributes;
	std::vector<int> params;

};

