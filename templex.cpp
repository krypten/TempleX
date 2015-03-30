#include <iostream>

#include "Parser/JSON/JsonDOMParser.h"
#include "Parser/XML/XmlDOMParser.h"
#include "Parser/ConvertUtil.h"

int main()
{
	bool error;
	Node node;
	Node *child = new Node();
	node.setNodeName("ROOT");
	child->setNodeName("CHILD");
	node.addChild(child);
	node.getFirstChild()->setAttribute("version", "asdf");
	std::cout << node.getLastChild()->getAttribute("version") << "\n";

	//ConvertUtil::convertXML2JSON("Data/demo.json", Parser::ParseInputType::FILE, node, error);
	ConvertUtil::convertJSON2XML("Data/demo.json", Parser::ParseInputType::FILE, node, error);

	JsonObject jObject;
	std::cout << node.getLastChild()->getNodeName() << "\n";
	JsonObject::JsonMap jMap;

	jObject.getObject(jMap, error);
	std::cout << jMap.first << "\n";

	return 0;
}
