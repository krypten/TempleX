/*
*	Author: Chaitanya Agrawal (krypten)
*
*	Description:
*
*/

#ifndef JsonDOM_OBJECT_H_
#define JsonDOM_OBJECT_H_

#include <map>
#include <vector>

#include "JsonDOMValue.h"

//namespace JsonDOM {

const std::string JSON_ARRAY_TAG = "@array";

class JsonObject {
public:
	enum JsonObjectType {
		JSONMap,
		JSONArray
	};
	typedef std::vector<JsonValue> JsonArray;
	typedef std::pair<TEXT, JsonValue> JsonMap;

	private:
		JsonObjectType objectType;
		union {
			JsonArray * jsonArray;
			JsonMap * jsonMap;
		} object;

	public:
		// constructors
		//JsonObject();

		// getter const
		JsonObjectType getObjectType() const;
		void getObject(JsonArray& jArray, bool& error) const;
		void getObject(JsonMap& jMap, bool& error) const;

		// setter
		void setObjectType(JsonObjectType type);
		void setObject(JsonArray* jArray);
		void setObject(JsonMap* jMap);

		static void assignMap(JsonMap* jMap, TEXT key, JsonValue jValue);
		static void assignArray(JsonArray* jArray, JsonValue jValue);
};

#endif // JsonDOM_OBJECT_H_
