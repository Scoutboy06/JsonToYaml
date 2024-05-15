#pragma once

#include <string>
#include <variant>
#include <map>
#include <vector>
#include <istream>
#include <sstream>

#include "JsonTypes.h"
#include "YamlPrinter.h"

class Parser {
private:
	std::istream& stream;
	char currChar;
	char peekChar;
	long lineIndex = 0;
	long lineColIndex = 0;
	bool isEOF = false;
	bool isPeekEOF = false;

	void Advance();
	void SkipWhitespace();
	void Expect(char c);
	void ExpectEither(std::initializer_list<char> list);

	JsonValue ParseValue();
	String ParseString();
	Number ParseNumber();
	Boolean ParseBoolean();
	Null ParseNull();

	Object ParseObject();
	Array ParseArray();

public:
	Parser(std::istream& stream) : stream(stream) {
		stream.get(currChar);
		stream.get(peekChar);
	}

	Json Parse();
};

static Json ParseJson(std::istream& stream) {
	Parser parser(stream);
	return parser.Parse();
}

static Json ParseJson(const std::string& string) {
	std::stringstream stream(string);
	Parser parser(stream);
	return parser.Parse();
}