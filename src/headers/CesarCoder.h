//
// Created by part4 on 17.03.2024.
//

#ifndef CODER_H
#define CODER_H

#include "Libraries.h"

using namespace std;

namespace enc {
	class CesarCoder {
		int cesar_key_;

		[[nodiscard]] char encodeChar(char in) const;


		[[nodiscard]] char decodeChar(char in) const;

	public:
		explicit CesarCoder(const int key) {
			this->cesar_key_ = key;
		};

		[[nodiscard]] string encode(const string &in) const;

		[[nodiscard]] string decode(const string &in) const;

		[[nodiscard]] static string sanitize(const string &in);

		void setCesarKey(int cesarKey) {
			cesar_key_ = cesarKey;
		}

		~CesarCoder() = default;
	};
} // enc

#endif //CODER_H
