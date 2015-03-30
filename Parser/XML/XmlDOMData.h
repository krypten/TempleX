/*
*	Author: Chaitanya Agrawal (krypten)
*
*	Description:
*
*/

#ifndef XmlDOM_DATA_H_
#define XmlDOM_DATA_H_

#include <string>

/*
namespace XmlDOM {
	typedef std::string TEXT;

	class Data;
}

using namespace XmlDOM;
*/

#include "../Parser.h"

class Data {
public:
	private:
		TEXT dataValue;

	public:

		// constructors
		Data();
		Data(TEXT data);
		// getter const
		TEXT getValue() const;

		// setter
		void setValue(TEXT value);
};

#endif // XmlDOM_DATA_H_
