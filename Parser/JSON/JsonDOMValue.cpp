/*
*	Author: Chaitanya Agrawal (krypten)
*
*	Description:
*
*/

#include "JsonDOMValue.h"

//using namespace JsonDOM;

// getter const functions
JsonValue::JsonValue()
{

}

JsonValue::JsonValueType JsonValue::getValueType() const
{
	return valueType;
}

void JsonValue::getValue(int& jInt, bool& error) const
{
	error = false;
	if (getValueType() == JsonValueType::JSONInteger) {
		jInt = value.jsonInteger;
	} else {
		error = true;
	}
}

void JsonValue::getValue(bool& jBool, bool& error) const
{
	error = false;
	if (getValueType() == JsonValueType::JSONBoolean) {
		jBool = value.jsonBoolean;
	} else {
		error = true;
	}
}

void JsonValue::getValue(double& jDouble, bool& error) const
{
	error = false;
	if (getValueType() == JsonValueType::JSONDouble) {
		jDouble = value.jsonDouble;
	} else {
		error = true;
	}
}


void JsonValue::getValue(TEXT& jString, bool& error) const
{
	error = false;
	if (getValueType() == JsonValueType::JSONString) {
		jString = *(value.jsonString);
	} else {
		error = true;
	}
}

void JsonValue::getValue(JsonObject* jObject, bool& error) const
{
	error = false;
	if (getValueType() == JsonValueType::JSONObject) {
		jObject = value.jsonObject;
	} else {
		error = true;
	}
}

// setter functions
void JsonValue::setValueType(JsonValueType type)
{
	valueType = type;
}

void JsonValue::setValue(int jInt)
{
	setValueType(JsonValueType::JSONInteger);
	value.jsonInteger = jInt;
}

void JsonValue::setValue(bool jBool)
{
	setValueType(JsonValueType::JSONBoolean);
	value.jsonBoolean = jBool;
}

void JsonValue::setValue(double jDouble)
{
	setValueType(JsonValueType::JSONDouble);
	value.jsonDouble = jDouble;
}

void JsonValue::setValue(TEXT* jString)
{
	setValueType(JsonValueType::JSONString);
	value.jsonString = jString;
}

void JsonValue::setValue(JsonObject* jObject)
{
	setValueType(JsonValueType::JSONObject);
	value.jsonObject = jObject;
}
