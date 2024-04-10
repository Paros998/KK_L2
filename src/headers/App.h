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
	enc::CesarCoder app_coder_;

	[[nodiscard]] int extractKey() const;

	static std::map<std::string, double> initializeBaseEnMonogramsData();

	void processInput();

	void tryToCrackTheEncoding();

	static double calculateChiSquare(utils::NgramsUtil &util, const map<std::string, double>& probabilityMap);

	void decipherAndWriteFinalResult(int cesar_key, ifstream &in);

	double sanitizeFileAndProcessMonograms();
public:
	explicit App(args::Arguments app_args);

	void run();

	~App() = default;

};


#endif //APP_H
