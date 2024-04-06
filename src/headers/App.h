//
// Created by part4 on 21.03.2024.
//

#ifndef APP_H
#define APP_H


#include "Arguments.h"
#include "Coder.h"
#include "FileService.h"

class App {
    args::Arguments app_args_;
    enc::Coder app_coder_;

    [[nodiscard]] int extractKey() const;

public:
    explicit App(args::Arguments app_args);

    void processInput();

    void run();

    ~App() {
    };
};


#endif //APP_H
