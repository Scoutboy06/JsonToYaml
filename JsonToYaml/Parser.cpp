#include "Parser.h"

Json ParseJson(std::ifstream& stream) {
	Parser parser(stream);
	return parser.Parse();
}

Json Parser::Parse() {
	switch (peekChar) {
		case '{': return Json{ ParseObject() };
		case '[': return Json{ ParseArray() };
		case '"': return Json{ ParseString() };
		case 't':
		case 'f': return Json{ ParseBoolean() };
		case 'n': return Json{ ParseNull() };
	}

	if (std::isdigit(peekChar)) {
		return Json{ ParseNumber() };
	}

	throw std::exception("Invalid character at beginning of file");
};

void Parser::Advance() {
	currChar = peekChar;
	stream.get(peekChar);
}

void Parser::SkipWhitespace() {
	while (std::isspace(currChar)) {
		Advance();
	}
}

void Parser::Expect(char c) const {
	if (currChar != c) {
		throw std::exception("Invalid character");
	}
}

void Parser::ExpectPeek(char c) const {
	if (peekChar != c) {
		throw std::exception("Invalid character");
	}
}

void Parser::ExpectEither(std::initializer_list<char> list) const {
	for (char ch : list) {
		if (ch == currChar)
			return;
	}

	throw std::exception("Invalid token");
}

String Parser::ParseString() {
	std::string result;

	Expect('"');
	Advance();
	bool isEscaped = false;

	while (currChar != '"' && isEscaped) {
		if (currChar == '\\') {
			isEscaped = !isEscaped;
		}

		result += currChar;
		Advance();
	}

	// Since the current character is a ", advance
	Advance();

	return String{ result };
}

Number Parser::ParseNumber() {
	std::string number;

	bool isDecimal = false;
	bool isPower = false;

	if (currChar == '-') {
		number += currChar;
		Advance();
	}

	while (std::isdigit(currChar)
		|| currChar == '.'
		|| currChar == '-'
		|| currChar == '+'
		|| currChar == 'e'
		|| currChar == 'E')
	{
		if (currChar == 'e' || currChar == 'E') {
			if (isPower) throw std::exception("Invalid number");
			isPower = true;

			if (peekChar == '+' || peekChar == '-') {
				number += currChar;
				Advance();
			}
		}

		else if (currChar == '.') {
			if (isDecimal) throw std::exception("Invalid number");
			isDecimal = true;
		}

		number += currChar;
		Advance();
	}

	return Number{ number };
}

Object Parser::ParseObject() {
	std::map<String, JsonValue> object;

	enum State { Key, Value };

	String key;
	State state = Key; // What we expect next

	while (currChar != '}') {
		if (state == Key) {
			if (currChar == '"') {
				key = ParseString();
				state = Value;
			} else {
				throw std::exception("Invalid key in object");
			}
		}

		else {
			switch (currChar) {
				case '{': object.insert_or_assign(key, ParseObject()); break;
				case '[': object.insert_or_assign(key, ParseArray()); break;
				case '"': object.insert_or_assign(key, ParseString()); break;
				case 't':
				case 'f': object.insert_or_assign(key, ParseBoolean()); break;
				case 'n': object.insert_or_assign(key, ParseNull()); break;
				default:
					if (std::isdigit(peekChar)) {
						object.insert_or_assign(key, ParseNumber());
					} else {
						throw std::exception("Invalid character at beginning of file");
					}
			}
		}

		Advance();
	}

	if (state == Key) {
		throw std::exception("Unexpected end of object");
	}

	return Object{ object };
};

Array Parser::ParseArray() {
	std::vector<JsonValue> array;
	
	Token token = tokenizer.NextToken();

	while (!std::holds_alternative<ClosedBracket>(token)) {
		if (std::holds_alternative<EndOfFile>(token)) {
			throw std::exception("Unexpected end of file");
		}

		// "," Comma
		if (std::holds_alternative<Comma>(token)) {
			continue;
		}

		// "{" Open curly brace
		if (std::holds_alternative<OpenCurly>(token)) {
			array.push_back(ParseObject());
		}
		
		// "[" Open bracket
		else if (std::holds_alternative<OpenBracket>(token)) {
			array.push_back(ParseArray());
		}
		
		// String
		else if(String* str = std::get_if<String>(&token)){
			array.push_back(*str);
		}
		
		// Number
		else if (Number* num = std::get_if<Number>(&token)) {
			array.push_back(*num);
		}
		
		// Boolean
		else if (Boolean* b = std::get_if<Boolean>(&token)) {
			array.push_back(*b);
		}

		// Null
		else if (std::holds_alternative<Null>(token)) {
			array.push_back(Null());
		}
		
		// Invalid token
		else {
			throw std::exception("Invalid token");
		}

		token = tokenizer.NextToken();
	}

	return Array{ array };
}