//
// Created by part4 on 13.03.2024.
//

#include "headers/FileService.h"

using namespace std;

namespace files {
	// Function to read an integer key from a file
	int FileService::readKey(const char *file) {
		int key = 0;

		ifstream infile(file);
		string line;
		if (getline(infile, line)) {
			key = std::stoi(line); // Convert string to integer
		}
		infile.close();

		return key;
	}

	// Function to get an input file stream handle
	std::ifstream FileService::getInputHandle(const char *file) {
		return ifstream(file);
	}

	// Function to get an output file stream handle
	std::ofstream FileService::getOutputHandle(const char *file) {
		return ofstream(file);
	}

} // args
