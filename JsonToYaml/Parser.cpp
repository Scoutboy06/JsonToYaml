#include "Parser.h"

Json Json::Parse(std::ifstream& stream) {
	Parser parser(stream);
	return parser.Parse();
}

Json Parser::Parse() {
	SkipWhitespace();

	switch (currChar) {
		case '{': return Json{ ParseObject() };
		case '[': return Json{ ParseArray() };
		case '"': return Json{ ParseString() };
		case 't':
		case 'f': return Json{ ParseBoolean() };
		case 'n': return Json{ ParseNull() };
	}

	if (std::isdigit(currChar)) {
		return Json{ ParseNumber() };
	}

	throw std::exception("Invalid character at beginning of file");
};

void Parser::Advance() {
	lineColIndex++;

	if (currChar == '\n') {
		lineIndex++;
		lineColIndex = 0;
	}

	currChar = peekChar;
	stream.get(peekChar);

	if (isPeekEOF) isEOF = true;
	if (stream.eof()) isPeekEOF = true;
}

void Parser::SkipWhitespace() {
	while (std::isspace(currChar)) {
		Advance();
	}
}

void Parser::Expect(char c) {
	if (currChar != c) {
		throw std::exception("Invalid character");
	}
	Advance();
}

void Parser::ExpectEither(std::initializer_list<char> list) {
	for (char ch : list) {
		if (ch == currChar) {
			Advance();
			return;
		}
	}

	throw std::exception("Invalid token");
}

String Parser::ParseString() {
	std::string result;

	Expect('"');
	bool isEscaped = false;

	while (!(currChar == '"' && !isEscaped)) {
		if (currChar == '\\') {
			isEscaped = !isEscaped;
		}

		result += currChar;
		Advance();
	}

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

Boolean Parser::ParseBoolean() {
	if (currChar == 't') {
		Expect('t');
		Expect('r');
		Expect('u');
		Expect('e');
		return Boolean{ true };
	} else if (currChar == 'f') {
		Expect('f');
		Expect('a');
		Expect('l');
		Expect('s');
		Expect('e');
		return Boolean{ false };
	} else {
		throw std::exception("Invalid character");
	}
}

Null Parser::ParseNull() {
	Expect('n');
	Expect('u');
	Expect('l');
	Expect('l');
	return Null{};
}

Object Parser::ParseObject() {
	std::map<String, JsonValue> object;

	Expect('{');
	SkipWhitespace();

	enum State { Key, Value };

	State state = Key; // What we expect next
	String key;

	while (currChar != '}') {
		if (state == Key) {
			if (currChar == '"') {
				key = ParseString();
				state = Value;
				SkipWhitespace();
				Expect(':');
				SkipWhitespace();
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
						throw std::exception("Invalid character");
					}
			}

			SkipWhitespace();
			if (currChar == '}') {
				break;
			}
			Expect(',');
			SkipWhitespace();
			state = Key;
		}
	}

	if (state == Key) {
		throw std::exception("Unexpected end of object");
	}


	// Since currChar == '{', advance
	Advance();

	return Object{ object };
};

Array Parser::ParseArray() {
	std::vector<JsonValue> array;

	Expect('[');
	SkipWhitespace();

	while (currChar != ']') {
		std::cout << currChar << std::endl;

		if(isEOF) {
			throw std::exception("Unexpected end of file");
		}

		if (currChar == '{') {
			array.push_back(ParseObject());
		}
		
		else if (currChar == '[') {
			array.push_back(ParseArray());
		}
		
		// String
		else if(currChar == '"') {
			array.push_back(ParseString());
		}
		
		// Number
		else if (std::isdigit(currChar)) {
			array.push_back(ParseNumber());
		}
		
		// Boolean
		else if (currChar == 't' || currChar == 'f') {
			array.push_back(ParseBoolean());
		}

		// Null
		else if (currChar == 'n') {
			array.push_back(ParseNull());
		}
		
		// Invalid token
		else {
			throw std::exception("Invalid token");
		}

		SkipWhitespace();
		if (currChar == ']') break;
		Expect(',');
		SkipWhitespace();
	}

	Advance(); // Since currChar == ']'

	return Array{ array };
}

void Json::PrintAsYaml(std::ofstream& output) {
	
}