//
// Created by part4 on 10.04.2024.
//

#ifndef KK_L2_AFFINECODER_H
#define KK_L2_AFFINECODER_H

#include "Libraries.h"
#include "Coder.h"
#include "NgramsUtil.h"
#include "App.h"

namespace enc {

	class AffineCoder : public Coder {
		vector<char> letters;
		map<char, char> keys_map_{};

		[[nodiscard]] char encodeChar(char in) const override;

		[[nodiscard]] char decodeChar(char in) const override;

		void readKeys();

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

		const vector<char> &getLetters() const {
			return letters;
		}

		void setKeysMap(const map<char, char> &keysMap) {
			this->keys_map_ = keysMap;
		}

		std::map<char, char> initializeBasicKeyMap() {
			auto keys = map<char, char>();
			for (auto c: letters) {
				keys.insert({c, c});
				keys[c] = c;
			}
			return keys;
		}

		char minMaxForKey(const char key, const map<string, double>& probabilityMap, utils::NgramsUtil &util, ifstream &in);

		~AffineCoder() = default;

	};

} // enc

#endif //KK_L2_AFFINECODER_H
