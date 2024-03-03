#include <fstream>
#include <string>
#include <iostream>
#include <sstream>
#include <variant>

#include "Tokenizer.h"

int main()
{
	std::ifstream input("./test.json");

	if (!input.is_open()) {
		std::cout << "Unable to open file" << std::endl;
		return 1;
	}

	std::stringstream buffer;
	buffer << input.rdbuf();
	std::string str = buffer.str();

	std::cout << str.length() << ", " << str[0] << std::endl;

	Tokenizer tokenizer(str);

	/*while (true) {
		Token next = tokenizer.NextToken();

		if (auto str = std::get_if<String>(&next)) {
			std::cout << "String: " << str->value;
		}
		
		else if (auto num = std::get_if<Number>(&next)) {
			if (auto l = std::get_if<long>(&(num->value))) {
				std::cout << "Long: " << l;
			}

			else if (auto d = std::get_if<double>(&(num->value))) {
				std::cout << "Double: " << d;
			}
		}

		else if (auto b = std::get_if<Boolean>(&next)) {
			std::cout << "Boolean: " << b->value;
		}

		std::cout << std::endl;

		if (std::holds_alternative<EndOfFile>(next)) {
			std::cout << "End of file" << std::endl;
			break;
		}
	}*/
}