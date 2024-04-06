//
// Created by part4 on 13.03.2024.
//

#ifndef ARGUMENTS_H
#define ARGUMENTS_H

#include "Libraries.h"

namespace args {
    static const std::string D_FLAG = "-d";
    static const std::string E_FLAG = "-e";
    static const std::string I_FLAG = "-i";
    static const std::string K_FLAG = "-k";
    static const std::string O_FLAG = "-o";
    static const std::string A_FLAG = "-a";

    enum flag {
        d, e, i, k, o, a
    };

    static std::map<std::string, flag> FLAGS = {
        {D_FLAG, d}, {E_FLAG, e}, {I_FLAG, i}, {K_FLAG, k}, {O_FLAG, o}, {A_FLAG, a}
    };

    enum EncryptMode {
        ENCRYPT, DECRYPT, NONE
    };

    class Arguments {
        EncryptMode encrypt_mode_ = EncryptMode::NONE;
        std::string inputFile_;
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

        friend std::ostream &operator<<(std::ostream &os, const Arguments &obj) {
            return os
                   << "[" << std::endl
                   << "encrypt_mode_: " << obj.encrypt_mode_ << std::endl
                   << "inputFile_: " << obj.inputFile_ << std::endl
                   << "outputFile_: " << obj.outputFile_ << std::endl
                   << "keyFile_: " << obj.keyFile_ << std::endl
                   << "]" << std::endl;
        }
    };
} // args

#endif //ARGUMENTS_H
