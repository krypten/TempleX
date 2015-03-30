/*
*	Author: Chaitanya Agrawal (krypten)
*
*	Description:
*
*/
#include <iostream>
#include "XmlDOMParser.h"

//using namespace XmlDOM;

void XmlParser::parseXML(TEXT xmlInput, ParseInputType inputType, Node& outNode, bool& error)
{
	TEXT xmlString;

	error = false;
	if (inputType == ParseInputType::FILE) {
		readFile(xmlInput, xmlString, error);
	} else {
		xmlString = xmlInput;
	}

	if (xmlString.empty()) {
		return ;
	}
	std::cout << xmlString << "\n";

	unsigned int start_pos = 0;
	// Parsing
	// parseXMLNode(outNode, xmlString, start_pos);
	std::cout << "NEXT NODE \n";
	parseXMLNode(outNode, xmlString, start_pos);
}

void XmlParser::parseXMLNode(Node &currNode, TEXT xmlString, unsigned int& start_pos)
{
	TEXT tag;
	unsigned int initial_pos = 0;
	unsigned int end_pos;
	unsigned int closing_start_pos;
	//Node *child = new Node();

	while(start_pos < xmlString.size() - 1) {
		start_pos = xmlString.find_first_of('<', start_pos);
		end_pos = xmlString.find_first_of('>', start_pos);

		tag = xmlString.substr(start_pos + 1, end_pos - start_pos);

		if (xmlString[start_pos + 1] == '/') {
			start_pos = end_pos;
			return ;
		}

		setTagValue(currNode, tag);

		start_pos = end_pos;// + 1;

		if (xmlString[end_pos - 1] == '/' || xmlString[end_pos - 1] == '?') {
			continue;
		}

		closing_start_pos = xmlString.find_first_of("<", start_pos);

		if (xmlString.at(closing_start_pos + 1) != '/') {
			// new
			Node *child = new Node();
			parseXMLNode(*child, xmlString.substr(closing_start_pos), initial_pos);
			currNode.addChild(child);
			start_pos = closing_start_pos + initial_pos;
		} else if (end_pos != (closing_start_pos -1)) {
			Node *child = new Node();
			child->setData(xmlString.substr(end_pos, closing_start_pos - end_pos));
			currNode.addChild(child);
			start_pos = closing_start_pos + 1;
		}
	}
}

void XmlParser::setTagValue(Node &currNode, TEXT tag)
{
	unsigned int start_pos;
	unsigned int end_pos;

	// node name
	getFirstPosition(tag, ' ', start_pos, end_pos);
	currNode.setNodeName(tag.substr(0,start_pos));
	std::cout << currNode.getNodeName() << "\n";

	// attributes
	tag = tag.substr(end_pos);
	getNotFirstPosition(tag.substr(end_pos), ' ', end_pos);
	tag = tag.substr(end_pos);
	while (!tag.empty() && tag.compare(">") && tag.compare("/>")) {
		getFirstPosition(tag, ' ', start_pos, end_pos);
		setAttributeValue(currNode, tag.substr(0, start_pos));

		tag = tag.substr(end_pos);
	}
}

void XmlParser::setAttributeValue(Node &currNode, TEXT attribute)
{
	unsigned int end_position = attribute.find_first_of("=");
	if (end_position == TEXT::npos) {
		end_position = attribute.size() - 1;
	}

	currNode.setAttribute(attribute.substr(0,end_position), attribute.substr(end_position + 1));

	std::cout << attribute.substr(0,end_position) << " " <<  attribute.substr(end_position + 1)  << "\n";
}
