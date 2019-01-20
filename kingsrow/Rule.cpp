#include "Rule.h"
#include <ctype.h>
#include <sstream>


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

	if (result.length() > 3) {
		for (unsigned int i = 0; i < result.length(); i++) {
			if (std::find(commands.begin(), commands.end(), result.at(i)) != commands.end()) {
				if (i < result.length() - 1) {
					if (result.at(i + 1) == '(') {
						for (unsigned int a = i; a < result.length(); a++) { //find ')'
							if (result.at(a) == ')') {
								std::stringstream resultArgs;
								resultArgs.str(result.substr(i + 2, a - (i + 2))); // get the part between ()
								std::string segment;
								std::vector<std::string> subsegments;
								while (std::getline(resultArgs, segment, ','))
								{
									subsegments.push_back(segment);
								}
								insertionOrder.push_back(result.at(i));
								resultSegments[result.at(i)] = subsegments;
								i = a;
								break;
							}
						}
					}
					else {//this function has no attributes
						insertionOrder.push_back(result.at(i));
						resultSegments[result.at(i)] = std::vector<std::string>();
					}
				}
				else { //this is the last element without attributes
					insertionOrder.push_back(result.at(i));
					resultSegments[result.at(i)] = std::vector<std::string>();
				}
			}
		}
		
	}
}


Rule::~Rule()
{
}

//= != < > <= >= ! (U A)
std::string Rule::process()
{
	std::string result = "";
	bool not = false;
	std::string currentRule = rule;
	if ( currentRule.at(0) == '!') { // !(x=y)
		not = true;
		currentRule = currentRule.substr(2, currentRule.length() - 3); //cut ! and ()
	}

	//rule is in form x (operator) y
	//				  x (operator) number	
	int indexAttribute = std::find(attributes.begin(), attributes.end(), currentRule.at(0)) - attributes.begin();
	int firstparam = params.at(indexAttribute);
	currentRule = currentRule.substr(1); // first attribute is cut
	int secondParam;
	//parse operator
	char operatorFirstPart = currentRule.at(0);
	currentRule = currentRule.substr(1);
	switch (operatorFirstPart)
	{
	case '=': { 
		secondParam = getParam(currentRule);
		if (not) {
			if (firstparam != secondParam) {
				result = getResult();
			}
		}
		else if (firstparam == secondParam) {
			result = getResult();
		}
		break;
	}
	case '!': { // second part MUST be =
		if (currentRule.at(0) != '=') {
			result = "";
		}
		currentRule = currentRule.substr(1);
		secondParam = getParam(currentRule);
		if (not) {
			if (firstparam == secondParam) {
				result = getResult();
			}
		} else if (firstparam != secondParam) {
			result = getResult();
		}
		break;
	}
	case '<': { // second part could be =
		if (currentRule.at(0) == '=') {
			currentRule = currentRule.substr(1);
			secondParam = getParam(currentRule);
			if (not) {
				if (firstparam > secondParam) {
					result = getResult();
				}
			} else if (firstparam <= secondParam) {
				result = getResult();
			}
		} else {
			secondParam = getParam(currentRule);
			if (not) {
				if (firstparam >= secondParam) {
					result = getResult();
				}
			} else if (firstparam < secondParam) {
				result = getResult();
			}
		}
		break;
	}
	case '>': { // second part could be =
		if (currentRule.at(0) == '=') {
			currentRule = currentRule.substr(1);
			secondParam = getParam(currentRule);
			if (not) {
				if (firstparam < secondParam) {
					result = getResult();
				}
			} else if (firstparam >= secondParam) {
				result = getResult();
			}
		}
		else {
			secondParam = getParam(currentRule);
			if (not) {
				if (firstparam <= secondParam) {
					result = getResult();
				}
			} else if (firstparam > secondParam) {
				result = getResult();
			}
		}
		break;
	} 
	default:
		break;
	}
	params.clear();
	return result;
}

//A(x*1,x+y) A(x*1,x+y) A   
std::string Rule::getResult()
{
	if (result.length() <= 3) {
		return result;
	}
	
	std::string returnVal = "";
	// + - * /
	for (char c : insertionOrder) {
		returnVal.append(std::string(1, c));
		std::vector<std::string> segments = resultSegments[c];
		for (unsigned int i = 0; i < segments.size(); i++) {
			if (i == 0) {
				returnVal.append("(");
			}
			std::string currentSegment = segments.at(i);

			std::size_t foundPlus = currentSegment.find("+");
			std::size_t foundMinus = currentSegment.find("-");
			std::size_t foundMul = currentSegment.find("*");
			std::size_t foundDiv = currentSegment.find("/");
			if (foundPlus != std::string::npos) {
				std::string firstAttr = currentSegment.substr(0, foundPlus);
				std::string secondAttr = currentSegment.substr(foundPlus + 1);
				int firstparam = getParam(firstAttr);
				int secondparam = getParam(secondAttr);
				int res = firstparam + secondparam;
				returnVal.append(std::to_string(res));
			}
			else if (foundMinus != std::string::npos) {
				std::string firstAttr = currentSegment.substr(0, foundMinus);
				std::string secondAttr = currentSegment.substr(foundMinus + 1);
				int firstparam = getParam(firstAttr);
				int secondparam = getParam(secondAttr);
				int res = firstparam - secondparam;
				returnVal.append(std::to_string(res));

			}
			else if (foundMul != std::string::npos) {
				std::string firstAttr = currentSegment.substr(0, foundMul);
				std::string secondAttr = currentSegment.substr(foundMul + 1);
				int firstparam = getParam(firstAttr);
				int secondparam = getParam(secondAttr);
				int res = firstparam * secondparam;
				returnVal.append(std::to_string(res));
			}
			else if (foundDiv != std::string::npos) {
				std::string firstAttr = currentSegment.substr(0, foundDiv);
				std::string secondAttr = currentSegment.substr(foundDiv + 1);
				int firstparam = getParam(firstAttr);
				int secondparam = getParam(secondAttr);
				int res = firstparam / secondparam;
				returnVal.append(std::to_string(res));
			}
			else { //if there is no operator, it should be an attribute
				returnVal.append(std::to_string(getParam(currentSegment)));
			}
			if (i < segments.size() - 1) {
				returnVal.append(",");
			}
			else {
				returnVal.append(")");
			}
		}
	}
	return returnVal;
}

int Rule::getParam(std::string currentRule)
{	
	bool letter = false;
	for (int i = 0; i < currentRule.length(); ++i) {
		if (isalpha(currentRule.at(i))) {
			letter = true;
			break;
		}
	}
	if (letter) {
		//if it is a letter it should have the length 1
		return params.at(std::find(attributes.begin(), attributes.end(), currentRule.at(0)) - attributes.begin());
	}
	else {
		return std::stoi(currentRule);
	};
}
