//
// Created by part4 on 21.03.2024.
//

#ifndef APP_H
#define APP_H


#include "Arguments.h"
#include "CesarCoder.h"
#include "FileService.h"
#include "NgramsUtil.h"

class App {
	args::Arguments app_args_;
	enc::Coder *app_coder_{};

	std::map<std::string, double> initializeBaseEnGramsData();

	void processInput();

	void tryToCrackTheEncoding();

	double sanitizeFileAndProcessMonograms();

	void bruteForceCesar(const map<std::string, double> &gramsProbability, double criticalValue);

	void minMaxAffine(const map<std::string, double> &gramsProbability, double criticalValue);

	void decipherAndWriteFinalResult(enc::Coder &coder, ifstream &in);

public:
	explicit App(args::Arguments app_args);

	void run();

	~App() {
		delete this->app_coder_;
	};

	static double calculateChiSquare(utils::NgramsUtil &util, const map<std::string, double>& probabilityMap)  {
		// N
		double chi = 0.0;
		const auto totalGrams = util.getTotal();
		const auto &tested_text_grams_counter = util.getCounter();

		for (const auto &[ngram, /** Ci */ count]: tested_text_grams_counter) {
			// Pi
			double example_probability = probabilityMap.find(ngram)->second;

			// Ei
			double expected_count = static_cast<double>(totalGrams) * example_probability;
//			expected_count = std::round(expected_count * 1000000000.0) / 1000000000.0;

			// X^2 i
			const auto power = static_cast<double>(std::pow(static_cast<double>(count) - expected_count, 2));

			// T
			chi += expected_count == 0 ? 0.0 : power / expected_count;
		}

		return chi;
	}
};


#endif //APP_H
