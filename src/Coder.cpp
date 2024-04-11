//
// Created by part4 on 10.04.2024.
//

#include "headers/Coder.h"

namespace enc {
	string Coder::sanitize(const string &in) {
		string sanitized_in;

		for (const auto c: in) {
			if (c >= 97 && c <= 122) {
				sanitized_in += static_cast<char>(std::toupper(c));
				continue;
			}

			if (c >= 65 && c <= 90) {
				sanitized_in += c;
			}
		}

		return sanitized_in;
	}

	string Coder::encode(const string &in) {
		string out;
		for (const auto c: in) {
			const char encoded_char = encodeChar(c);
			out += encoded_char;
		}
		return out;
	}

	string Coder::decode(const string &in)  {
		string out;
		for (const auto c: in) {
			const char decoded_char = decodeChar(c);
			out += decoded_char;
		}
		return out;
	}

}
