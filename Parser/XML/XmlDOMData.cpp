/*
*	Author: Chaitanya Agrawal (krypten)
*
*	Description:
*
*/

#include "XmlDOMData.h"

//using namespace XmlDOM;

Data::Data() : dataValue("")
{
}

Data::Data(TEXT data) : dataValue(data)
{
}

TEXT Data::getValue() const
{
	return dataValue;
}

void Data::setValue(TEXT value)
{
	dataValue = value;
}
