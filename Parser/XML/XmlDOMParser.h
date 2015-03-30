/* 
*	Author: Chaitanya Agrawal (krypten)
*
*	Description: 
*
*/

#ifndef XmlDOM_PARSER_H_
#define XmlDOM_PARSER_H_

#include "../Parser.h"
#include  "XmlDOMNode.h"

class XmlParser : public Parser {
	private:

	public:
		void setTagValue(Node &currNode, TEXT tag);
		void setAttributeValue(Node &currNode, TEXT attribute);
		void parseXMLNode(Node &currNode, TEXT xmlString, unsigned int& start_pos);
		void parseXML(TEXT xmlInput, ParseInputType inputType, Node& outNode, bool& error);
};

#endif // XmlDOM_PARSER_H_