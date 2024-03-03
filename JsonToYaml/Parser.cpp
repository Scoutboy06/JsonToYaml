#include "Parser.h"
#include "Tokenizer.h"

Json Parser::Parse(const std::string& input) {
	Tokenizer tokenizer(input);
	Token token = tokenizer.NextToken();

	if (std::holds_alternative<OpenCurly>(token)) {
		Object v = ParseObject();
		return Json{ v };
	}

	if (std::holds_alternative<OpenBracket>(token)) {
		Array v = ParseArray();
		return Json{ v };
	}

	while (!std::holds_alternative<EndOfFile>(token)) {
		if (std::holds_alternative<OpenCurly>(token)) {

		}

		token = tokenizer.NextToken();
	}
};

Object Parser::ParseObject() {
	
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