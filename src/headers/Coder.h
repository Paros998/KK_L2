// File created on: 10.04.2024
// Header guard to prevent multiple inclusion of this header file
#ifndef KK_L2_CODER_H
#define KK_L2_CODER_H

// Including necessary header files
#include "Libraries.h"
#include "Arguments.h"

// Using standard namespace
using namespace std;

namespace enc {
	// Base class for encoding and decoding text
	class Coder {
		// Virtual functions for encoding and decoding characters
		[[nodiscard]] virtual char encodeChar(char in) const {
			return in;
		};
		[[nodiscard]] virtual char decodeChar(char in) const {
			return in;
		};

	protected:
		args::Arguments *args_{}; // Pointer to argument object

	public:
		// Constructors
		Coder() = default; // Default constructor
		explicit Coder(args::Arguments *args) : args_(args) {}; // Constructor with arguments

		// Static function to sanitize input string
		static string sanitize(const string &in);

		// Function to decode input string
		string decode(const string &in);
		// Function to encode input string
		string encode(const string &in);

		// Pure virtual function to set key for iteration
		virtual void setKeyForIteration(int i) = 0;

		// Destructor
		~Coder() = default;
	};

} // enc

#endif //KK_L2_CODER_H
