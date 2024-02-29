#include "Parser.h"

// ==========================
// =====  Type classes  =====
// ==========================

class Json {
public:
	explicit Json(const JsonTypeVariant& data) : _data(data) {};
private:
	const JsonTypeVariant& _data;
};

class Object {
public:
	explicit Object(const JsonObjectVariant& data) : _data(data) {};
private:
	const JsonObjectVariant& _data;
};

class Array {
public:
	explicit Array(const JsonArrayVariant& data) : _data(data) {};
private:
	const JsonArrayVariant& _data;
};

class String {
public:
	explicit String(const std::string& data) : _data(data) {};
private:
	const std::string& _data;
};

class Number {
public:
	explicit Number(const long data) : _data(data) {};
private:
	const long _data;
};

class Boolean {
public:
	explicit Boolean(const bool data) : _data(data) {};
private:
	const bool _data;
};

class Null {
public:
	explicit Null() {};
};

Object Json::Object(const JsonObjectVariant& data) { return Object(data); };

Array Json::Array(const JsonArrayVariant& data) { return Array(data); };

String Json::String(const std::string& data) { return String(data); };

Number Json::Number(const long data) { return Number(data); };

Boolean Json::Boolean(const bool data) { return Boolean(data); };

Null Json::Null() { return Null(); };

// =========================
// =======  Parsing  =======
// =========================

Json Parser::Parse(const std::string& input) {
};

Json Parser::ParseObject() {
};

