//
// Created by part4 on 22.03.2024.
//

#include "headers/NgramsUtil.h"   // Include the header file for NgramsUtil
#include "headers/Arguments.h"    // Include the header file for Arguments (if needed)

using namespace std;

namespace utils {
	// Process a single line of text to extract n-grams and update their frequencies
	void NgramsUtil::processLine(const string &line) {
		for (int i = 0; i < line.size(); i++) {
			// Ensure there are enough characters left in the line to form an n-gram
			if (i + this->mode_ >= line.size()) {
				return;
			}

			// Extract the n-gram from the current position in the line
			string expr = line.substr(i, this->mode_);

			// Update the frequency count for the extracted n-gram
			if (const auto find = this->counter_.find(expr); find == this->counter_.end()) {
				// If the n-gram is not found in the counter, add it with frequency 1
				auto pair = std::pair<const string, int>(expr.c_str(), 1);
				this->counter_.insert(pair);
			} else {
				// If the n-gram is already in the counter, increment its frequency
				find->second += 1;
			}

			// Increment the total count of processed n-grams
			this->total_++;
		}
	}

	// Get the map containing n-gram frequencies
	const map<const std::string, int> &NgramsUtil::getCounter() const {
		return counter_;
	}

	// Get the total count of processed n-grams
	int64_t NgramsUtil::getTotal() const {
		return total_;
	}

	// Reset the internal state of the NgramsUtil object
	void NgramsUtil::reset() {
		this->total_ = 0;
		this->counter_.clear();
	}
}
