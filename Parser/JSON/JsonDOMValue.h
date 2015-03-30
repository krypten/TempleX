/*
*	Author: Chaitanya Agrawal (krypten)
*
*	Description:
*
*/

#ifndef JsonDOM_VALUE_H_
#define JsonDOM_VALUE_H_


#include <string>
#include <memory>

#include "../Parser.h"

#define JSON_INT_TAG = "@int";
#define JSON_DOUBLE_TAG = "@double";
#define JSON_STRING_TAG = "@string";

//namespace JsonDOM {
class JsonObject;

class JsonValue {
public:
	enum JsonValueType {
		JSONInteger,
		JSONBoolean,
		JSONDouble ,
		JSONString,
		JSONObject
	};

	private:
		JsonValueType valueType;
		union {
			int jsonInteger;
			bool jsonBoolean;
			double jsonDouble;

			TEXT * jsonString;
			JsonObject * jsonObject;
		} value;
	public:
		// constructors
		JsonValue();

		// getter const
		JsonValueType getValueType() const;
		void getValue(int& jInt, bool& error) const;
		void getValue(bool& jBool, bool& error) const;
		void getValue(double& jDouble, bool& error) const;

		void getValue(TEXT& jString, bool& error) const;
		void getValue(JsonObject* jObject, bool& error) const;

		// setter
		void setValueType(JsonValueType type);
		void setValue(int jInt);
		void setValue(bool jBool);
		void setValue(double jDouble);

		void setValue(TEXT* jString);
		void setValue(JsonObject* jObject);
};
#endif // JsonDOM_VALUE_H_
