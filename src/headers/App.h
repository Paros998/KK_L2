// File created on: 21.03.2024
// Header guard to prevent multiple inclusion of this header file
#ifndef APP_H
#define APP_H

// Including necessary header files
#include "Arguments.h"
#include "CesarCoder.h"
#include "FileService.h"
#include "NgramsUtil.h"

// Class declaration for the main application
class App {
	args::Arguments app_args_; // Object to store application arguments
	enc::Coder *app_coder_{}; // Pointer to encoder object

	// Function to initialize base English n-grams data
	std::map<std::string, double> initializeBaseEnGramsData();
	// Function to process input
	void processInput();
	// Function to attempt cracking the encoding
	void tryToCrackTheEncoding();
	// Function to calculate Chi-square value
	static double calculateChiSquare(utils::NgramsUtil &util, const map<std::string, double>& probabilityMap);
	// Function to decipher and write the final result
	void decipherAndWriteFinalResult(enc::Coder &coder, ifstream &in);
	// Function to sanitize file and process monograms
	double sanitizeFileAndProcessMonograms();
	// Function to print decipher information
	void printDecipherInfo(int iteration) const;

public:
	// Constructor
	explicit App(args::Arguments app_args);
	// Function to run the application
	void run();
	// Destructor
	~App() {
		delete this->app_coder_;
	};
};

#endif //APP_H
