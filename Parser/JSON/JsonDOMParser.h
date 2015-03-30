/* 
*	Author: Chaitanya Agrawal (krypten)
*
*	Description: 
*
*/

#ifndef JsonDOM_PARSER_H_
#define JsonDOM_PARSER_H_

#include "../Parser.h"
#include  "JsonDOMObject.h"

class JsonParser : public Parser {
	private:

	public:
		void parseJsonNumber(JsonValue& jValue, TEXT jNumber, unsigned int& start_pos); 
		void parseJsonValue(JsonValue& jValue, TEXT jString, unsigned int& start_pos);
		void parseJsonArray(JsonObject::JsonArray* currArray, TEXT jString, unsigned int& start_pos);
		void parseJsonMap(JsonObject::JsonMap* currMap, TEXT jString, unsigned int& start_pos);
		void parseJSON(TEXT jsonInput, ParseInputType inputType, JsonObject& jObject, bool& error);
};

#endif // JsonDOM_PARSER_H_