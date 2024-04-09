//
// Created by part4 on 13.03.2024.
//

#include "headers/FileService.h"

using namespace std;

namespace files {
	int FileService::readKey(const char *file) {
		int key = 0;

		ifstream infile(file);
		string line;
		if (getline(infile, line)) {
			key = std::stoi(line);
		}
		infile.close();

		return key;
	}

	std::ifstream FileService::getInputHandle(const char *file) {
		return ifstream(file);
	}

	std::ofstream FileService::getOutputHandle(const char *file) {
		return ofstream(file);
	}

} // args
