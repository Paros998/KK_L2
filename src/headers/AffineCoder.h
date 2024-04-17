//
// Created by part4 on 10.04.2024.
//

#ifndef KK_L2_AFFINECODER_H
#define KK_L2_AFFINECODER_H

#include "Libraries.h"
#include "Coder.h"

namespace enc {
	struct pair_hash {
		template<class T1, class T2>
		std::size_t operator () (const std::pair<T1,T2> &pair) const {
			auto hash1 = my_hash<T1>{}(pair.first);
			auto hash2 = std::hash<T2>{}(pair.second);
			return hash1 ^ (hash2 + 0x9e3779b9 + (hash1 << 6) + (hash1 >> 2)); // Improved combining hash function
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

	class AffineCoder : public Coder {
		vector<std::size_t> used_key_map_hashes_;
		vector<char> letters;
		map<char, char> keys_map_{};

		[[nodiscard]] char encodeChar(char in) const override;

		[[nodiscard]] char decodeChar(char in) const override;

		void readKeys();

		void setKeysMap(const map<char, char> &keysMap) {
			this->keys_map_ = keysMap;
		}

		int randomInRange(int min, int max);

		size_t calculateMapHash(map<char, char> &mapToHash);

		map<char, char> &randomizeKeyMap(map<char, char> &keysMap);

	public:
		explicit AffineCoder() {
			for (int i = 65; i <= 90; i++) {
				letters.push_back(static_cast<char>(i));
			}
		};

		explicit AffineCoder(args::Arguments *args) : Coder(args) {
			readKeys();
		};

		[[nodiscard]] const map<char, char> &getKeysMap() const {
			return keys_map_;
		}

		void setKeyForIteration(int i) override;

		~AffineCoder() = default;

	};

} // enc

#endif //KK_L2_AFFINECODER_H
