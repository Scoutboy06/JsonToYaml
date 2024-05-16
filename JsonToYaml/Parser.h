#pragma once

#include <string>
#include <variant>
#include <map>
#include <vector>
#include <istream>
#include <sstream>

#include "JsonTypes.h"
#include "YamlPrinter.h"

/// @brief Class to parse a JSON tree from an input stream.
class Parser {
private:
	std::istream& stream;		/// The input stream from which the JSON tree is parsed.
	char currChar;				/// The current character being parsed.
	char peekChar;				/// The next character to be parsed.
	long lineIndex = 0;			/// The current line index in the input stream.
	long lineColIndex = 0;		/// The current column index in the input stream.
	bool isEOF = false;			/// Flag indicating if the end of the input stream has been reached.
	bool isPeekEOF = false;		/// Flag indicating if the next character is the end of the input stream.

	/// @brief Advances the parser to the next character in the input stream.
	void Advance();

	/// @brief Skips whitespace characters in the input stream.
	void SkipWhitespace();

	/**
	 * @brief Expects the next character in the input stream to be a specific character.
	 * @param c The character to check against.
	 * @throws std::exception if the current character being parsed does not equal param c.
	 */
	void Expect(char c);

	/**
	 * @brief Parses the upcoming JSON value in the input stream.
	 * @return The parsed JsonValue.
	 */
	JsonValue ParseValue();

	/**
	 * @brief Parses the upcoming JSON value in the input stream as a String value.
	 * @return The parsed String value.
	 */
	String ParseString();

	/**
	 * @brief Parses the upcoming JSON value in the input stream as a Number value.
	 * @return The parsed Number value.
	 */
	Number ParseNumber();

	/**
	 * @brief Parses the upcoming JSON value in the input stream as a Boolean value.
	 * @return The parsed Boolean value.
	 */
	Boolean ParseBoolean();

	/**
	 * @brief Parses the upcoming JSON value in the input stream as a Null value.
	 * @return An instance of Null.
	 */
	Null ParseNull();

	/**
	 * @brief Parses the upcoming JSON value in the input stream as an Object.
	 * @return The parsed Object.
	 */
	Object ParseObject();

	/**
	 * @brief Parses the upcoming JSON value in the input stream as an Array.
	 * @return The parsed Array.
	 */
	Array ParseArray();

public:
	/// @brief Constructor for the Parser class.
	Parser(std::istream& stream) : stream(stream) {
		stream.get(currChar);
		stream.get(peekChar);
	}

	/// @brief Starts the parsing of the input stream into a JSON tree.
	Json Parse();
};

/**
 * @brief Parses the input stream into a JSON tree.
 * @param stream The input stream.
 * @return A Json object, holding the parsed JSON tree.
 */
static Json ParseJson(std::istream& stream) {
	Parser parser(stream);
	return parser.Parse();
}

/**
 * @brief Parses the input string into a JSON tree.
 * @param string The input string.
 * @return a Json object, holding the parsed JSON tree.
 */
static Json ParseJson(const std::string& string) {
	std::stringstream stream(string);
	Parser parser(stream);
	return parser.Parse();
}