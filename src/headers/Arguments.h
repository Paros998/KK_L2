//
// Created by part4 on 13.03.2024.
//

#ifndef ARGUMENTS_H
#define ARGUMENTS_H

#include "Libraries.h"

namespace args {
	static const std::string EnMonogramsFile = "../data/english_monograms.txt";

	static const std::string D_FLAG = "-d";
	static const std::string E_FLAG = "-e";
	static const std::string I_FLAG = "-i";
	static const std::string K_FLAG = "-k";
	static const std::string O_FLAG = "-o";
	static const std::string A_FLAG = "-a";
	static const std::string CA_FLAG = "-ca";
	static const std::string CC_FLAG = "-cc";

	enum flag {
		d, e, i, k, o, a, ca, cc
	};

	static std::map<std::string, flag> FLAGS = {
			{D_FLAG, d},
			{E_FLAG, e},
			{I_FLAG, i},
			{K_FLAG, k},
			{O_FLAG, o},
			{A_FLAG, a},
			{CA_FLAG, ca},
			{CC_FLAG, cc}
	};

	enum CoderType {
		NO_CODER, CESAR, AFFINITY
	};

	enum EncryptMode {
		ENCRYPT, DECRYPT, NONE
	};

	enum CrackEncMode {
		NO_CRACK, BRUTE_FORCE
	};

	class Arguments {
		EncryptMode encrypt_mode_ = EncryptMode::NONE;
		CrackEncMode crack_mode_ = CrackEncMode::NO_CRACK;
		CoderType coder_type_ = CoderType::NO_CODER;
		std::string inputFile_;
		std::string tmpInputFile_ = "../data/tmp.txt";
		std::string outputFile_;
		std::string keyFile_;

	public:
		Arguments(int argc, char const *argv[]);

		[[nodiscard]] EncryptMode encrypt_mode() const {
			return encrypt_mode_;
		}

		[[nodiscard]] std::string input_file() const {
			return inputFile_;
		}

		[[nodiscard]] std::string output_file() const {
			return outputFile_;
		}

		[[nodiscard]] std::string key_file() const {
			return keyFile_;
		}

		[[nodiscard]] CrackEncMode getCrackEncMode() const {
			return crack_mode_;
		}

		[[nodiscard]] std::string tmpInputFile() const {
			return tmpInputFile_;
		}

		[[nodiscard]] CoderType getCoderType() const {
			return coder_type_;
		}

		friend std::ostream &operator<<(std::ostream &os, const Arguments &obj) {
			return os
					<< "[" << std::endl
					<< "encrypt_mode_: " << obj.encrypt_mode_ << std::endl
					<< "inputFile_: " << obj.inputFile_ << std::endl
					<< "outputFile_: " << obj.outputFile_ << std::endl
					<< "keyFile_: " << obj.keyFile_ << std::endl
					<< "analize_mode_: " << obj.crack_mode_ << std::endl
					<< "coder_type_: " << obj.coder_type_ << std::endl
					<< "]" << std::endl;
		}
	};
} // args

#endif //ARGUMENTS_H
