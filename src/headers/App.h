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

	static double calculateChiSquare(utils::NgramsUtil &util, const map<std::string, double>& probabilityMap);

	void decipherAndWriteFinalResult(enc::Coder &coder, ifstream &in);

	double sanitizeFileAndProcessMonograms();
public:
	explicit App(args::Arguments app_args);

	void run();

	~App() {
		delete this->app_coder_;
	};

};


#endif //APP_H
