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

	std::size_t AffineCoder::calculateMapHash(map<char, char> &m) {
		pair_hash elem_hash;
		std::size_t hash_value = 0;

		// Combine hash values using XOR and multiplication
		for (const auto &elem : m) {
			hash_value = (hash_value * 37) ^ elem_hash(elem);
		}

		return hash_value;
	}

	void AffineCoder::setKeyForIteration(int i) {
		std:size_t keysHash;

		std::map<char, char> keysMap;

		// randomize original keysMap not yet tested
		do {
			keysMap = randomizeKeyMap(keysMap);
			keysHash = calculateMapHash(keysMap);
		} while (std::binary_search(this->used_key_map_hashes_.begin(), this->used_key_map_hashes_.end(), keysHash));

		this->used_key_map_hashes_.push_back(keysHash);
//		std::sort(this->used_key_map_hashes_.begin(), this->used_key_map_hashes_.end());
		this->setKeysMap(keysMap);
	}

	map<char, char> &AffineCoder::randomizeKeyMap(map<char, char> &keysMap) {
		char randomSign;
		keysMap = map<char, char>();
		vector<int> lettersUsed;

		for (const auto c: letters) {
			randomSign = -1;
			do {
				randomSign = randomInRange(65, 90);
			} while (binary_search(lettersUsed.begin(), lettersUsed.end(), static_cast<int>(randomSign)));

			keysMap.insert({c, randomSign});
			lettersUsed.push_back(static_cast<int>(randomSign));
			sort(lettersUsed.begin(), lettersUsed.end());
		}
		return keysMap;
	}

} // enc