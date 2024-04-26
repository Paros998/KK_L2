// File created on: 10.04.2024
#include "headers/AffineCoder.h"

namespace enc {
	// Function to encode a character using Affine Cipher
	char AffineCoder::encodeChar(const char in) const {
		// Find the replacement character in the keys map
		const auto find = this->keys_map_.find(in);
		// If replacement character found, return it, otherwise return original character
		if (find->second == 0) return in;
		return find->second;
	}

	// Function to decode a character using Affine Cipher
	char AffineCoder::decodeChar(const char in) const {
		// Iterate over keys map to find the original character
		for (auto [key, value]: this->keys_map_) {
			if (value == in) return key;
		}
		// If original character not found, return input character
		return in;
	}

	// Function to read keys from file
	void AffineCoder::readKeys() {
		// Open key file
		ifstream infile(this->args_->key_file());
		string line;
		// Read each line and extract original and replacement characters
		while (getline(infile, line)) {
			if (line.size() == 3) {
				const auto original_key = line.substr(0, 1);
				const auto replacement = line.substr(2, 1);
				// Insert into keys map
				this->keys_map_.insert({
						                       static_cast<char>(std::toupper(original_key[0])),
						                       static_cast<char>(std::toupper(replacement[0]))
				                       });
			}
		}
		// Close file
		infile.close();
	}

	// Function to generate a random number in a given range
	int AffineCoder::randomInRange(int min, int max) {
		// Seed random number generator
		std::random_device rd;
		std::mt19937 eng(rd());
		// Define distribution
		std::uniform_int_distribution<> distribution(min, max);
		// Generate random number
		return distribution(eng);
	}

	// Function to calculate hash value of map
	std::size_t AffineCoder::calculateMapHash(map<char, char> &m) {
		pair_hash elem_hash;
		std::size_t hash_value = 0;

		// Combine hash values using XOR and multiplication
		for (const auto &elem : m) {
			hash_value = (hash_value * 37) ^ elem_hash(elem);
		}

		return hash_value;
	}

	// Function to set key for iteration
	void AffineCoder::setKeyForIteration(int i) {
		std:size_t keysHash;

		std::map<char, char> keysMap;

		// Randomize original keysMap
		do {
			keysMap = randomizeKeyMap(keysMap);
			keysHash = calculateMapHash(keysMap);
		} while (std::binary_search(this->used_key_map_hashes_.begin(), this->used_key_map_hashes_.end(), keysHash));

		// Add keys hash to used hashes vector
		this->used_key_map_hashes_.push_back(keysHash);
		// Sort used hashes vector
		std::sort(this->used_key_map_hashes_.begin(), this->used_key_map_hashes_.end());
		// Set keys map
		this->setKeysMap(keysMap);
	}

	// Function to randomize keys map
	map<char, char> &AffineCoder::randomizeKeyMap(map<char, char> &keysMap) {
		char randomSign;
		keysMap = map<char, char>();
		vector<int> lettersUsed;

		// Iterate over letters and assign random replacement characters
		for (const auto c: letters) {
			randomSign = -1;
			// Generate random replacement character not already used
			do {
				randomSign = static_cast<char>(randomInRange(65, 90));
			} while (binary_search(lettersUsed.begin(), lettersUsed.end(), static_cast<int>(randomSign)));

			// Insert into keys map and add to used letters vector
			keysMap.insert({c, randomSign});
			lettersUsed.push_back(static_cast<int>(randomSign));
			sort(lettersUsed.begin(), lettersUsed.end());
		}
		return keysMap;
	}

} // enc
