//
// Created by part4 on 21.03.2024.
//

#include "headers/App.h"
#include "headers/FileService.h"
#include "headers/NgramsUtil.h"

using namespace enc;
using namespace files;

int App::extractKey() const {
	return FileService::readKey(this->app_args_.key_file().c_str());
}

App::App(args::Arguments app_args) : app_args_(std::move(app_args)), app_coder_(CesarCoder(extractKey())) {
	std::cout << this->app_args_ << endl;
}

void App::processInput() {
	if (this->app_args_.encrypt_mode() == args::NONE) {
		return;
	}

	auto if_stream = FileService::getInputHandle(this->app_args_.input_file().c_str());
	auto of_stream = FileService::getOutputHandle(this->app_args_.output_file().c_str());

	string line, processed_line;
	while (getline(if_stream, line)) {
		if (this->app_args_.encrypt_mode() == args::ENCRYPT) {
			const string sanitized_in = CesarCoder::sanitize(line);
			processed_line = this->app_coder_.encode(sanitized_in);
		} else {
			processed_line = this->app_coder_.decode(line);
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
		std::cout << (this->app_args_.encrypt_mode() == 0 ? "Encryption completed." : "Decryption completed");
	}
}

void App::tryToCrackTheEncoding() {
	if (this->app_args_.encrypt_mode() == args::NONE && this->app_args_.getCrackEncMode() == args::BRUTE_FORCE) {
		// initializeExampleEnMonograms
		const auto enMonogramsProbability = initializeBaseEnMonogramsData();

		// sanitize input and process monograms
		const double totalMonograms = sanitizeFileAndProcessMonograms();

		// calcualate gsl_cdf_chisq_Pinv criticalValue with 0.05 inaccuracy
		const double criticalValue = gsl_cdf_chisq_Pinv(0.95, totalMonograms);

		// initialize standard vars
		int cesar_index_i = 0;
		double chiSquare;
		std::string line, processed_line;

		utils::NgramsUtil util = utils::NgramsUtil();
		auto coder = CesarCoder(cesar_index_i);

		// read from sanitized input
		ifstream in = files::FileService::getInputHandle(this->app_args_.tmpInputFile().c_str());

		do {
			// update loop, reset util and ifstream pos
			in.clear();
			in.seekg(0, std::ios::beg);
			cesar_index_i++;
			util.reset();

			// initialize new cesar key
			coder.setCesarKey(cesar_index_i);

			// decode input
			while (getline(in, line)) {
				processed_line = coder.decode(line);
				// process decoded line
				util.processLine(processed_line);
			}

			/* test x^2 */
			chiSquare = calculateChiSquare(util, enMonogramsProbability);

			std::cout << "End of iteration for cesar: " << cesar_index_i << endl;
		} while (chiSquare > criticalValue && cesar_index_i < 26);

		if (chiSquare < criticalValue) {
			decipherAndWriteFinalResult(cesar_index_i, in);
		} else std::cout << "Decipher key not found." << endl;

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

double App::calculateChiSquare(utils::NgramsUtil &util, const map<std::string, double>& probabilityMap) {
	// N
	double chi = 0.0;
	const auto total_found_monograms = util.getTotal();
	const auto& tested_text_monograms_counter = util.getCounter();

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

void App::decipherAndWriteFinalResult(int cesar_key, ifstream &in) {
	std::string line, processed_line;

	std::cout << "The cesar encoding has been broken, and the key was: " << cesar_key << endl;

	// store the current deciphered result into output
	std::ofstream of = files::FileService::getOutputHandle(this->app_args_.output_file().c_str());
	auto coder = CesarCoder(cesar_key);

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
		const std::string sanitized_in = enc::CesarCoder::sanitize(line);

		// process sanitized line
		util.processLine(sanitized_in);
		of << sanitized_in << endl;
	}

	of.close();
	in.close();

	return static_cast<double>(util.getTotal());
}
