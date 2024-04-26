// File created on: 21.03.2024
#include <iomanip>
#include "headers/App.h"
#include "headers/FileService.h"
#include "headers/NgramsUtil.h"
#include "headers/AffineCoder.h"

using namespace enc;
using namespace files;

// Constructor to initialize App object with arguments
App::App(args::Arguments app_args) : app_args_(std::move(app_args)) {
	std::cout << this->app_args_ << endl; // Print arguments
}

// Function to process input based on encryption or decryption mode
void App::processInput() {
	if (this->app_args_.encrypt_mode() == args::NONE) {
		return; // If no encryption or decryption mode specified, return
	}

	// Depending on the coder type specified in the arguments, create the corresponding coder object
	switch (this->app_args_.getCoderType()) {
		case args::NO_CODER:
			break;
		case args::CESAR:
			this->app_coder_ = new CesarCoder(&this->app_args_);
			break;
		case args::AFFINITY:
			this->app_coder_ = new AffineCoder(&this->app_args_);
			break;
	}

	// Get input and output file handles
	auto if_stream = FileService::getInputHandle(this->app_args_.input_file().c_str());
	auto of_stream = FileService::getOutputHandle(this->app_args_.output_file().c_str());

	string line, processed_line;
	// Process each line of input file
	while (getline(if_stream, line)) {
		if (this->app_args_.encrypt_mode() == args::ENCRYPT) {
			const string sanitized_in = Coder::sanitize(line);
			processed_line = this->app_coder_->encode(sanitized_in); // Encode input line
		} else {
			processed_line = this->app_coder_->decode(line); // Decode input line
		}
		of_stream << processed_line << endl; // Write processed line to output file
	}
	of_stream.close(); // Close output file stream
	if_stream.close(); // Close input file stream

	// Print encryption or decryption completion message
	if (this->app_args_.encrypt_mode() != args::NONE) {
		std::cout << (this->app_args_.encrypt_mode() == args::ENCRYPT ? "Encryption completed." : "Decryption completed");
	}
}

// Function to run the application
void App::run() {
	processInput(); // Process input based on specified mode
	tryToCrackTheEncoding(); // Try to crack the encoding if specified
}

// Function to attempt to crack the encoding
void App::tryToCrackTheEncoding() {
	// If not in encryption or decryption mode or not in brute force crack mode, return
	if (this->app_args_.encrypt_mode() != args::NONE && this->app_args_.getCrackEncMode() != args::BRUTE_FORCE) {
		return;
	}

	// Initialize English n-grams probability data
	const auto enGramsProbability = initializeBaseEnGramsData();

	// Sanitize input and process monograms
	const double totalMonograms = sanitizeFileAndProcessMonograms();

	// Calculate critical chi-square value
	const double criticalValue = gsl_cdf_chisq_Pinv(0.95, totalMonograms);

	// Initialize standard variables
	int iteration = 0;
	double chiSquare;
	std::string line, processed_line;
	utils::NgramsUtil util = utils::NgramsUtil(this->app_args_.getBruteForceNgramsMode());

	// Create coder object based on coder type specified in arguments
	if (this->app_args_.getCoderType() == args::CESAR) {
		this->app_coder_ = new CesarCoder();
	} else {
		this->app_coder_ = new AffineCoder();
	}

	// Read from sanitized input
	ifstream in = files::FileService::getInputHandle(this->app_args_.tmpInputFile().c_str());
	do {
		// Update loop, reset util and ifstream position
		in.clear();
		in.seekg(0, std::ios::beg);
		iteration++;
		util.reset();

		// Initialize new cipher key
		app_coder_->setKeyForIteration(iteration);

		// Decode input
		while (getline(in, line)) {
			processed_line = app_coder_->decode(line);
			// Process decoded line
			util.processLine(processed_line);
		}

		// Test chi-square value
		chiSquare = calculateChiSquare(util, enGramsProbability);

		// Print iteration and chi-square value
		std::cout << "End of iteration: " << iteration << ", and the critical val is:" << criticalValue << ", current chiSquare is:"
		          << std::setprecision(15) << chiSquare << endl;

		// If coder type is Cesar and iteration is greater than or equal to 26, break the loop
		if (this->app_args_.getCoderType() == args::CESAR && iteration >= 26) {
			break;
		}
	} while (chiSquare > criticalValue);

	// If chi-square value is greater than critical value, decipher key not found
	if (chiSquare > criticalValue) {
		std::cout << "Decipher key not found." << endl;
		return;
	}

	// Print decipher information and write final result
	printDecipherInfo(iteration);
	decipherAndWriteFinalResult(*app_coder_, in);

	// Close input file stream
	in.close();
}

// Function to print decipher information
void App::printDecipherInfo(int iteration) const {
	if (app_args_.getCoderType() == args::CESAR) {
		cout << "The cesar encoding has been broken, and the key was: " << iteration << endl;
	} else {
		cout << "The affine encoding has been broken, and the keys were: " << endl;
		// Print keys map for AffineCoder
		for (const auto &[k, v]: dynamic_cast<AffineCoder *>(app_coder_)->getKeysMap()) {
			cout << "Key:" << k << " -> Val:" << v << endl;
		}
	}
}

// Function to initialize base English n-grams data
std::map<std::string, double> App::initializeBaseEnGramsData() {
	// Initialize counter for n-grams and probability map
	auto counter = std::map<std::string, int>();
	auto probabilityMap = std::map<std::string, double>();
	std::int64_t total = 0;
	std::string line;

	// Get file paths and n-grams mode
	const char *grams_file = this->app_args_.getBruteForceNgramsFile().c_str();
	int n_grams_mode = this->app_args_.getBruteForceNgramsMode();

	// Open input file stream
	auto infile = files::FileService::getInputHandle(grams_file);

	// Read and process each line of the file
	while (getline(infile, line)) {
		// Check if line contains valid n-grams data
		if (line.size() >= n_grams_mode + 2) {
			// Extract n-gram expression and count
			const auto expr = line.substr(0, n_grams_mode);
			const int count = std::stoi(line.substr(n_grams_mode + 1));

			// Update total count and insert into counter
			counter.insert({expr, count});
			total += count;
		}
	}

	// Close input file stream
	infile.close();

	// Calculate probability for each n-gram and insert into probability map
	double probability;
	for (const auto &[ngram, count]: counter) {
		probability = static_cast<double>(count) / static_cast<double>(total);
		probabilityMap.insert({ngram, probability});
	}

	return probabilityMap;
}

// Function to calculate the chi-square value
double App::calculateChiSquare(utils::NgramsUtil &util, const std::map<std::string, double> &probabilityMap) {
	// Initialize chi-square value
	double chi = 0.0;

	// Get total grams count and tested text grams counter
	const auto totalGrams = util.getTotal();
	const auto &tested_text_grams_counter = util.getCounter();

	// Calculate chi-square for each n-gram
	for (const auto &[ngram, count]: tested_text_grams_counter) {
		// Get example probability from probability map
		double example_probability = probabilityMap.find(ngram)->second;

		// Calculate expected count
		double expected_count = static_cast<double>(totalGrams) * example_probability;

		// Calculate X^2
		auto power = static_cast<double>(std::pow(static_cast<double>(count) - expected_count, 2));
		double x_2 = expected_count == 0 ? 0.0 : power / expected_count;

		// Update chi-square
		chi += x_2;
	}

	return chi;
}

// Function to decipher the input file using the provided coder and write the final result to an output file
void App::decipherAndWriteFinalResult(enc::Coder &coder, std::ifstream &in) {
	std::string line, processed_line;

	// Open output file for writing the deciphered data
	std::ofstream of = files::FileService::getOutputHandle(this->app_args_.output_file().c_str());

	// Reset file stream to the beginning
	in.clear();
	in.seekg(0, std::ios::beg);

	// Decode each line of the input file and write the deciphered data to the output file
	while (getline(in, line)) {
		processed_line = coder.decode(line);
		of << processed_line << std::endl;
	}

	// Close the output file
	of.close();
}

// Function to sanitize the input file and process monograms, returning the total count of monograms
double App::sanitizeFileAndProcessMonograms() {
	std::string line;
	utils::NgramsUtil util = utils::NgramsUtil(this->app_args_.getBruteForceNgramsMode());

	// Open input and output files
	std::ifstream in = files::FileService::getInputHandle(this->app_args_.input_file().c_str());
	std::ofstream of = files::FileService::getOutputHandle(this->app_args_.tmpInputFile().c_str());

	// Sanitize the input file and process each line
	while (getline(in, line)) {
		const std::string sanitized_in = Coder::sanitize(line);

		// Process sanitized line
		util.processLine(sanitized_in);
		of << sanitized_in << std::endl;
	}

	// Close input and output files
	of.close();
	in.close();

	// Return the total count of monograms
	return static_cast<double>(util.getTotal());
}

