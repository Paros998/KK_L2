//
// Created by part4 on 10.04.2024.
//

#ifndef KK_L2_CODER_H
#define KK_L2_CODER_H

#include "Libraries.h"
#include "Arguments.h"

using namespace std;

namespace enc {
	class Coder {
		[[nodiscard]] virtual char encodeChar(char in) const {
			return in;
		};

		[[nodiscard]] virtual char decodeChar(char in) const {
			return in;
		};

	protected:
		args::Arguments *args_{};

	public:
		Coder() = default;

		explicit Coder(args::Arguments *args) : args_(args) {};

		static string sanitize(const string &in);

		string decode(const string &in);

		string encode(const string &in);

		~Coder() = default;
	};

}
#endif //KK_L2_CODER_H
