#pragma once

#include <variant>
#include <string>
#include <ostream>

#include "JsonTypes.h"
#include "Parser.h"

const std::string singleQuoteChars(R"(:{}[],&*#?|-<>=!%@"')");

class YamlPrinter {
public:
	YamlPrinter(Json& input, std::ostream& output) : input(input), output(output) {}

	void Print();
private:
	std::ostream& output;
	Json& input;

	int indentLevel = -1;

	void PrintValue(const JsonValue& value);
	void PrintArray(const Array& array);
	void PrintObject(const Object& object);
	void PrintString(const String& str);
};

