#pragma once

#include <variant>
#include <string>
#include <fstream>

#include "Parser.h"

#define INDENT_SIZE 2

const std::string quotedChars = R"(:#*?|-{}[]&!>@%\n\t\r\0\x85\x{2028}\x{2029})";

class YamlPrinter {
public:
	YamlPrinter(Json& input, std::ofstream& output) : input(input), output(output) {}

	void Print();
private:
	std::ofstream& output;
	Json& input;

	int32_t indentLevel = -1;

	void PrintValue(const JsonValue& value);
	void PrintArray(const Array& array);
	void PrintObject(const Object& object);
	void PrintString(const String& str);
};

