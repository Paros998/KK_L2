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

	int AffineCoder::randomInRange(int min, int max) {
		std::random_device rd;
		std::mt19937 eng(rd()); // Seed the generator
		std::uniform_int_distribution<> distribution(min, max); // Define the range

		return distribution(eng); // Generate the random number
	}

	void AffineCoder::setIteration(int i) {
		char randomSign;

		// randomize and set keys map
		auto keysMap = std::map<char, char>();
		vector<char> lettersUsed;

		for (const auto c: this->letters) {
			int pos;
			randomSign = -1;
			do {
				randomSign = randomInRange(65, 90);
			} while (randomSign == c && std::binary_search(lettersUsed.begin(), lettersUsed.end(), randomSign));

			keysMap.insert({c, randomSign});
			lettersUsed.push_back(randomSign);
			std::sort(lettersUsed.begin(), lettersUsed.end());
		}

		this->setKeysMap(keysMap);
	}

	} // enc