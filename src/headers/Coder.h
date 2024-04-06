//
// Created by part4 on 17.03.2024.
//

#ifndef CODER_H
#define CODER_H

#include "Libraries.h"

using namespace std;

namespace enc {
    class Coder {
        int cesar_key_;

        [[nodiscard]] char encodeChar(char in) const;


        [[nodiscard]] char decodeChar(char in) const;

    public:
        explicit Coder(const int key) {
            this->cesar_key_ = key;
        };

        [[nodiscard]] string encode(const string& in) const;

        [[nodiscard]] string decode(const string& in) const;

        [[nodiscard]] static string sanitize(const string& in);

        ~Coder() = default;
    };
} // enc

#endif //CODER_H
