/* 
*	Author: Chaitanya Agrawal (krypten)
*
*	Description: 
*
*/
#include <iostream>
#include "JsonDOMParser.h"

//using namespace JsonDOM;

void JsonParser::parseJSON(TEXT jsonInput, ParseInputType inputType, JsonObject& jObject, bool& error)
{
	TEXT jString;

	error = false;
	if (inputType == ParseInputType::FILE) {
		readFile(jsonInput, jString, error);
	} else {
		jString = jsonInput;
	}

	if (jString.empty()) {
		return ;
	}
	std::cout << jString.c_str() << "\n";

	// Parsing
	unsigned int start_position = 0;

	JsonObject::JsonMap * jMap = new JsonObject::JsonMap();
	jObject.setObjectType(JsonObject::JsonObjectType::JSONMap);
	parseJsonMap(jMap, jString, start_position);
	jObject.setObject(jMap);
}

void JsonParser::parseJsonMap(JsonObject::JsonMap* currMap, TEXT jString, unsigned int& start_pos)
{
	TEXT key;
	JsonValue jValue;
	unsigned int end_pos;
	unsigned int intial_pos = 0;
	unsigned int closing_key_pos;

	getFirstPosition(jString, '{', start_pos, end_pos);
	getNotFirstPosition(jString.substr(end_pos), ' ', start_pos);

	closing_key_pos = jString.substr(end_pos + start_pos).find_first_of(':');
	key = jString.substr(start_pos + end_pos, closing_key_pos);
	std::cout << key << "\n";

	closing_key_pos = closing_key_pos + start_pos + end_pos + 1;
	parseJsonValue(jValue, jString.substr(closing_key_pos), intial_pos);
	JsonObject::assignMap(currMap, key, jValue);

	start_pos = closing_key_pos + intial_pos;
	start_pos += jString.substr(start_pos).find_first_of("}");
	++start_pos;
}

void JsonParser::parseJsonValue(JsonValue& jValue, TEXT jString, unsigned int& start_pos)
{
	unsigned int intial_pos = 0;
	getNotFirstPosition(jString.substr(start_pos), ' ', intial_pos);
	start_pos += intial_pos;
	intial_pos = 0;

	if (jString[start_pos] == '[') {

		JsonObject *jObject = new JsonObject();
		JsonObject::JsonArray * jArray = new JsonObject::JsonArray();
		jObject->setObjectType(JsonObject::JsonObjectType::JSONArray);
		
		parseJsonArray(jArray, jString.substr(start_pos), intial_pos);
		jObject->setObject(jArray);
		jValue.setValue(jObject);

	} else if (jString[start_pos] == '{')  {
		JsonObject *jObject = new JsonObject();
		JsonObject::JsonMap * jMap = new JsonObject::JsonMap();
		jObject->setObjectType(JsonObject::JsonObjectType::JSONMap);
		
		parseJsonMap(jMap, jString.substr(start_pos), intial_pos);
		jObject->setObject(jMap);
		jValue.setValue(jObject);

	} else if (jString[start_pos] == '\"') {
		// parse string
		intial_pos = jString.substr(start_pos + 1).find_first_of("\"") + 2;
		std::string * jStr = new std::string(jString.substr(start_pos + 1, intial_pos - 2));
		jValue.setValue(jStr);

	} else if (jString[start_pos] == 'n' &&  jString.substr(start_pos, 4).compare("null") == 0) {
		// parse null
		intial_pos = 5;
		jValue.setValue("");

	} else if (jString[start_pos] == 't' || jString[start_pos] == 'f') {
		// parse boolean
		if (jString.substr(start_pos, 4).compare("true") == 0) {
			intial_pos = 5;
			jValue.setValue(true);
		} else if (jString.substr(start_pos, 5).compare("false") == 0) {
			intial_pos = 6;
			jValue.setValue(false);
		}

	} else if ('0' <= jString[start_pos] && jString[start_pos] <= '9') {
		//parse number
		parseJsonNumber(jValue, jString.substr(start_pos) , intial_pos);

	} else {
		return ;
	}

	std::cout << "Value : " << jString.substr(start_pos, intial_pos) << "\n";
	start_pos += intial_pos; 
}

void JsonParser::parseJsonArray(JsonObject::JsonArray* currArray, TEXT jString, unsigned int& start_pos)
{
	JsonValue jValue;
	unsigned int intial_pos = 0;
	while (true) {
		
		start_pos += jString.substr(start_pos).find_first_of('[');

		parseJsonValue(jValue, jString.substr(start_pos + 1), intial_pos);
		JsonObject::assignArray(currArray, jValue);

		start_pos += intial_pos + 1;

		intial_pos = 0;
		getNotFirstPosition(jString.substr(start_pos), ' ', intial_pos);
		start_pos += intial_pos;

		if (jString.substr(start_pos)[0] == ',') {
			++start_pos;
			continue;
		} else if (jString.substr(start_pos)[0] == ']'){
			++start_pos;
			break;
		}
	}
}

void JsonParser::parseJsonNumber(JsonValue& jValue, TEXT jNumber, unsigned int& start_pos)
{
	int numInt = 0;
	unsigned int pos = start_pos;
	double numDouble = 0.0;
	bool fDouble = false;

	while (isDigit(jNumber[start_pos])) {
		numInt = numInt * 10 + toDigit(jNumber[start_pos++]);
	}
	if (jNumber[start_pos] == '.') {
		fDouble = true;
		start_pos += 1;
	}
	if (fDouble) {
		while (isDigit(jNumber[start_pos++]));
		numDouble = std::stod(jNumber.substr(pos, start_pos).c_str());
		std::cout << numDouble << "\n";
		jValue.setValue(numDouble);
	} else {
		std::cout << numInt << "\n";
		jValue.setValue(numInt);
		
	}
}
