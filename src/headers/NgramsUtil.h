// File created on: 22.03.2024
// Header guard to prevent multiple inclusion of this header file
#ifndef NGRAMSUTIL_H
#define NGRAMSUTIL_H

// Including necessary header files
#include "Libraries.h"
#include "FileService.h"

// Namespace for utility functions
namespace utils {
	// Class for handling n-grams utility operations
	class NgramsUtil {
		std::map<const std::string, int> counter_; // Map to store n-grams counts
		std::int64_t total_ = 0; // Total count of n-grams
		int mode_; // Mode for n-grams processing

	public:
		// Constructor with mode parameter
		explicit NgramsUtil(const int mode) {
			this->mode_ = mode;
			this->counter_ = std::map<const std::string, int>();
		};

		// Getter method for n-grams counter map
		[[nodiscard]] const std::map<const std::string, int> &getCounter() const;
		// Getter method for total count of n-grams
		[[nodiscard]] int64_t getTotal() const;

		// Function to process a line of text and update n-grams counts
		void processLine(const std::string &line);
		// Function to reset n-grams counts
		void reset();

		// Destructor
		~NgramsUtil() = default;
	};
}

#endif //NGRAMSUTIL_H
