//
// Created by part4 on 17.03.2024.
//

#include "headers/CesarCoder.h"
#include "headers/FileService.h"

namespace enc {
	char CesarCoder::encodeChar(const char in) const {
		int movedKey = in + this->cesar_key_;
		if (movedKey <= 90) {
			return static_cast<char>(movedKey);
		}

		return static_cast<char>(65 + ((movedKey - 90) % 26));
	}

	char CesarCoder::decodeChar(const char in) const {
		int movedKey = in - this->cesar_key_;
		if (movedKey >= 65) {
			return static_cast<char>(movedKey);
		}

		return static_cast<char>(90 - ((65 - movedKey) % 26));
	}

	void CesarCoder::extractKey() {
		this->cesar_key_ = files::FileService::readKey(this->args_->key_file().c_str());
	}
} // enc
