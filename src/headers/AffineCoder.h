// File created on: 10.04.2024
// Header guard to prevent multiple inclusion of this header file
#ifndef KK_L2_AFFINECODER_H
#define KK_L2_AFFINECODER_H

// Including necessary header files
#include "Libraries.h" // Including external libraries
#include "Coder.h" // Including the base class definition

namespace enc {
	// Custom hash function for pairs
	struct pair_hash {
		// Operator overload for computing hash value of pairs
		template<class T1, class T2>
		std::size_t operator () (const std::pair<T1,T2> &pair) const {
			auto hash1 = my_hash<T1>{}(pair.first);
			auto hash2 = std::hash<T2>{}(pair.second);
			// Improved combining hash function
			return hash1 ^ (hash2 + 0x9e3779b9 + (hash1 << 6) + (hash1 >> 2));
		}

	private:
		// Custom hash function for const char keys
		template<typename T>
		struct my_hash {
			std::size_t operator () (T key) const {
				return static_cast<std::size_t>(key);
			}
		};
	};

	// Class for Affine Encoder, inheriting from base Coder class
	class AffineCoder : public Coder {
		// Vector to store used key map hashes
		vector<std::size_t> used_key_map_hashes_;
		// Vector to store characters
		vector<char> letters;
		// Map to store keys
		map<char, char> keys_map_{};

		// Override functions to encode and decode characters
		[[nodiscard]] char encodeChar(char in) const override;
		[[nodiscard]] char decodeChar(char in) const override;

		// Function to read keys from input
		void readKeys();
		// Function to set keys map
		void setKeysMap(const map<char, char> &keysMap) {
			this->keys_map_ = keysMap;
		}
		// Function to generate random number in given range
		static int randomInRange(int min, int max);
		// Function to calculate hash of map
		static size_t calculateMapHash(map<char, char> &mapToHash);
		// Function to randomize keys map
		map<char, char> &randomizeKeyMap(map<char, char> &keysMap);

	public:
		// Constructors
		explicit AffineCoder() {
			// Initializing letters vector with characters
			for (int i = 65; i <= 90; i++) {
				letters.push_back(static_cast<char>(i));
			}
		};
		explicit AffineCoder(args::Arguments *args) : Coder(args) {
			// Initializing AffineCoder object with arguments
			readKeys();
		};

		// Function to get keys map
		[[nodiscard]] const map<char, char> &getKeysMap() const {
			return keys_map_;
		}
		// Function to set key for iteration
		void setKeyForIteration(int i) override;

		// Destructor
		~AffineCoder() = default;

	};

} // enc

#endif //KK_L2_AFFINECODER_H
