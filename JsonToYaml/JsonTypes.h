#pragma once

#include <string>
#include <variant>
#include <map>
#include <vector>
#include <istream>
#include <ostream>

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

struct Json {
	std::variant<Array, Object> body;

	Json(std::variant<Array, Object> body) : body(body) {}
};

