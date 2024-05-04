#pragma once

#include <string>
#include <variant>
#include <map>
#include <vector>
#include <istream>

struct String {
	std::string value;
	bool operator<(const String& other) const { return value < other.value; };
};
struct Number { std::string value; };
struct Boolean { bool value; };
struct Null {};

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
	std::map<String, JsonValue> values;
};
struct Array {
	std::vector<JsonValue> values;
};


class Json {
public:
	std::variant<Array, Object> body;

	Json(std::variant<Array, Object> body) : body(body) {}

	static Json Parse(std::istream& stream);
};

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
