#pragma once

#include <variant>
#include <map>
#include <vector>

#include "Tokenizer.h"

struct Object {
	std::map<String, JsonValue> value;
};

struct Array {
	std::vector<JsonValue> value;
};

struct Json {
	JsonValue& body;
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
	const std::string& input;
	Tokenizer tokenizer;
public:
	Json Parse(const std::string& input);

	Object ParseObject();
	Array ParseArray();
};
