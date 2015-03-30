# TempleX
---------

## Introduction
	This is project currently converting XML file or input to JSON format and vice versa.

## Working Code

	- Utility function for converting JSON to XML
	ConvertUtil::convertXML2JSON(TEXT xmlInput, Parser::ParseInputType inputType, JsonObject& outNode, bool& error);

	- Utility function for converting JSON to XML
	ConvertUtil::convertJSON2XML(TEXT jsonInput, Parser::ParseInputType inputType, Node& outNode, bool& error);

	For Example :
		bool error;
		Node node;
		ConvertUtil::convertJSON2XML("Data/demo.json", Parser::ParseInputType::FILE, node, error);


## Futute Work
	The intial aim of the project was to create dynamic OpenGL objects using popular file formats. This will make the process of creating OpenGL objects every easy. Intial draft has to use svg and json format and create OpenGL objects based on the data provided as input.

## ToDo

	Testing the functionality of XML to Model and Model to XML.
	Testing the functionality of JSON to Model and Model to JSON.

	Printing the XML and JSON [converting to Strings / toString() function]

	Error Handling to be supported by code.

	FIX :
		fix parsing map for multiple values.
		fix create output files in build folder
		Map or pair to be used in JsonMap ;;;;;; to be decided.
