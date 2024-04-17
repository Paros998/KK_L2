//
// Created by part4 on 21.03.2024.
//

#include <fenv.h>
#include <iomanip>
#include "headers/App.h"
#include "headers/FileService.h"
#include "headers/NgramsUtil.h"
#include "headers/AffineCoder.h"

using namespace enc;
using namespace files;

App::App(args::Arguments app_args) : app_args_(std::move(app_args)) {
	std::cout << this->app_args_ << endl;
}


void App::run() {
	processInput();

	tryToCrackTheEncoding();
}

void App::processInput() {
	if (this->app_args_.encrypt_mode() == args::NONE) {
		return;
	}

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

	auto if_stream = FileService::getInputHandle(this->app_args_.input_file().c_str());
	auto of_stream = FileService::getOutputHandle(this->app_args_.output_file().c_str());

	string line, processed_line;
	while (getline(if_stream, line)) {
		if (this->app_args_.encrypt_mode() == args::ENCRYPT) {
			const string sanitized_in = Coder::sanitize(line);
			processed_line = this->app_coder_->encode(sanitized_in);
		} else {
			processed_line = this->app_coder_->decode(line);
		}
		of_stream << processed_line << endl;
	}
	of_stream.close();
	if_stream.close();

	if (this->app_args_.encrypt_mode() != args::NONE) {
		std::cout << (this->app_args_.encrypt_mode() == args::ENCRYPT ? "Encryption completed." : "Decryption completed");
	}
}

void App::tryToCrackTheEncoding() {
	if (this->app_args_.encrypt_mode() != args::NONE && this->app_args_.getCrackEncMode() != args::BRUTE_FORCE) {
		return;
	}

	// initializeExampleEnGramsProbability
	const auto enGramsProbability = initializeBaseEnGramsData();

	// sanitize input and process monograms
	const double totalMonograms = sanitizeFileAndProcessMonograms();

	// calculate gsl_cdf_chisq_Pinv criticalValue with 0.05 inaccuracy
	const double criticalValue = gsl_cdf_chisq_Pinv(0.95, totalMonograms);

	switch (this->app_args_.getCoderType()) {
		case args::CESAR: {
			bruteForceCesar(enGramsProbability, criticalValue);
			return;
		}
		case args::AFFINITY: {
			minMaxAffine(enGramsProbability, criticalValue);
			return;
		}
		default:
			return;
	}
}

std::map<std::string, double> App::initializeBaseEnGramsData() {
	auto counter = std::map<std::string, int>();
	auto probabilityMap = std::map<std::string, double>();
	std::int64_t total = 0;
	std::string line;

	const char *grams_file = this->app_args_.getBruteForceNgramsFile().c_str();
	int n_grams_mode = this->app_args_.getBruteForceNgramsMode();
	auto infile = files::FileService::getInputHandle(grams_file);

	while (getline(infile, line)) {
		if (line.size() >= n_grams_mode + 2) {
			const auto expr = line.substr(0, n_grams_mode);
			const int count = std::stoi(line.substr(n_grams_mode + 1));
			counter.insert({expr, count});
			total += count;
		}
	}
	infile.close();

	double probability;
	for (const auto &[ngram, count]: counter) {
		probability = static_cast<double>(count) / static_cast<double>(total);
		probabilityMap.insert({ngram, probability});
	}

	return probabilityMap;
}

double App::sanitizeFileAndProcessMonograms() {
	std::string line;
	utils::NgramsUtil util = utils::NgramsUtil(this->app_args_.getBruteForceNgramsMode());

	ifstream in = files::FileService::getInputHandle(this->app_args_.input_file().c_str());
	ofstream of = files::FileService::getOutputHandle(this->app_args_.tmpInputFile().c_str());

	// sanitize testable input file
	while (getline(in, line)) {
		const std::string sanitized_in = Coder::sanitize(line);

		// process sanitized line
		util.processLine(sanitized_in);
		of << sanitized_in << endl;
	}

	of.close();
	in.close();

	return static_cast<double>(util.getTotal());
}

void App::bruteForceCesar(const map<std::string, double> &gramsProbability, const double criticalValue) {
	int iteration = 0;

	double chiSquare;
	std::string line, processed_line;
	utils::NgramsUtil util = utils::NgramsUtil(this->app_args_.getBruteForceNgramsMode());

	// read from sanitized input
	ifstream in = files::FileService::getInputHandle(this->app_args_.tmpInputFile().c_str());
	CesarCoder coder = CesarCoder();

	do {
		// update loop, reset util and ifstream pos
		in.clear();
		in.seekg(0, std::ios::beg);
		iteration++;
		util.reset();

		// initialize new cesar key
		coder.setKeyForIteration(iteration);

		// decode input
		while (getline(in, line)) {
			processed_line = coder.decode(line);
			// process decoded line
			util.processLine(processed_line);
		}

		/* test x^2 */
		chiSquare = calculateChiSquare(util, gramsProbability);

		std::cout << "End of iteration: " << iteration << ", and the critical val is:" << criticalValue << ", current chiSquare is:"
		          << chiSquare << endl;
	} while (chiSquare > criticalValue && iteration < 26);

	if (chiSquare > criticalValue) {
		std::cout << "Decipher key not found." << endl;
		return;
	}

	std::cout << "The cesar encoding has been broken, and the key was: " << iteration << endl;

	decipherAndWriteFinalResult(coder, in);

	// close all read/write streams
	in.close();
}

void App::minMaxAffine(const map<std::string, double> &gramsProbability, const double criticalValue) {
	double chiSquare;
	std::string line, processed_line;
	utils::NgramsUtil util = utils::NgramsUtil(this->app_args_.getBruteForceNgramsMode());

	// read from sanitized input
	ifstream in = files::FileService::getInputHandle(this->app_args_.tmpInputFile().c_str());
	AffineCoder coder = AffineCoder();
	auto resolvedKeyMap = map<char, char>();

	for (auto letter: coder.getLetters()) {
		char resolvedChar = coder.minMaxForKey(letter, gramsProbability, util, in);
		resolvedKeyMap.insert({letter, resolvedChar});
	}

	coder.setKeysMap(resolvedKeyMap);

	// decode input
	while (getline(in, line)) {
		processed_line = coder.decode(line);
		// process decoded line
		util.processLine(processed_line);
	}

	/* test x^2 */
	chiSquare = calculateChiSquare(util, gramsProbability);

	if (chiSquare > criticalValue) {
		std::cout << "Decipher key not found." << endl;
		return;
	}

	std::cout << "The affine encoding has been broken, and the keys were: " << endl;
	for (const auto &[k, v]: coder.getKeysMap()) {
		std::cout << "Key:" << k << " -> Val:" << v << endl;
	}

	decipherAndWriteFinalResult(coder, in);

	// close all read/write streams
	in.close();
}

void App::decipherAndWriteFinalResult(enc::Coder &coder, ifstream &in) {
	std::string line, processed_line;

	// store the current deciphered result into output
	std::ofstream of = files::FileService::getOutputHandle(this->app_args_.output_file().c_str());

	in.clear();
	in.seekg(0, std::ios::beg);

	std::cout << "Writing deciphered data to output file." << endl;
	while (getline(in, line)) {
		processed_line = coder.decode(line);
		of << processed_line << endl;
	}

	of.close();
}