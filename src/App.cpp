//
// Created by part4 on 21.03.2024.
//

#include "headers/App.h"
#include "headers/FileService.h"
#include "headers/NgramsUtil.h"
#include "headers/AffineCoder.h"

using namespace enc;
using namespace files;

App::App(args::Arguments app_args) : app_args_(std::move(app_args)) {
	std::cout << this->app_args_ << endl;
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
}

void App::run() {
	processInput();

	tryToCrackTheEncoding();

	if (this->app_args_.encrypt_mode() != args::NONE) {
		std::cout << (this->app_args_.encrypt_mode() == args::ENCRYPT ? "Encryption completed." : "Decryption completed");
	}
}

void App::tryToCrackTheEncoding() {
	if (this->app_args_.encrypt_mode() == args::NONE && this->app_args_.getCrackEncMode() == args::BRUTE_FORCE
	    && this->app_args_.getCoderType() != args::NO_CODER) {
		// initializeExampleEnMonograms
		const auto enMonogramsProbability = initializeBaseEnMonogramsData();

		// sanitize input and process monograms
		const double totalMonograms = sanitizeFileAndProcessMonograms();

		// calculate gsl_cdf_chisq_Pinv criticalValue with 0.05 inaccuracy
		const double criticalValue = gsl_cdf_chisq_Pinv(0.95, totalMonograms);

		// initialize standard vars
		int iteration = 0;
		double chiSquare;
		std::string line, processed_line;
		utils::NgramsUtil util = utils::NgramsUtil();

		if (this->app_args_.getCoderType() == args::CESAR) {
			this->app_coder_ = new CesarCoder();
		} else {
			this->app_coder_ = new AffineCoder();
		}

		// read from sanitized input
		ifstream in = files::FileService::getInputHandle(this->app_args_.tmpInputFile().c_str());

		do {
			// update loop, reset util and ifstream pos
			in.clear();
			in.seekg(0, std::ios::beg);
			iteration++;
			util.reset();

			// initialize new cesar key
			app_coder_->setIteration(iteration);

			// decode input
			while (getline(in, line)) {
				processed_line = app_coder_->decode(line);
				// process decoded line
				util.processLine(processed_line);
			}

			/* test x^2 */
			chiSquare = calculateChiSquare(util, enMonogramsProbability);

			std::cout << "End of iteration: " << iteration << ", and the critical val is:"<< criticalValue << ", current chiSquare is:" << chiSquare << endl;
		} while (chiSquare > criticalValue && (this->app_args_.getCoderType() == args::AFFINITY || iteration < 26));

		if (chiSquare < criticalValue) {
			if (this->app_args_.getCoderType() == args::CESAR) {
				std::cout << "The cesar encoding has been broken, and the key was: " << iteration << endl;
			} else {
				std::cout << "The affine encoding has been broken, and the keys were: " << endl;
				for (const auto &[k, v]: dynamic_cast<AffineCoder*>(this->app_coder_)->getKeysMap()) {
					std::cout << "Key:" << k << " -> Val:" << v << endl;
				}
			}

			decipherAndWriteFinalResult(*app_coder_, in);
		} else {
			std::cout << "Decipher key not found." << endl;
		}
		// close all read/write streams
		in.close();
	}
}

std::map<std::string, double> App::initializeBaseEnMonogramsData() {
	auto counter = std::map<std::string, int>();
	auto probabilityMap = std::map<std::string, double>();
	std::int64_t total = 0;
	std::string line;

	auto infile = files::FileService::getInputHandle(args::EnMonogramsFile.c_str());
	while (getline(infile, line)) {
		const auto expr = line.substr(0, 1);
		const int count = std::stoi(line.substr(2));
		counter.insert({expr, count});
		total += count;
	}
	infile.close();

	for (const auto &[ngram, count]: counter) {
		double probability = static_cast<double>(count) / static_cast<double>(total);
		//probability = std::round(probability * 1000000) / 1000000;
		probabilityMap.insert({ngram, probability});
	}

	return probabilityMap;
}

double App::calculateChiSquare(utils::NgramsUtil &util, const map<std::string, double> &probabilityMap) {
	// N
	double chi = 0.0;
	const auto total_found_monograms = util.getTotal();
	const auto &tested_text_monograms_counter = util.getCounter();

	for (const auto &[ngram, /** Ci */ count]: tested_text_monograms_counter) {
		// Pi
		double example_probability = probabilityMap.find(ngram)->second;

		// Ei
		double expected_count = static_cast<double>(total_found_monograms) * example_probability;
		//expected_count = std::round(expected_count * 1000000) / 1000000;

		// X^2 i
		const auto power = static_cast<double>(std::pow(static_cast<double>(count) - expected_count, 2));

		const double x_2 = expected_count == 0 ? 0.0 : power / expected_count;

//				 std::cout << "Current testable ngram:" << ngram << " has total count: " << count << " and it's x^2 equals:" << x_2 <<
//				 std::endl;

		// T
		chi += x_2;
	}

	return chi;
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

double App::sanitizeFileAndProcessMonograms() {
	std::string line;
	utils::NgramsUtil util = utils::NgramsUtil();

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
