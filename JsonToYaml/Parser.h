#pragma once

#include <variant>
#include <map>
#include <vector>

#include "Tokenizer.h"

class Object;
class Array;

using JsonValue = std::variant<
	Object,
	Array,
	String,
	Number,
	Boolean,
	Null,
>;

struct Json {
	JsonValue& body;
};

class Parser {
private:
	const std::string& input;
public:
	static Json Parse(const std::string& input);

	Object ParseObject();
	Array ParseArray();
};
