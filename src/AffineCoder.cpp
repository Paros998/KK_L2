//
// Created by part4 on 10.04.2024.
//

#include "headers/AffineCoder.h"

namespace enc {

	char AffineCoder::encodeChar(const char in) const {
		const auto find = this->keys_map_.find(in);
		if (find->second == 0) return in;
		return find->second;
	}

	char AffineCoder::decodeChar(const char in) const {
		for (auto [key, value]: this->keys_map_) {
			if (value == in) return key;
		}
		return in;
	}

	void AffineCoder::readKeys() {
		ifstream infile(this->args_->key_file());
		string line;
		while (getline(infile, line)) {
			if (line.size() == 3) {
				const auto original_key = line.substr(0, 1);
				const auto replacement = line.substr(2, 1);
				this->keys_map_.insert({
					static_cast<char>(std::toupper(original_key[0])),
					static_cast<char>(std::toupper(replacement[0]))
				});
			}
		}
		infile.close();
	}

} // enc