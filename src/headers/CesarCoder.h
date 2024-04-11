//
// Created by part4 on 17.03.2024.
//

#ifndef CODER_H
#define CODER_H

#include "Libraries.h"
#include "Coder.h"

using namespace std;

namespace enc {
	class CesarCoder : public Coder{
		int cesar_key_{};

		[[nodiscard]] char encodeChar(char in) const override;

		[[nodiscard]] char decodeChar(char in) const override;

		void extractKey();
	public:
		explicit CesarCoder(const int cesarKey) {
			this->cesar_key_ = cesarKey;
		};

		explicit CesarCoder(args::Arguments *args) : Coder(args) {
			extractKey();
		};

		void setCesarKey(int cesarKey) {
			cesar_key_ = cesarKey;
		}

		~CesarCoder() = default;
	};
} // enc

#endif //CODER_H
