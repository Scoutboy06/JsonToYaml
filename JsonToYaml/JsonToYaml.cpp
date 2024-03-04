#include <fstream>
#include <string>
#include <iostream>

#include "Parser.cpp"

int main()
{
	std::ifstream input("./test.json");

	if (!input.is_open()) {
		std::cout << "Unable to open file" << std::endl;
		return 1;
	}

	Json result = ParseJson(input);

	input.close();
}