#include "Tokenizer.h"

Token Tokenizer::NextToken() {
	if (cursor >= input.length()) {
		return EndOfFile();
	}

	char peek = Peek();

	if (peek == '-' || isalnum(peek)) {
		return ParseNumber();
	}

	switch (peek) {
		case '"': return ParseString();
		case 't': return ParseBoolean();
		case 'f': return ParseBoolean();
		case 'n': return ParseNull();
		case '{': Skip(); return OpenCurly();
		case '}': Skip(); return ClosedCurly();
		case '[': Skip(); return OpenBracket();
		case ']': Skip(); return ClosedBracket();
		case ':': Skip(); return Colon();
		case ',': Skip(); return Comma();
		case '\0': return EndOfFile();
	}

	return NextToken();
}

String Tokenizer::ParseString() {
	std::string result;

	Expect('"');
	char ch = Next();
	bool isEscaped = false;

	while (ch != '"' && !isEscaped) {
		if (ch == '\\') {
			isEscaped = !isEscaped;
		}

		result += ch;
		ch = Next();
	}

	return String{ result };
}

Number Tokenizer::ParseNumber() {
	std::string number;
	bool isDecimal = false;

	char ch = Next();

	while (std::isdigit(ch) || ch == '.' || ch == '-' || ch == '+') {
		if (ch == '.') {
			isDecimal = true;
		}

		number += ch;
		ch = Next();
	}

	// Since the last character wasn't a valid character, go back
	Back();

	if (isDecimal) {
		return Number{ stod(number) };
	} else {
		return Number{ stol(number) };
	}
}

Boolean Tokenizer::ParseBoolean() {
	char peek = Peek();

	if (peek == 't') {
		Expect('t');
		Expect('r');
		Expect('u');
		Expect('e');
		return Boolean{ true };
	}
	else if (peek == 'f') {
		Expect('f');
		Expect('a');
		Expect('l');
		Expect('s');
		Expect('e');
		return Boolean{ false };
	}

	throw std::exception("Invalid value");
}

Null Tokenizer::ParseNull() {
	Expect('n');
	Expect('u');
	Expect('l');
	Expect('l');
	return Null();
}

char Tokenizer::Peek() {
	if (cursor + 1 >= input.length()) {
		return '\0';
	}
	return input[cursor + 1];
}

void Tokenizer::Skip() { cursor++; };

void Tokenizer::Back() { cursor--; };

/**
* @bref Steps to the next character, increasing the counter
*/
char Tokenizer::Next() {
	if (cursor + 1 >= input.length()) {
		return '\0';
	}
	return input[++cursor];
}

/**
* @brief Steps to the next character, increasing the counter.
* Throws an error if the next character does not equal the expected one.
*/
void Tokenizer::Expect(char ch) {
	if (Next() != ch) {
		throw std::exception("Invalid character: " + ch);
	}
}