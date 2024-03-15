#include "YamlPrinter.h"

void YamlPrinter::Print() {
	if (Array* arr = std::get_if<Array>(&input.body)) {
		PrintArray(*arr);
	}

	else if (Object* obj = std::get_if<Object>(&input.body)) {
		PrintObject(*obj);
	}
}

void YamlPrinter::PrintArray(const Array& array) {
	indentLevel++;
	output << std::endl;
	size_t i = 0;

	for(const JsonValue& value : array.values) {
		// Indentation
		output
			<< std::string(' ', indentLevel)
			<< "- ";

		if (auto str = std::get_if<String>(&value)) {
			output << str->value;
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
			output << std::endl;
			PrintArray(*arr);
		}

		// Don't print null values
		//else if (std::holds_alternative<Null>(value));

		// Don't print endl after last item
		if(i < array.values.size() - 1) {
			output << std::endl;
		}
		i++;
	}

	indentLevel--;
}

void YamlPrinter::PrintObject(const Object& object) {}

void YamlPrinter::PrintString(const String& string) {}