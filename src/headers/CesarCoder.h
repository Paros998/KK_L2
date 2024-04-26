// File created on: 17.03.2024
// Header guard to prevent multiple inclusion of this header file
#ifndef CODER_H
#define CODER_H

// Including necessary header files
#include "Libraries.h"
#include "Coder.h"

// Using standard namespace
using namespace std;

namespace enc {
	// Class declaration for Cesar Cipher encoder, inheriting from base Coder class
	class CesarCoder : public Coder {
		int cesar_key_; // Key for Cesar Cipher

		// Override functions to encode and decode characters
		[[nodiscard]] char encodeChar(char in) const override;
		[[nodiscard]] char decodeChar(char in) const override;

		// Function to extract key from arguments
		void extractKey();
		// Function to set Cesar key
		void setCesarKey(int cesarKey) {
			cesar_key_ = cesarKey;
		}

	public:
		// Constructors
		explicit CesarCoder() = default; // Default constructor
		explicit CesarCoder(args::Arguments *args) : Coder(args) {
			// Constructor with arguments
			extractKey();
		};

		// Function to set key for iteration
		void setKeyForIteration(int i) override {
			setCesarKey(i);
		}

		// Destructor
		~CesarCoder() = default;
	};
} // enc

#endif //CODER_H
