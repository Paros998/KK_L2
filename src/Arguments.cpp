//
// Created by part4 on 13.03.2024.
//

#include "headers/Arguments.h"

namespace args {

	// Constructor for Arguments class to parse command-line arguments
	Arguments::Arguments(int const argc, char const *argv[]) {
		bool encryptionModeInitialized = false;
		bool coderSpecified = false;

		// Iterate through command-line arguments
		for (int j = 1; j < argc; ++j) {
			const auto argument = argv[j];

			// Iterate through defined flags
			for (const auto &key: FLAGS | std::views::keys) {
				if (argument == key) {
					switch (FLAGS[key]) {
						case e: {
							this->encrypt_mode_ = ENCRYPT;
							encryptionModeInitialized = true;
							break;
						}
						case d: {
							this->encrypt_mode_ = DECRYPT;
							encryptionModeInitialized = true;
							break;
						}
						case i: {
							// Check if the next argument is a file name
							if (std::string value = argv[++j]; !value.starts_with('-')) {
								this->inputFile_ = value;
								break;
							}
							throw std::invalid_argument("Input file not specified.");
						}
						case o: {
							// Check if the next argument is a file name
							if (std::string value = argv[++j]; !value.starts_with('-')) {
								this->outputFile_ = value;
								break;
							}
							throw std::invalid_argument("Output file not specified.");
						}
						case k: {
							// Check if the next argument is a file name
							if (j + 1 < argc) {
								if (std::string value = argv[++j]; !value.starts_with('-')) {
									this->keyFile_ = value;
									break;
								}
							}
							throw std::invalid_argument("Key file not specified.");
						}
						case a: {
							if (j + 1 < argc) {
								if (std::string value = argv[++j]; !value.starts_with('-')) {
									if (value == "bf") {
										this->crack_mode_ = BRUTE_FORCE;
									}

									if (this->crack_mode_ == NO_CRACK) {
										throw std::invalid_argument("Crack encoding mode not specified.");
									}
									break;
								}
							}
							break;
						}
						case ca: {
							this->coder_type_ = AFFINITY;
							coderSpecified = true;
							break;
						}
						case cc: {
							this->coder_type_ = CESAR;
							coderSpecified = true;
							break;
						}
						case n1: {
							this->brute_force_ngrams_mode = 1;
							this->brute_force_ngrams_file = EnMonogramsFile;
							break;
						}
						case n2: {
							this->brute_force_ngrams_mode = 2;
							this->brute_force_ngrams_file = EnBigramsFile;
							break;
						}
						case n3: {
							this->brute_force_ngrams_mode = 3;
							this->brute_force_ngrams_file = EnTrigramsFile;
							break;
						}
						case n4: {
							this->brute_force_ngrams_mode = 4;
							this->brute_force_ngrams_file = EnQuadgramsFile;
							break;
						}
						default:
							break;
					}
					break;
				}
			}
		}

		// Check if encryption mode, coder type, and crack mode are specified
		if (!encryptionModeInitialized && !coderSpecified && this->crack_mode_ == NO_CRACK) {
			throw std::invalid_argument("Encrypt/Decrypt mode not specified. Check program parameters.");
		}
	}
}