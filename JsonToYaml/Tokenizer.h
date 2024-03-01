#pragma once
#include <string>
#include <variant>

struct String {
	std::string value;
};

struct Number {
	std::string value;
};

struct Boolean {
	bool value;
};

struct Null {};
struct OpenCurly {};
struct ClosedCurly {};
struct OpenBracket {};
struct ClosedBracket {};
struct Colon {};
struct Comma {};
struct EndOfFile {};

using Token = std::variant<
	String,
	Number,
	Boolean,
	Null,
	OpenCurly,
	ClosedCurly,
	OpenBracket,
	ClosedBracket,
	Colon,
	Comma,
	EndOfFile
>;

class Tokenizer {
private:
	const std::string& input;
	unsigned int cursor = 0;

	char Peek();
	char Next();
	void Back();
	void Skip();

	String ParseString();
	Number ParseNumber();
	Boolean ParseBoolean();
	Null ParseNull();

	void Expect(char c);
public:
	Tokenizer(const std::string& input) : input(input) {}

	Token NextToken();
};

