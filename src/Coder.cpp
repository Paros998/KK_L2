//
// Created by part4 on 10.04.2024.
//

#include "headers/Coder.h"

namespace enc {
	// Function to sanitize a string by removing non-alphabetic characters and converting lowercase letters to uppercase
	string Coder::sanitize(const string &in) {
		string sanitized_in;

		for (const auto c: in) {
			if (c >= 97 && c <= 122) { // Check if the character is lowercase
				sanitized_in += static_cast<char>(std::toupper(c)); // Convert to uppercase
				continue;
			}

			if (c >= 65 && c <= 90) { // Check if the character is uppercase
				sanitized_in += c;
			}
		}

		return sanitized_in;
	}

	// Function to encode a string
	string Coder::encode(const string &in) {
		string out;
		for (const auto c: in) {
			const char encoded_char = encodeChar(c);
			out += encoded_char;
		}
		return out;
	}

	// Function to decode a string
	string Coder::decode(const string &in)  {
		string out;
		for (const auto c: in) {
			const char decoded_char = decodeChar(c);
			out += decoded_char;
		}
		return out;
	}

}
