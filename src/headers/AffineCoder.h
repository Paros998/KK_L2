//
// Created by part4 on 10.04.2024.
//

#ifndef KK_L2_AFFINECODER_H
#define KK_L2_AFFINECODER_H

#include "Libraries.h"
#include "Coder.h"

namespace enc {

	class AffineCoder : public Coder {
		map<char, char> keys_map_;

		[[nodiscard]] char encodeChar(char in) const override;

		[[nodiscard]] char decodeChar(char in) const override;

		void readKeys();

	public:
		explicit AffineCoder(const map<char, char> &keysMap) {
			this->keys_map_ = keysMap;
		}

		explicit AffineCoder(args::Arguments *args) : Coder(args) {
			readKeys();
		};

		void setKeysMap(const map<char, char> &keysMap) {
			this->keys_map_ = keysMap;
		}

		~AffineCoder() = default;
	};

} // enc

#endif //KK_L2_AFFINECODER_H
