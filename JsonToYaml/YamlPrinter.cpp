#include "YamlPrinter.h"

void YamlPrinter::Print() {
	if (Array* arr = std::get_if<Array>(&input.body)) {
		PrintArray(*arr);
	}

	else if (Object* obj = std::get_if<Object>(&input.body)) {
		PrintObject(*obj);
	}
}

void YamlPrinter::PrintValue(const JsonValue& value) {
	if (auto* str = std::get_if<String>(&value)) {
		PrintString(*str);
	}

	else if (auto* num = std::get_if<Number>(&value)) {
		output << num->value;
	}

	else if (auto* b = std::get_if<Boolean>(&value)) {
		if (b->value == true)
			output << "true";
		else
			output << "false";
	}

	else if (std::holds_alternative<Null>(value)) {
		output << '~';
	}

	else if (auto* obj = std::get_if<Object>(&value)) {
		output << '\n';
		PrintObject(*obj);
	}

	else if (auto* arr = std::get_if<Array>(&value)) {
		output << '\n';
		PrintArray(*arr);
	}
}

void YamlPrinter::PrintArray(const Array& array) {
	indentLevel++;
	size_t i = 0;

	for(const JsonValue& value : array.values) {
		if (indentLevel > 0) {
			output << std::string(indentLevel, ' ');
		}

		output << "- ";
		PrintValue(value);

		// Don't print new line after last item
		if(i < array.values.size() - 1) {
			output << '\n';
		}

		i++;
	}

	indentLevel--;
}

void YamlPrinter::PrintObject(const Object& object) {
	indentLevel++;

	size_t i = 0;

	for (auto& [key, value] : object.values) {
		output << std::string(indentLevel, ' ');
		PrintString(key);
		output << ": ";
		PrintValue(value);

		// Don't print new line after last item
		if (i < object.values.size() - 1) {
			output << '\n';
		}

		i++;
	}

	indentLevel--;
}

void YamlPrinter::PrintString(const String& string) {
	// First, determine the quotation type

	enum Quotation { Single, Double, None };
	Quotation quot = None;

	for (char c : string.value) {
		if (c == '\\') {
			quot = Double;
			break;
		}

		else if (singleQuoteChars.find(c) != std::string::npos) {
			quot = Single;
		}
	}

	if (quot == Single) output << '\'';
	else if (quot == Double) output << '"';
	
	for (char c : string.value) {
		if (c == '\'' && quot == Single) {
			// Escape ' character with ' character
			output << '\'';
		}

		output << c;
	}

	if (quot == Single) output << '\'';
	else if (quot == Double) output << '"';
}