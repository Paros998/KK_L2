// File created on: 13.03.2024
// Header guard to prevent multiple inclusion of this header file
#ifndef FILEREADER_H
#define FILEREADER_H

// Including necessary header files
#include "Libraries.h"
#include "Arguments.h"

// Namespace for file-related operations
namespace files {
	// Class for file handling operations
	class FileService {
	public:
		// Function to read key from file
		static int readKey(const char *file);
		// Function to get input file handle
		static std::ifstream getInputHandle(const char *file);
		// Function to get output file handle
		static std::ofstream getOutputHandle(const char *file);
	};

} // files

#endif //FILEREADER_H
