#pragma once

#include <variant>
#include <string>
#include <fstream>

#include "Parser.h"

class YamlPrinter {
public:
	YamlPrinter(Json& input, std::ofstream& output)
		: input(input), output(output) {}

	void Print();
private:
	std::ofstream& output;
	Json& input;

	uint32_t indentLevel = 0;

	void PrintArray(const Array& array);
	void PrintObject(const Object& object);
	void PrintString(const String& string);
};

