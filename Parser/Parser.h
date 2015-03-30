/*
*	Author: Chaitanya Agrawal (krypten)
*
*	Description:
*
*/

#ifndef PARSER_H_
#define PARSER_H_

#include <string>

typedef std::string TEXT;

class Parser {
	public:
		enum ParseInputType {
			FILE,
			STRING
		};

		void readFile(TEXT fileName, TEXT& fileString, bool& error);

		void getFirstPosition(TEXT text, char value, unsigned int& start_position, unsigned int& end_position);
		//change name
		void getNotFirstPosition(TEXT text, char value, unsigned int& position);

		int toDigit(char digit);
		bool isDigit(char digit);
};

#endif // PARSER_H_
