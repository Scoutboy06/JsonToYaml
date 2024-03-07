#pragma once

#include <string>
#include <variant>
#include <map>
#include <vector>
#include <fstream>

// Tokens
struct String { std::string value; };
struct Number { std::string value; };
struct Boolean { bool value; };
struct Null {};
struct OpenCurly {};
struct ClosedCurly {};
struct OpenBracket {};
struct ClosedBracket {};
struct Colon {};
struct Comma {};
struct EndOfFile {};

struct Object {
	std::map<String, JsonValue> value;
};
struct Array {
	std::vector<JsonValue> value;
};
struct Json {
	JsonValue body;
};

using JsonValue = std::variant<
	Object,
	Array,
	String,
	Number,
	Boolean,
	Null,
>;

class Parser {
private:
	std::ifstream& stream;
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

	String ParseString();
	Number ParseNumber();
	Boolean ParseBoolean();
	Null ParseNull();

	Object ParseObject();
	Array ParseArray();

public:
	Parser(std::ifstream& stream) : stream(stream) {
		stream.get(currChar);
		stream.get(peekChar);
	}

	Json Parse();
};
