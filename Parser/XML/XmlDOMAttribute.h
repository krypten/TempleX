/*
*	Author: Chaitanya Agrawal (krypten)
*
*	Description:
*
*/

#ifndef XmlDOM_ATTRIBUTE_H_
#define XmlDOM_ATTRIBUTE_H_

#include <map>
#include <string>

//namespace XmlDOM {


//	class Attribute;
//}

#include "../Parser.h"

const std::string XML_ATTRIBUTE_TAG = "@attribute";


class Attribute	{
public:
	typedef std::map<TEXT, TEXT> AttributeMap;

	private:
		AttributeMap attrMap;

	public:
		// constructors
		Attribute();
		// getter const
		TEXT getValue(TEXT key) const;
		AttributeMap getAttributeMap() const;

		// setter
		void setValue(TEXT key, TEXT value);
};

#endif // XmlDOM_ATTRIBUTE_H_
