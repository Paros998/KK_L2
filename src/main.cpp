#include "headers/Arguments.h"
#include "headers/App.h"

using namespace std;

int main(int const argc, char const *argv[]) {
    const auto arguments = args::Arguments(argc, argv);

    auto app_runner = App(arguments);

    app_runner.run();
    return 0;
}