#include "headers/Arguments.h"
#include "headers/App.h"

using namespace std;

int main(int const argc, char const *argv[]) {
	// Initialize command-line arguments
	const auto arguments = args::Arguments(argc, argv);

	// Create an instance of the App class with the provided arguments
	auto app_runner = App(arguments);

	// Run the application
	app_runner.run();

	return 0;
}
