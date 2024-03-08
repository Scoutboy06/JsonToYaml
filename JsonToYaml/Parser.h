#pragma once

#include <string>
#include <variant>
#include <map>
#include <vector>
#include <fstream>
#include <iostream>

// Tokens
struct String {
	std::string value;
	bool operator<(const String& other) const { return value < other.value; };
};
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

struct Object;
struct Array;

using JsonValue = std::variant<
	Object,
	Array,
	String,
	Number,
	Boolean,
	Null
>;

struct Object {
	std::map<String, JsonValue> value;
};
struct Array {
	std::vector<JsonValue> value;
};


class Json {
private:
public:
	JsonValue body;

	Json(JsonValue body) : body(body) {}

	static Json Parse(std::ifstream& stream);

	void PrintAsYaml(std::ofstream& outout);
};

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
