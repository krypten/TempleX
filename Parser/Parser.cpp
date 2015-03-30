/* 
*	Author: Chaitanya Agrawal (krypten)
*
*	Description: 
*
*/

#include <fstream>
#include <iostream>
#include "Parser.h"

void Parser::readFile(TEXT fileName, TEXT& fileString, bool& error)
{
	TEXT temp;
	std::fstream mFile(fileName.c_str());

	if (!mFile) {
		error = true;
		fileString = "";
		std::cerr << "READ ERROR\n";
		return ;
	}

	while(std::getline(mFile, temp)) {
		fileString += temp;
	}
}

void Parser::getFirstPosition(TEXT text, char value, unsigned int& start_position, unsigned int& end_position)
{
		start_position = text.find_first_of(value);
		
		if (start_position >= 0 && start_position <= text.size()) {
			end_position = start_position + text.substr(start_position).find_first_not_of(value);
		} else {
			start_position = text.size() - 1;
			end_position = start_position;
		}
}

void Parser::getNotFirstPosition(TEXT text, char value, unsigned int& position)
{
	position = text.find_first_not_of(value);
	if (position == TEXT::npos) {
		position = text.size() - 1;
	}
}

int Parser::toDigit(char digit)
{
	return (digit - '0');
}

bool Parser::isDigit(char digit)
{
	return ('0' <= digit && digit <= '9');
}