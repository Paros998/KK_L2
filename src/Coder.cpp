//
// Created by part4 on 17.03.2024.
//

#include "headers/Coder.h"

namespace enc {
    char Coder::encodeChar(const char in) const {
		int movedKey = in + this->cesar_key_;
		if (movedKey <= 90) {
			return static_cast<char>(movedKey);
		}

	    return static_cast<char>(65 + (movedKey - 90));
    }

    char Coder::decodeChar(const char in) const {
	    int movedKey = in - this->cesar_key_;
	    if (movedKey >= 65) {
		    return static_cast<char>(movedKey);
	    }

	    return static_cast<char>(90 - (65 - movedKey));
    }

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

    string Coder::encode(const string &in) const {
        string out;
        for (const auto c: in) {
            const char encoded_char = encodeChar(c);
            out += encoded_char;
        }
        return out;
    }

    string Coder::decode(const string &in) const {
        string out;
        for (const auto c: in) {
            const char decoded_char = decodeChar(c);
            out += decoded_char;
        }
        return out;
    }
} // enc