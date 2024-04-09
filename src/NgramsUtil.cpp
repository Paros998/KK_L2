//
// Created by part4 on 22.03.2024.
//

#include "headers/NgramsUtil.h"

#include "headers/Arguments.h"

using namespace std;

namespace utils {
	void NgramsUtil::processLine(const string &line) {
		for (int i = 0; i < line.size(); i++) {
			if (i + this->mode_ >= line.size()) {
				return;
			}

			string expr = line.substr(i, this->mode_);

			if (const auto find = this->counter_.find(expr); find == this->counter_.end()) {
				auto pair = std::pair<const string, int>(expr.c_str(), 1);
				this->counter_.insert(pair);
			} else {
				find->second += 1;
			}

			this->total_++;
		}
	}

	const map<const std::string, int> &NgramsUtil::getCounter() const {
		return counter_;
	}

	int64_t NgramsUtil::getTotal() const {
		return total_;
	}

	void NgramsUtil::reset() {
		this->total_ = 0;
		this->counter_.clear();
	}
}
