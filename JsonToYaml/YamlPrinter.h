#pragma once

#include <variant>
#include <string>
#include <ostream>

#include "JsonTypes.h"
#include "Parser.h"

/// @brief String of characters that need to be single quoted in YAML.
const std::string singleQuoteChars(R"(:{}[],&*#?|-<>=!%@"')");

/// @brief Class to print a Json tree in YAML format.
class YamlPrinter {
public:
	/**
	 * @brief Constructor for YamlPrinter class.
	 * @param input The Json tree to be printed.
	 * @param output The output stream where the YAML will be printed.
	 */
	YamlPrinter(Json& input, std::ostream& output) : input(input), output(output) {}

	/// @brief Prints the JSON tree in YAML format to the output stream.
	void Print();
private:
	std::ostream& output;	/// The output stream where the outputed YAML will be printed.
	Json& input;			/// The JSON tree to be printed.

	int indentLevel = -1;	/// The current indentation level for the YAML printer.

	/**
	 * @brief Prints a JsonValue in YAML format to the output stream.
	 * @param value The JsonValue to be printed.
	 */
	void PrintValue(const JsonValue& value);

	/**
	 * @brief Prints an Array in YAML format to the output stream.
	 * @param array The Array to be printed.
	 */
	void PrintArray(const Array& array);

	/**
	 * @brief Prints an Object in YAML format to the output stream.
	 * @param object The Object to be printed.
	 */
	void PrintObject(const Object& object);

	/**
	 * @brief Prints a String in YAML format to the output stream.
	 * @param string The String to be printed.
	 */
	void PrintString(const String& string);
};

