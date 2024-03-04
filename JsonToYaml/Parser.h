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

	void Advance();
	void SkipWhitespace();
	void Expect(char c) const;
	void ExpectPeek(char c) const;
	void ExpectEither(std::initializer_list<char> list) const;

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
