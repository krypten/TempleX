/* 
*	Author: Chaitanya Agrawal (krypten)
*
*	Description: 
*
*/

#include "JsonDOMObject.h"

//using namespace JsonDOM;

/*
Node::Node(Data value): 
	data(value),
	parentNode(NULL),
	lastChild(NULL),
	firstChild(NULL),
	previousSibling(NULL),
	nextSibling(NULL),
	self(this)
{
}
*/

// getter const functions
JsonObject::JsonObjectType JsonObject::getObjectType() const
{
	return objectType;
}

void JsonObject::getObject(JsonArray& jArray, bool& error) const
{
	error = false;
	if (getObjectType() == JsonObject::JSONArray) {
		jArray = *(object.jsonArray);
	} else {
		error = true;
	}
}

void JsonObject::getObject(JsonMap& jMap, bool& error) const
{
	error = false;
	if (getObjectType() == JsonObject::JSONMap) {
		jMap = *(object.jsonMap);
	} else {
		error = true;
	}
}

// setter functions
void JsonObject::setObjectType(JsonObjectType type)
{
	objectType = type;
}

void JsonObject::setObject(JsonArray* jArray)
{
	setObjectType(JsonObject::JSONArray);
	object.jsonArray = jArray;
}

void JsonObject::setObject(JsonMap* jMap)
{
	setObjectType(JsonObject::JSONMap);
	object.jsonMap = jMap;
}

void JsonObject::assignMap(JsonMap* jMap, TEXT key, JsonValue jValue)
{
	jMap->first = key;
	jMap->second = jValue;
}

void JsonObject::assignArray(JsonArray* jArray, JsonValue jValue)
{
	jArray->push_back(jValue);
}