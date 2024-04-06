//
// Created by part4 on 21.03.2024.
//

#include "headers/App.h"

using namespace enc;
using namespace files;

int App::extractKey() const {
    return FileService::readKey(this->app_args_.key_file().c_str());
}

App::App(args::Arguments app_args) : app_args_(std::move(app_args)), app_coder_(Coder(extractKey())) {
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
            const string sanitized_in = Coder::sanitize(line);
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

	analizeEncryptedData();

	if (this->app_args_.encrypt_mode() != args::NONE) {
		std::cout << (this->app_args_.encrypt_mode() == 0 ? "Encryption completed." : "Decryption completed");
	}
}

void App::analizeEncryptedData() {
	if (this->app_args_.encrypt_mode() == args::NONE && this->app_args_.getAnalizeMode() == args::BRUTE_FORCE) {
		// test all keys until x^2 is eq or lower than 0.05


	}
}
