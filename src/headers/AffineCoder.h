//
// Created by part4 on 10.04.2024.
//

#ifndef KK_L2_AFFINECODER_H
#define KK_L2_AFFINECODER_H

#include "Libraries.h"
#include "Coder.h"

namespace enc {
	class AffineCoder : public Coder {
		vector<char> letters;
		map<char, char> keys_map_{};

		[[nodiscard]] char encodeChar(char in) const override;

		[[nodiscard]] char decodeChar(char in) const override;

		void readKeys();

		void setKeysMap(const map<char, char> &keysMap) {
			this->keys_map_ = keysMap;
		}

		int randomInRange(int min, int max);

		size_t calculateMapHash(map<char, char> mapToHash);
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
