/*
*	Author: Chaitanya Agrawal (krypten)
*
*	Description:
*
*/

#include "XmlDOMAttribute.h"

//using namespace XmlDOM;

Attribute::Attribute()
{
}

TEXT Attribute::getValue(TEXT key) const
{
	auto iter = attrMap.find(key);
	if (iter != attrMap.end()) {
		return iter->second;
	}
	return "";
}

Attribute::AttributeMap Attribute::getAttributeMap() const
{
	return attrMap;
}


void Attribute::setValue(TEXT key, TEXT value)
{
	if (key != "") {
		attrMap[key] = value;
	}
}
