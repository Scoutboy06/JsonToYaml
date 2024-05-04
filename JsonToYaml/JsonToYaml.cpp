#include <fstream>
#include <string>
#include <iostream>

#include "Parser.h"
#include "YamlPrinter.h"

int main()
{
	std::ifstream input("./array.json");

	if (!input.is_open()) {
		std::cout << "Unable to open file" << std::endl;
		return 1;
	}

	Json json = Json::Parse(input);
	input.close();

	std::ofstream output("./array.yaml");
	YamlPrinter printer(json, output);
	printer.Print();
	output.close();
}