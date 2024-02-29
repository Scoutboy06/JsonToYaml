#pragma once

#include <variant>
#include <string>
#include <map>
#include <vector>
#include <any>

/*
Data types:
- Object
- Array
- String
- Number
- Boolean
- Null
*/

class Object;
class Array;
class String;
class Number;
class Boolean;
class Null;

using JsonObjectVariant = std::variant<std::string, JsonTypeVariant>;
using JsonArrayVariant = std::vector<JsonTypeVariant>;

using JsonTypeVariant = std::variant<
	JsonObjectVariant, // Object
	JsonArrayVariant, // Array
	std::string, // String
	long, // Number
	bool, // Boolean
	// Null
>;

class Json {
public:
	enum class JsonType {
		Object,
		Array,
		String,
		Number,
		Boolean,
		Null,
	};

	static Object Object(const JsonObjectVariant& data);
	static Array Array(const JsonArrayVariant& data);
	static String String(const std::string& data);
	static Number Number(const long data);
	static Boolean Boolean(const bool data);
	static Null Null();

private:
	JsonType type;
	JsonTypeVariant value;

	Json(JsonType type, JsonTypeVariant value) : type(type), value(value) {}
};

class Parser {
private:
	const std::string& input;

	char NextToken();
	void Expect(char ch);
public:
	static Json Parse(const std::string& input);

	Object ParseObject();
};