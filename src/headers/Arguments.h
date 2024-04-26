// File created on: 13.03.2024
// Header guard to prevent multiple inclusion of this header file
#ifndef ARGUMENTS_H
#define ARGUMENTS_H

// Including necessary header files
#include "Libraries.h"

// Namespace for handling command line arguments
namespace args {
	// File paths for English n-grams data
	static const std::string EnMonogramsFile = "../data/grams/english_monograms.txt";
	static const std::string EnBigramsFile = "../data/grams/english_bigrams.txt";
	static const std::string EnTrigramsFile = "../data/grams/english_trigrams.txt";
	static const std::string EnQuadgramsFile = "../data/grams/english_quadgrams.txt";

	// Command line flags
	static const std::string D_FLAG = "-d";
	static const std::string E_FLAG = "-e";
	static const std::string I_FLAG = "-i";
	static const std::string K_FLAG = "-k";
	static const std::string O_FLAG = "-o";
	static const std::string A_FLAG = "-a";
	static const std::string CA_FLAG = "-ca";
	static const std::string CC_FLAG = "-cc";
	static const std::string N1_FLAG = "-n1";
	static const std::string N2_FLAG = "-n2";
	static const std::string N3_FLAG = "-n3";
	static const std::string N4_FLAG = "-n4";

	// Enumeration for command line flags
	enum flag {
		d, e, i, k, o, a, ca, cc, n1, n2, n3, n4
	};

	// Map for command line flags and their corresponding enum values
	static std::map<std::string, flag> FLAGS = {
			{D_FLAG, d},
			{E_FLAG, e},
			{I_FLAG, i},
			{K_FLAG, k},
			{O_FLAG, o},
			{A_FLAG, a},
			{CA_FLAG, ca},
			{CC_FLAG, cc},
			{N1_FLAG, n1},
			{N2_FLAG, n2},
			{N3_FLAG, n3},
			{N4_FLAG, n4}
	};

	// Enumeration for encoder types
	enum CoderType {
		NO_CODER, CESAR, AFFINITY
	};

	// Enumeration for encryption modes
	enum EncryptMode {
		NONE, ENCRYPT, DECRYPT
	};

	// Enumeration for crack encoding modes
	enum CrackEncMode {
		NO_CRACK, BRUTE_FORCE
	};

	// Class to handle command line arguments
	class Arguments {
		EncryptMode encrypt_mode_ = EncryptMode::NONE; // Encryption mode
		CrackEncMode crack_mode_ = CrackEncMode::NO_CRACK; // Crack encoding mode
		CoderType coder_type_ = CoderType::NO_CODER; // Encoder type
		int brute_force_ngrams_mode = -1; // Brute force n-grams mode
		std::string brute_force_ngrams_file; // Brute force n-grams file path
		std::string inputFile_; // Input file path
		std::string tmpInputFile_ = "../data/tmp.txt"; // Temporary input file path
		std::string outputFile_; // Output file path
		std::string keyFile_; // Key file path

	public:
		// Constructor to initialize arguments based on command line inputs
		Arguments(int argc, char const *argv[]);

		// Getter methods for various arguments
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

		[[nodiscard]] int getBruteForceNgramsMode() const {
			return brute_force_ngrams_mode;
		}

		[[nodiscard]] const std::string &getBruteForceNgramsFile() const {
			return brute_force_ngrams_file;
		}

		// Overloaded stream insertion operator to print argument values
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
