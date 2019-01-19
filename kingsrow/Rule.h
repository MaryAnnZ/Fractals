#pragma once

#include <string>
#include <vector>

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
	char function;
	std::string rule;
	std::string result;

	std::vector<char> attributes;
	std::vector<int> params;

};

