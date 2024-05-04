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
	if(auto* obj = std::get_if<Object>(&value)) {
		PrintObject(*obj);
	}

	else if (auto* arr = std::get_if<Array>(&value)) {
		PrintArray(*arr);
	}

	else if (auto* str = std::get_if<String>(&value)) {
		PrintString(*str);
	}

	else if (auto* num = std::get_if<Number>(&value)) {
		output << num->value;
	}

	else if (auto* b = std::get_if<Boolean>(&value)) {
		output << b->value;
	}

	else if (std::holds_alternative<Null>(value)) {
		output << "null";
	}
}

void YamlPrinter::PrintArray(const Array& array) {
	indentLevel++;
	output << std::endl;

	int i = 0;
	for(const JsonValue& value : array.values) {
		// Indentation
		output
			<< std::string(indentLevel * INDENT_SIZE, ' ')
			<< "- ";

		if (auto str = std::get_if<String>(&value)) {
			PrintString(*str);
		}

		else if (auto num = std::get_if<Number>(&value)) {
			output << num->value;
		}

		else if (auto b = std::get_if<Boolean>(&value)) {
			output << b->value;
		}

		else if (auto obj = std::get_if<Object>(&value)) {
			PrintObject(*obj);
		}

		else if (auto arr = std::get_if<Array>(&value)) {
			PrintArray(*arr);
		}

		// Don't print null values
		else if (std::holds_alternative<Null>(value)) {
			output << "null";
		}

		// Don't print endl after last item
		if(i < array.values.size() - 1) {
			output << std::endl;
		}

		i++;
	}

	indentLevel--;
}

void YamlPrinter::PrintObject(const Object& object) {
	indentLevel++;

	output << '\n' << std::string(indentLevel * INDENT_SIZE, ' ');

	int i = 0;
	for (auto& [key, value] : object.values) {
		PrintString(key);
		output << ": ";
		PrintValue(value);

		if (i < object.values.size() - 1) {
			output << '\n'
				   << std::string(indentLevel * INDENT_SIZE, ' ');
		}

		i++;
	}

	indentLevel--;
}

void YamlPrinter::PrintString(const String& str) {
	enum Quotation { None, Single, Double };
	Quotation quot = None;

	// Figure out the type of quotation to use
	for (char ch : str.value) {
		if (ch == '\\' || !isprint(ch)) {
			quot = Double;
			break;
		}

		if (quotedChars.find(ch) != std::string::npos) {
			quot = Single;
		}
	}

	// If the string is empty, use single quotes
	if (str.value.empty()) {
		quot = Single;
	}

	if (quot == Single)
		output << '\'';
	else if (quot == Double)
		output << '"';

	output << str.value;

	if (quot == Single)
		output << '\'';
	else if (quot == Double)
		output << '"';
}
