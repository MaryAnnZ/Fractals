#include "Rule.h"


           //A(x,y)             y<=3              A(x*1,x+y)
Rule::Rule(std::string command, std::string rule, std::string result)
{
	function = command.at(0);
	//std::size_t startIndexAttributes = command.find("(");
	//std::size_t endIndexAttributes = command.find(")");
	std::string rawAttributes = command.substr(command.find("("));
	for (unsigned int i = 0; i < rawAttributes.size(); ++i) {
		if (i % 2 == 1) {
			attributes.push_back(rawAttributes.at(i));
		}
	} 
	this->rule = rule;
	this->result = result;
}


Rule::~Rule()
{
}

std::string Rule::process()
{

	params.clear();
	return std::string();
}
