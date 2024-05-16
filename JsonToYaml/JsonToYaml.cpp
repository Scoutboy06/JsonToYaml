#include <fstream>
#include <string>
#include <iostream>

#include "Parser.h"

int main(int argc, char* argv[]) {
	if (argc == 1) {
		std::cout <<
			"JsonToYaml version 1.0.0\n"
			"Use --help or -h to get full help\n";
		return 0;
	}

	if (argv[1] == "--help" || argv[1] == "-h") {
		std::cout <<
			"JsonToYaml version 1.0.0\n"
			"usage: jsontoyaml <input file> <output file>\n";
		return 0;
	}

	if (argc != 3) {
		std::cout <<
			"Invalid usage\n"
			"Use --help or -h to get full help\n";
		return 1;
	}

	std::ifstream input(argv[1]);
	if (!input.is_open()) {
		std::cout << "Unable to open input file: " << argv[1];
		return 1;
	}

	std::ofstream output(argv[2]);
	if (!output.is_open()) {
		std::cout << "Unable to open output file: " << argv[2];
		return 1;
	}
	
	Json json = ParseJson(input);
	input.close();

	YamlPrinter printer(json, output);
	printer.Print();
	output.close();
}