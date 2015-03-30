/*
*	Author: Chaitanya Agrawal (krypten)
*
*	Description:
*
*/

#ifndef Convert_UTIL_H_
#define Convert_UTIL_H_

#include <string>

#include "Model/Model.h"
#include "XML/XmlDOMNode.h"
#include "JSON/JsonDOMObject.h"

#include "Parser.h"

class ConvertUtil {

private:

	static void convertModel2XML(Model model, Node& outNode, bool& error);
	static void convertXML2Model(Node xmlInput, Model model, bool& error);
	static void convertModel2JSON(Model model, JsonObject& outNode, bool& error);
	static void convertJSON2Model(JsonObject jsonInput, Model& model, bool& error);

	static Attribute model2Attributes(Model model, bool& error);
	static Model attributes2Model(Attribute attributes);
	static void modelValue2XMLNode(Model model, Node& outNode, bool& error);
	static void jsonValue2Model(JsonValue value, Model& iModel, bool& error);

public:
	// Utility function for converting XML to JSON
	static void convertXML2JSON(TEXT xmlInput, Parser::ParseInputType inputType, JsonObject& outNode, bool& error);
	// Utility function for converting JSON to XML
	static void convertJSON2XML(TEXT jsonInput, Parser::ParseInputType inputType, Node& outNode, bool& error);
};

#endif // Convert_UTIL_H_
