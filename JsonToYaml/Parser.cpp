#include "Parser.h"

// ==========================
// =====  Type classes  =====
// ==========================

class Object {
public:
	explicit Object(const std::map<String, JsonValue>& data) : _data(data) {};
private:
	const std::map<String, JsonValue>& _data;
};

class Array {
public:
	explicit Array(const std::vector<JsonValue>& data) : _data(data) {};
private:
	const std::vector<JsonValue>& _data;
};

// =========================
// =======  Parsing  =======
// =========================

Json Parser::Parse(const std::string& input) {
	Tokenizer tokenizer(input);

	Token token = tokenizer.NextToken();

	if (std::holds_alternative<OpenCurly>(token)) {
		auto v = ParseObject();
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

}