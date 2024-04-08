//
// Created by part4 on 13.03.2024.
//

#include "headers/Arguments.h"

namespace args {

    Arguments::Arguments(int const argc, char const *argv[]) {
        bool encryptionModeIntitialized = false;

        for (int j = 1; j < argc; ++j) {
            const auto argument = argv[j];

            for (const auto &key: FLAGS | std::views::keys) {
                if (argument == key) {
                    switch (FLAGS[key]) {
                        case e: {
                            this->encrypt_mode_ = ENCRYPT;
                            encryptionModeIntitialized = true;
                            break;
                        }
                        case d: {
                            this->encrypt_mode_ = DECRYPT;
                            encryptionModeIntitialized = true;
                            break;
                        }
                        case i: {
                            if (std::string value = argv[++j]; !value.starts_with('-')) {
                                this->inputFile_ = value;
                                break;
                            }
                            throw std::invalid_argument("Input file not specified.");
                        }
                        case o: {
                            if (std::string value = argv[++j]; !value.starts_with('-')) {
                                this->outputFile_ = value;
                                break;
                            }
                            throw std::invalid_argument("Output file not specified.");
                        }
                        case k: {
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
                        default: break;
                    }
                    break;
                }
            }
        }
        if (!encryptionModeIntitialized && this->crack_mode_ == NO_CRACK) {
            throw std::invalid_argument("Encrypt/Decrypt mode not specified. Check program parameters.");
        }
    }

} // args
