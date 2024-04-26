# Kryptografia i kryptoanaliza
## Laboratorium 2
### Grupa 1IZ22A
### Autor: Patryk Grzywacz

### Zadanie 1

Napisz program (w języku C++ / Rust) implementujący algorytm szyfru przesuwnego (szyfr Cezara).
1. Tekst jawny powinien być importowany do programu z pliku tekstowego, którego nazwa określona powinna być
   po zdefiniowanym argumencie / fladze: -i.
2. Wynik pracy programu powinien być eksportowany do pliku tekstowego, którego nazwa określona powinna być
   po zdefiniowanym argumencie / fladze: -o.
3. Klucz powinien być określany za pomocą parametru / flagi -k.
4. Tryb pracy programu powinien być określony poprzez flagi: -e dla procesu szyfrowania, -d dla procesu deszyfrowania.
   
Przykład wywołania programu w celu zaszyfrowania tekstu:

./program -e -k klucz.txt -i tekst_jawny.txt -o szyfrogram.txt

Przykład wywołania programu w celu odszyfrowania tekstu:

./program -d -k klucz.txt -i szyfrogram.txt -o tekst_odszyfrowany.txt

Uwagi:

• Kolejność argumentów powinna być dowolna.

• Odczytany tekst jawny, przed dalszym przetwarzaniem, powinien być zamieniony do postaci składającej się
tylko z dużych liter. Ponadto z tekstu powinny być usunięte wszystkie znaki, które nie są literami, np: odstępy,
przecinki, kropki itp.

### Zadanie 2
Rozbuduj program z poprzedniego zadania poprzez implementację ataku typu brute-force na szyfrogram wygenerowany przy pomocy algorytmu przesuwnego.
1. Algorytm powinien być wyzwalany po użyciu flagi -a z parametrem bf.

Przykład wywołania programu:

./program -a bf -i szyfrogram -o tekst_odszyfrowany

Uwagi:

• Program w celu klasyfikacji wyniku działania algorytmu, powinien wykorzystywać test χ
2 na poziomie istotności
0.05 (patrz ostatnie zadanie z poprzedniej instrukcji).

• Do wyznaczenia wartości krytycznej, decydującej o odrzuceniu hipotezy zerowej (odszyfrowany tekst jest tekstem
w języku angielskim), należy użyć funkcji gsl_cdf_chisq_Pinv z biblioteki gsl.

### Zadanie 3
Napisz program analogiczny do programu z zadania 1, który tym razem implementuje szyfr afiniczny

### Zadanie 4

Rozbuduj program z poprzedniego zadania poprzez implementację ataku typu brute-force na szyfrogram zaimplementowany przy pomocy szyfru afinicznego. Sposób pracy z programem powinien być analogiczny do pracy z
programem z zadania 2.

### Kody źródłowe - headery klas

* Libraries.h

``` C++
// File: libraries.h
// This header file seems to serve as a container for all included libraries.
// It can be useful to avoid repeating the inclusion of the same libraries in different source files.

#pragma once

// Including standard and external libraries
#include <iostream>     // Standard input-output
#include <fstream>      // File handling
#include <string>       // String manipulation

#include <map>          // Map data structure
#include <ranges>       // Ranges library (C++20)

#include <cstdint>      // Fixed-width integer types

#include <cmath>        // Mathematical functions
#include <vector>       // Vectors
#include <random>       // Random number generators
#include <algorithm>    // General algorithms

#include <boost/functional.hpp> // Boost library

#include "gsl/gsl_cdf.h"       // GSL (GNU Scientific Library) - Cumulative Distribution Functions

#ifndef LIBRARIES_H
#define LIBRARIES_H

#endif //LIBRARIES_H

```

* AffineCoder.h

``` C++
// File created on: 10.04.2024
// Header guard to prevent multiple inclusion of this header file
#ifndef KK_L2_AFFINECODER_H
#define KK_L2_AFFINECODER_H

// Including necessary header files
#include "Libraries.h" // Including external libraries
#include "Coder.h" // Including the base class definition

namespace enc {
	// Custom hash function for pairs
	struct pair_hash {
		// Operator overload for computing hash value of pairs
		template<class T1, class T2>
		std::size_t operator () (const std::pair<T1,T2> &pair) const {
			auto hash1 = my_hash<T1>{}(pair.first);
			auto hash2 = std::hash<T2>{}(pair.second);
			// Improved combining hash function
			return hash1 ^ (hash2 + 0x9e3779b9 + (hash1 << 6) + (hash1 >> 2));
		}

	private:
		// Custom hash function for const char keys
		template<typename T>
		struct my_hash {
			std::size_t operator () (T key) const {
				return static_cast<std::size_t>(key);
			}
		};
	};

	// Class for Affine Encoder, inheriting from base Coder class
	class AffineCoder : public Coder {
		// Vector to store used key map hashes
		vector<std::size_t> used_key_map_hashes_;
		// Vector to store characters
		vector<char> letters;
		// Map to store keys
		map<char, char> keys_map_{};

		// Override functions to encode and decode characters
		[[nodiscard]] char encodeChar(char in) const override;
		[[nodiscard]] char decodeChar(char in) const override;

		// Function to read keys from input
		void readKeys();
		// Function to set keys map
		void setKeysMap(const map<char, char> &keysMap) {
			this->keys_map_ = keysMap;
		}
		// Function to generate random number in given range
		static int randomInRange(int min, int max);
		// Function to calculate hash of map
		static size_t calculateMapHash(map<char, char> &mapToHash);
		// Function to randomize keys map
		map<char, char> &randomizeKeyMap(map<char, char> &keysMap);

	public:
		// Constructors
		explicit AffineCoder() {
			// Initializing letters vector with characters
			for (int i = 65; i <= 90; i++) {
				letters.push_back(static_cast<char>(i));
			}
		};
		explicit AffineCoder(args::Arguments *args) : Coder(args) {
			// Initializing AffineCoder object with arguments
			readKeys();
		};

		// Function to get keys map
		[[nodiscard]] const map<char, char> &getKeysMap() const {
			return keys_map_;
		}
		// Function to set key for iteration
		void setKeyForIteration(int i) override;

		// Destructor
		~AffineCoder() = default;

	};

} // enc

#endif //KK_L2_AFFINECODER_H

```

* App.h

``` C++
// File created on: 21.03.2024
// Header guard to prevent multiple inclusion of this header file
#ifndef APP_H
#define APP_H

// Including necessary header files
#include "Arguments.h"
#include "CesarCoder.h"
#include "FileService.h"
#include "NgramsUtil.h"

// Class declaration for the main application
class App {
	args::Arguments app_args_; // Object to store application arguments
	enc::Coder *app_coder_{}; // Pointer to encoder object

	// Function to initialize base English n-grams data
	std::map<std::string, double> initializeBaseEnGramsData();
	// Function to process input
	void processInput();
	// Function to attempt cracking the encoding
	void tryToCrackTheEncoding();
	// Function to calculate Chi-square value
	static double calculateChiSquare(utils::NgramsUtil &util, const map<std::string, double>& probabilityMap);
	// Function to decipher and write the final result
	void decipherAndWriteFinalResult(enc::Coder &coder, ifstream &in);
	// Function to sanitize file and process monograms
	double sanitizeFileAndProcessMonograms();
	// Function to print decipher information
	void printDecipherInfo(int iteration) const;

public:
	// Constructor
	explicit App(args::Arguments app_args);
	// Function to run the application
	void run();
	// Destructor
	~App() {
		delete this->app_coder_;
	};
};

#endif //APP_H

```

* Arguments.h

``` C++
// File created on: 13.03.2024
// Header guard to prevent multiple inclusion of this header file
#ifndef ARGUMENTS_H
#define ARGUMENTS_H

// Including necessary header files
#include "Libraries.h"

// Namespace for handling command line arguments
namespace args {
	// File paths for English n-grams data
	static const std::string EnMonogramsFile = "../data/grams/english_monograms.txt";
	static const std::string EnBigramsFile = "../data/grams/english_bigrams.txt";
	static const std::string EnTrigramsFile = "../data/grams/english_trigrams.txt";
	static const std::string EnQuadgramsFile = "../data/grams/english_quadgrams.txt";

	// Command line flags
	static const std::string D_FLAG = "-d";
	static const std::string E_FLAG = "-e";
	static const std::string I_FLAG = "-i";
	static const std::string K_FLAG = "-k";
	static const std::string O_FLAG = "-o";
	static const std::string A_FLAG = "-a";
	static const std::string CA_FLAG = "-ca";
	static const std::string CC_FLAG = "-cc";
	static const std::string N1_FLAG = "-n1";
	static const std::string N2_FLAG = "-n2";
	static const std::string N3_FLAG = "-n3";
	static const std::string N4_FLAG = "-n4";

	// Enumeration for command line flags
	enum flag {
		d, e, i, k, o, a, ca, cc, n1, n2, n3, n4
	};

	// Map for command line flags and their corresponding enum values
	static std::map<std::string, flag> FLAGS = {
			{D_FLAG, d},
			{E_FLAG, e},
			{I_FLAG, i},
			{K_FLAG, k},
			{O_FLAG, o},
			{A_FLAG, a},
			{CA_FLAG, ca},
			{CC_FLAG, cc},
			{N1_FLAG, n1},
			{N2_FLAG, n2},
			{N3_FLAG, n3},
			{N4_FLAG, n4}
	};

	// Enumeration for encoder types
	enum CoderType {
		NO_CODER, CESAR, AFFINITY
	};

	// Enumeration for encryption modes
	enum EncryptMode {
		NONE, ENCRYPT, DECRYPT
	};

	// Enumeration for crack encoding modes
	enum CrackEncMode {
		NO_CRACK, BRUTE_FORCE
	};

	// Class to handle command line arguments
	class Arguments {
		EncryptMode encrypt_mode_ = EncryptMode::NONE; // Encryption mode
		CrackEncMode crack_mode_ = CrackEncMode::NO_CRACK; // Crack encoding mode
		CoderType coder_type_ = CoderType::NO_CODER; // Encoder type
		int brute_force_ngrams_mode = -1; // Brute force n-grams mode
		std::string brute_force_ngrams_file; // Brute force n-grams file path
		std::string inputFile_; // Input file path
		std::string tmpInputFile_ = "../data/tmp.txt"; // Temporary input file path
		std::string outputFile_; // Output file path
		std::string keyFile_; // Key file path

	public:
		// Constructor to initialize arguments based on command line inputs
		Arguments(int argc, char const *argv[]);

		// Getter methods for various arguments
		[[nodiscard]] EncryptMode encrypt_mode() const {
			return encrypt_mode_;
		}

		[[nodiscard]] std::string input_file() const {
			return inputFile_;
		}

		[[nodiscard]] std::string output_file() const {
			return outputFile_;
		}

		[[nodiscard]] std::string key_file() const {
			return keyFile_;
		}

		[[nodiscard]] CrackEncMode getCrackEncMode() const {
			return crack_mode_;
		}

		[[nodiscard]] std::string tmpInputFile() const {
			return tmpInputFile_;
		}

		[[nodiscard]] CoderType getCoderType() const {
			return coder_type_;
		}

		[[nodiscard]] int getBruteForceNgramsMode() const {
			return brute_force_ngrams_mode;
		}

		[[nodiscard]] const std::string &getBruteForceNgramsFile() const {
			return brute_force_ngrams_file;
		}

		// Overloaded stream insertion operator to print argument values
		friend std::ostream &operator<<(std::ostream &os, const Arguments &obj) {
			return os
					<< "[" << std::endl
					<< "encrypt_mode_: " << obj.encrypt_mode_ << std::endl
					<< "inputFile_: " << obj.inputFile_ << std::endl
					<< "outputFile_: " << obj.outputFile_ << std::endl
					<< "keyFile_: " << obj.keyFile_ << std::endl
					<< "analize_mode_: " << obj.crack_mode_ << std::endl
					<< "coder_type_: " << obj.coder_type_ << std::endl
					<< "]" << std::endl;
		}
	};
} // args

#endif //ARGUMENTS_H

```

* CesarCoder.h

``` C++
// File created on: 17.03.2024
// Header guard to prevent multiple inclusion of this header file
#ifndef CODER_H
#define CODER_H

// Including necessary header files
#include "Libraries.h"
#include "Coder.h"

// Using standard namespace
using namespace std;

namespace enc {
	// Class declaration for Cesar Cipher encoder, inheriting from base Coder class
	class CesarCoder : public Coder {
		int cesar_key_; // Key for Cesar Cipher

		// Override functions to encode and decode characters
		[[nodiscard]] char encodeChar(char in) const override;
		[[nodiscard]] char decodeChar(char in) const override;

		// Function to extract key from arguments
		void extractKey();
		// Function to set Cesar key
		void setCesarKey(int cesarKey) {
			cesar_key_ = cesarKey;
		}

	public:
		// Constructors
		explicit CesarCoder() = default; // Default constructor
		explicit CesarCoder(args::Arguments *args) : Coder(args) {
			// Constructor with arguments
			extractKey();
		};

		// Function to set key for iteration
		void setKeyForIteration(int i) override {
			setCesarKey(i);
		}

		// Destructor
		~CesarCoder() = default;
	};
} // enc

#endif //CODER_H

```

* Coder.h

``` C++
// File created on: 10.04.2024
// Header guard to prevent multiple inclusion of this header file
#ifndef KK_L2_CODER_H
#define KK_L2_CODER_H

// Including necessary header files
#include "Libraries.h"
#include "Arguments.h"

// Using standard namespace
using namespace std;

namespace enc {
	// Base class for encoding and decoding text
	class Coder {
		// Virtual functions for encoding and decoding characters
		[[nodiscard]] virtual char encodeChar(char in) const {
			return in;
		};
		[[nodiscard]] virtual char decodeChar(char in) const {
			return in;
		};

	protected:
		args::Arguments *args_{}; // Pointer to argument object

	public:
		// Constructors
		Coder() = default; // Default constructor
		explicit Coder(args::Arguments *args) : args_(args) {}; // Constructor with arguments

		// Static function to sanitize input string
		static string sanitize(const string &in);

		// Function to decode input string
		string decode(const string &in);
		// Function to encode input string
		string encode(const string &in);

		// Pure virtual function to set key for iteration
		virtual void setKeyForIteration(int i) = 0;

		// Destructor
		~Coder() = default;
	};

} // enc

#endif //KK_L2_CODER_H

```

* FileService.h

``` C++
// File created on: 13.03.2024
// Header guard to prevent multiple inclusion of this header file
#ifndef FILEREADER_H
#define FILEREADER_H

// Including necessary header files
#include "Libraries.h"
#include "Arguments.h"

// Namespace for file-related operations
namespace files {
	// Class for file handling operations
	class FileService {
	public:
		// Function to read key from file
		static int readKey(const char *file);
		// Function to get input file handle
		static std::ifstream getInputHandle(const char *file);
		// Function to get output file handle
		static std::ofstream getOutputHandle(const char *file);
	};

} // files

#endif //FILEREADER_H

```

* NgramsUtil.h

``` C++
// File created on: 22.03.2024
// Header guard to prevent multiple inclusion of this header file
#ifndef NGRAMSUTIL_H
#define NGRAMSUTIL_H

// Including necessary header files
#include "Libraries.h"
#include "FileService.h"

// Namespace for utility functions
namespace utils {
	// Class for handling n-grams utility operations
	class NgramsUtil {
		std::map<const std::string, int> counter_; // Map to store n-grams counts
		std::int64_t total_ = 0; // Total count of n-grams
		int mode_; // Mode for n-grams processing

	public:
		// Constructor with mode parameter
		explicit NgramsUtil(const int mode) {
			this->mode_ = mode;
			this->counter_ = std::map<const std::string, int>();
		};

		// Getter method for n-grams counter map
		[[nodiscard]] const std::map<const std::string, int> &getCounter() const;
		// Getter method for total count of n-grams
		[[nodiscard]] int64_t getTotal() const;

		// Function to process a line of text and update n-grams counts
		void processLine(const std::string &line);
		// Function to reset n-grams counts
		void reset();

		// Destructor
		~NgramsUtil() = default;
	};
}

#endif //NGRAMSUTIL_H

```


### Kody źródłowe - źródła klas

* AffineCoder.cpp

``` C++
// File created on: 10.04.2024
#include "headers/AffineCoder.h"

namespace enc {
	// Function to encode a character using Affine Cipher
	char AffineCoder::encodeChar(const char in) const {
		// Find the replacement character in the keys map
		const auto find = this->keys_map_.find(in);
		// If replacement character found, return it, otherwise return original character
		if (find->second == 0) return in;
		return find->second;
	}

	// Function to decode a character using Affine Cipher
	char AffineCoder::decodeChar(const char in) const {
		// Iterate over keys map to find the original character
		for (auto [key, value]: this->keys_map_) {
			if (value == in) return key;
		}
		// If original character not found, return input character
		return in;
	}

	// Function to read keys from file
	void AffineCoder::readKeys() {
		// Open key file
		ifstream infile(this->args_->key_file());
		string line;
		// Read each line and extract original and replacement characters
		while (getline(infile, line)) {
			if (line.size() == 3) {
				const auto original_key = line.substr(0, 1);
				const auto replacement = line.substr(2, 1);
				// Insert into keys map
				this->keys_map_.insert({
						                       static_cast<char>(std::toupper(original_key[0])),
						                       static_cast<char>(std::toupper(replacement[0]))
				                       });
			}
		}
		// Close file
		infile.close();
	}

	// Function to generate a random number in a given range
	int AffineCoder::randomInRange(int min, int max) {
		// Seed random number generator
		std::random_device rd;
		std::mt19937 eng(rd());
		// Define distribution
		std::uniform_int_distribution<> distribution(min, max);
		// Generate random number
		return distribution(eng);
	}

	// Function to calculate hash value of map
	std::size_t AffineCoder::calculateMapHash(map<char, char> &m) {
		pair_hash elem_hash;
		std::size_t hash_value = 0;

		// Combine hash values using XOR and multiplication
		for (const auto &elem : m) {
			hash_value = (hash_value * 37) ^ elem_hash(elem);
		}

		return hash_value;
	}

	// Function to set key for iteration
	void AffineCoder::setKeyForIteration(int i) {
		std:size_t keysHash;

		std::map<char, char> keysMap;

		// Randomize original keysMap
		do {
			keysMap = randomizeKeyMap(keysMap);
			keysHash = calculateMapHash(keysMap);
		} while (std::binary_search(this->used_key_map_hashes_.begin(), this->used_key_map_hashes_.end(), keysHash));

		// Add keys hash to used hashes vector
		this->used_key_map_hashes_.push_back(keysHash);
		// Sort used hashes vector
		std::sort(this->used_key_map_hashes_.begin(), this->used_key_map_hashes_.end());
		// Set keys map
		this->setKeysMap(keysMap);
	}

	// Function to randomize keys map
	map<char, char> &AffineCoder::randomizeKeyMap(map<char, char> &keysMap) {
		char randomSign;
		keysMap = map<char, char>();
		vector<int> lettersUsed;

		// Iterate over letters and assign random replacement characters
		for (const auto c: letters) {
			randomSign = -1;
			// Generate random replacement character not already used
			do {
				randomSign = static_cast<char>(randomInRange(65, 90));
			} while (binary_search(lettersUsed.begin(), lettersUsed.end(), static_cast<int>(randomSign)));

			// Insert into keys map and add to used letters vector
			keysMap.insert({c, randomSign});
			lettersUsed.push_back(static_cast<int>(randomSign));
			sort(lettersUsed.begin(), lettersUsed.end());
		}
		return keysMap;
	}

} // enc

```

* App.cpp

``` C++
// File created on: 21.03.2024
#include <fenv.h>
#include <iomanip>
#include "headers/App.h"
#include "headers/FileService.h"
#include "headers/NgramsUtil.h"
#include "headers/AffineCoder.h"

using namespace enc;
using namespace files;

// Constructor to initialize App object with arguments
App::App(args::Arguments app_args) : app_args_(std::move(app_args)) {
	std::cout << this->app_args_ << endl; // Print arguments
}

// Function to process input based on encryption or decryption mode
void App::processInput() {
	if (this->app_args_.encrypt_mode() == args::NONE) {
		return; // If no encryption or decryption mode specified, return
	}

	// Depending on the coder type specified in the arguments, create the corresponding coder object
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

	// Get input and output file handles
	auto if_stream = FileService::getInputHandle(this->app_args_.input_file().c_str());
	auto of_stream = FileService::getOutputHandle(this->app_args_.output_file().c_str());

	string line, processed_line;
	// Process each line of input file
	while (getline(if_stream, line)) {
		if (this->app_args_.encrypt_mode() == args::ENCRYPT) {
			const string sanitized_in = Coder::sanitize(line);
			processed_line = this->app_coder_->encode(sanitized_in); // Encode input line
		} else {
			processed_line = this->app_coder_->decode(line); // Decode input line
		}
		of_stream << processed_line << endl; // Write processed line to output file
	}
	of_stream.close(); // Close output file stream
	if_stream.close(); // Close input file stream

	// Print encryption or decryption completion message
	if (this->app_args_.encrypt_mode() != args::NONE) {
		std::cout << (this->app_args_.encrypt_mode() == args::ENCRYPT ? "Encryption completed." : "Decryption completed");
	}
}

// Function to run the application
void App::run() {
	processInput(); // Process input based on specified mode
	tryToCrackTheEncoding(); // Try to crack the encoding if specified
}

// Function to attempt to crack the encoding
void App::tryToCrackTheEncoding() {
	// If not in encryption or decryption mode or not in brute force crack mode, return
	if (this->app_args_.encrypt_mode() != args::NONE && this->app_args_.getCrackEncMode() != args::BRUTE_FORCE) {
		return;
	}

	// Initialize English n-grams probability data
	const auto enGramsProbability = initializeBaseEnGramsData();

	// Sanitize input and process monograms
	const double totalMonograms = sanitizeFileAndProcessMonograms();

	// Calculate critical chi-square value
	const double criticalValue = gsl_cdf_chisq_Pinv(0.95, totalMonograms);

	// Initialize standard variables
	int iteration = 0;
	double chiSquare;
	std::string line, processed_line;
	utils::NgramsUtil util = utils::NgramsUtil(this->app_args_.getBruteForceNgramsMode());

	// Create coder object based on coder type specified in arguments
	if (this->app_args_.getCoderType() == args::CESAR) {
		this->app_coder_ = new CesarCoder();
	} else {
		this->app_coder_ = new AffineCoder();
	}

	// Read from sanitized input
	ifstream in = files::FileService::getInputHandle(this->app_args_.tmpInputFile().c_str());
	do {
		// Update loop, reset util and ifstream position
		in.clear();
		in.seekg(0, std::ios::beg);
		iteration++;
		util.reset();

		// Initialize new cipher key
		app_coder_->setKeyForIteration(iteration);

		// Decode input
		while (getline(in, line)) {
			processed_line = app_coder_->decode(line);
			// Process decoded line
			util.processLine(processed_line);
		}

		// Test chi-square value
		chiSquare = calculateChiSquare(util, enGramsProbability);

		// Print iteration and chi-square value
		std::cout << "End of iteration: " << iteration << ", and the critical val is:" << criticalValue << ", current chiSquare is:"
		          << std::setprecision(15) << chiSquare << endl;

		// If coder type is Cesar and iteration is greater than or equal to 26, break the loop
		if (this->app_args_.getCoderType() == args::CESAR && iteration >= 26) {
			break;
		}
	} while (chiSquare > criticalValue);

	// If chi-square value is greater than critical value, decipher key not found
	if (chiSquare > criticalValue) {
		std::cout << "Decipher key not found." << endl;
		return;
	}

	// Print decipher information and write final result
	printDecipherInfo(iteration);
	decipherAndWriteFinalResult(*app_coder_, in);

	// Close input file stream
	in.close();
}

// Function to print decipher information
void App::printDecipherInfo(int iteration) const {
	if (app_args_.getCoderType() == args::CESAR) {
		cout << "The cesar encoding has been broken, and the key was: " << iteration << endl;
	} else {
		cout << "The affine encoding has been broken, and the keys were: " << endl;
		// Print keys map for AffineCoder
		for (const auto &[k, v]: dynamic_cast<AffineCoder *>(app_coder_)->getKeysMap()) {
			cout << "Key:" << k << " -> Val:" << v << endl;
		}
	}
}

// Function to initialize base English n-grams data
std::map<std::string, double> App::initializeBaseEnGramsData() {
	// Initialize counter for n-grams and probability map
	auto counter = std::map<std::string, int>();
	auto probabilityMap = std::map<std::string, double>();
	std::int64_t total = 0;
	std::string line;

	// Get file paths and n-grams mode
	const char *grams_file = this->app_args_.getBruteForceNgramsFile().c_str();
	int n_grams_mode = this->app_args_.getBruteForceNgramsMode();

	// Open input file stream
	auto infile = files::FileService::getInputHandle(grams_file);

	// Read and process each line of the file
	while (getline(infile, line)) {
		// Check if line contains valid n-grams data
		if (line.size() >= n_grams_mode + 2) {
			// Extract n-gram expression and count
			const auto expr = line.substr(0, n_grams_mode);
			const int count = std::stoi(line.substr(n_grams_mode + 1));

			// Update total count and insert into counter
			counter.insert({expr, count});
			total += count;
		}
	}

	// Close input file stream
	infile.close();

	// Calculate probability for each n-gram and insert into probability map
	double probability;
	for (const auto &[ngram, count]: counter) {
		probability = static_cast<double>(count) / static_cast<double>(total);
		probabilityMap.insert({ngram, probability});
	}

	return probabilityMap;
}

// Function to calculate the chi-square value
double App::calculateChiSquare(utils::NgramsUtil &util, const std::map<std::string, double> &probabilityMap) {
	// Initialize chi-square value
	double chi = 0.0;

	// Get total grams count and tested text grams counter
	const auto totalGrams = util.getTotal();
	const auto &tested_text_grams_counter = util.getCounter();

	// Calculate chi-square for each n-gram
	for (const auto &[ngram, count]: tested_text_grams_counter) {
		// Get example probability from probability map
		double example_probability = probabilityMap.find(ngram)->second;

		// Calculate expected count
		double expected_count = static_cast<double>(totalGrams) * example_probability;

		// Calculate X^2
		auto power = static_cast<double>(std::pow(static_cast<double>(count) - expected_count, 2));
		double x_2 = expected_count == 0 ? 0.0 : power / expected_count;

		// Update chi-square
		chi += x_2;
	}

	return chi;
}

// Function to decipher the input file using the provided coder and write the final result to an output file
void App::decipherAndWriteFinalResult(enc::Coder &coder, std::ifstream &in) {
	std::string line, processed_line;

	// Open output file for writing the deciphered data
	std::ofstream of = files::FileService::getOutputHandle(this->app_args_.output_file().c_str());

	// Reset file stream to the beginning
	in.clear();
	in.seekg(0, std::ios::beg);

	// Decode each line of the input file and write the deciphered data to the output file
	while (getline(in, line)) {
		processed_line = coder.decode(line);
		of << processed_line << std::endl;
	}

	// Close the output file
	of.close();
}

// Function to sanitize the input file and process monograms, returning the total count of monograms
double App::sanitizeFileAndProcessMonograms() {
	std::string line;
	utils::NgramsUtil util = utils::NgramsUtil(this->app_args_.getBruteForceNgramsMode());

	// Open input and output files
	std::ifstream in = files::FileService::getInputHandle(this->app_args_.input_file().c_str());
	std::ofstream of = files::FileService::getOutputHandle(this->app_args_.tmpInputFile().c_str());

	// Sanitize the input file and process each line
	while (getline(in, line)) {
		const std::string sanitized_in = Coder::sanitize(line);

		// Process sanitized line
		util.processLine(sanitized_in);
		of << sanitized_in << std::endl;
	}

	// Close input and output files
	of.close();
	in.close();

	// Return the total count of monograms
	return static_cast<double>(util.getTotal());
}


```

* Arguments.cpp

``` C++
//
// Created by part4 on 13.03.2024.
//

#include "headers/Arguments.h"

namespace args {

	// Constructor for Arguments class to parse command-line arguments
	Arguments::Arguments(int const argc, char const *argv[]) {
		bool encryptionModeInitialized = false;
		bool coderSpecified = false;

		// Iterate through command-line arguments
		for (int j = 1; j < argc; ++j) {
			const auto argument = argv[j];

			// Iterate through defined flags
			for (const auto &key: FLAGS | std::views::keys) {
				if (argument == key) {
					switch (FLAGS[key]) {
						case e: {
							this->encrypt_mode_ = ENCRYPT;
							encryptionModeInitialized = true;
							break;
						}
						case d: {
							this->encrypt_mode_ = DECRYPT;
							encryptionModeInitialized = true;
							break;
						}
						case i: {
							// Check if the next argument is a file name
							if (std::string value = argv[++j]; !value.starts_with('-')) {
								this->inputFile_ = value;
								break;
							}
							throw std::invalid_argument("Input file not specified.");
						}
						case o: {
							// Check if the next argument is a file name
							if (std::string value = argv[++j]; !value.starts_with('-')) {
								this->outputFile_ = value;
								break;
							}
							throw std::invalid_argument("Output file not specified.");
						}
						case k: {
							// Check if the next argument is a file name
							if (j + 1 < argc) {
								if (std::string value = argv[++j]; !value.starts_with('-')) {
									this->keyFile_ = value;
									break;
								}
							}
							throw std::invalid_argument("Key file not specified.");
						}
						case a: {
							if (j + 1 < argc) {
								if (std::string value = argv[++j]; !value.starts_with('-')) {
									if (value == "bf") {
										this->crack_mode_ = BRUTE_FORCE;
									}

									if (this->crack_mode_ == NO_CRACK) {
										throw std::invalid_argument("Crack encoding mode not specified.");
									}
									break;
								}
							}
							break;
						}
						case ca: {
							this->coder_type_ = AFFINITY;
							coderSpecified = true;
							break;
						}
						case cc: {
							this->coder_type_ = CESAR;
							coderSpecified = true;
							break;
						}
						case n1: {
							this->brute_force_ngrams_mode = 1;
							this->brute_force_ngrams_file = EnMonogramsFile;
							break;
						}
						case n2: {
							this->brute_force_ngrams_mode = 2;
							this->brute_force_ngrams_file = EnBigramsFile;
							break;
						}
						case n3: {
							this->brute_force_ngrams_mode = 3;
							this->brute_force_ngrams_file = EnTrigramsFile;
							break;
						}
						case n4: {
							this->brute_force_ngrams_mode = 4;
							this->brute_force_ngrams_file = EnQuadgramsFile;
							break;
						}
						default:
							break;
					}
					break;
				}
			}
		}

		// Check if encryption mode, coder type, and crack mode are specified
		if (!encryptionModeInitialized && !coderSpecified && this->crack_mode_ == NO_CRACK) {
			throw std::invalid_argument("Encrypt/Decrypt mode not specified. Check program parameters.");
		}
	}
}
```

* CesarCoder.cpp

``` C++
//
// Created by part4 on 17.03.2024.
//

#include "headers/CesarCoder.h"
#include "headers/FileService.h"

namespace enc {
	// Function to encode a character using the Caesar cipher
	char CesarCoder::encodeChar(const char in) const {
		int movedKey = in + this->cesar_key_;
		if (movedKey <= 90) {
			return static_cast<char>(movedKey);
		}

		return static_cast<char>(65 + ((movedKey - 90) % 26));
	}

	// Function to decode a character using the Caesar cipher
	char CesarCoder::decodeChar(const char in) const {
		int movedKey = in - this->cesar_key_;
		if (movedKey >= 65) {
			return static_cast<char>(movedKey);
		}

		return static_cast<char>(90 - ((65 - movedKey) % 26));
	}

	// Function to extract the key for the Caesar cipher from a file
	void CesarCoder::extractKey() {
		this->cesar_key_ = files::FileService::readKey(this->args_->key_file().c_str());
	}
} // enc

```

* Coder.cpp

``` C++
//
// Created by part4 on 10.04.2024.
//

#include "headers/Coder.h"

namespace enc {
	// Function to sanitize a string by removing non-alphabetic characters and converting lowercase letters to uppercase
	string Coder::sanitize(const string &in) {
		string sanitized_in;

		for (const auto c: in) {
			if (c >= 97 && c <= 122) { // Check if the character is lowercase
				sanitized_in += static_cast<char>(std::toupper(c)); // Convert to uppercase
				continue;
			}

			if (c >= 65 && c <= 90) { // Check if the character is uppercase
				sanitized_in += c;
			}
		}

		return sanitized_in;
	}

	// Function to encode a string
	string Coder::encode(const string &in) {
		string out;
		for (const auto c: in) {
			const char encoded_char = encodeChar(c);
			out += encoded_char;
		}
		return out;
	}

	// Function to decode a string
	string Coder::decode(const string &in)  {
		string out;
		for (const auto c: in) {
			const char decoded_char = decodeChar(c);
			out += decoded_char;
		}
		return out;
	}

}

```

* FileService.cpp

``` C++
//
// Created by part4 on 13.03.2024.
//

#include "headers/FileService.h"

using namespace std;

namespace files {
	// Function to read an integer key from a file
	int FileService::readKey(const char *file) {
		int key = 0;

		ifstream infile(file);
		string line;
		if (getline(infile, line)) {
			key = std::stoi(line); // Convert string to integer
		}
		infile.close();

		return key;
	}

	// Function to get an input file stream handle
	std::ifstream FileService::getInputHandle(const char *file) {
		return ifstream(file);
	}

	// Function to get an output file stream handle
	std::ofstream FileService::getOutputHandle(const char *file) {
		return ofstream(file);
	}

} // args

```

* NgramsUtil.cpp

``` C++
//
// Created by part4 on 22.03.2024.
//

#include "headers/NgramsUtil.h"   // Include the header file for NgramsUtil
#include "headers/Arguments.h"    // Include the header file for Arguments (if needed)

using namespace std;

namespace utils {
	// Process a single line of text to extract n-grams and update their frequencies
	void NgramsUtil::processLine(const string &line) {
		for (int i = 0; i < line.size(); i++) {
			// Ensure there are enough characters left in the line to form an n-gram
			if (i + this->mode_ >= line.size()) {
				return;
			}

			// Extract the n-gram from the current position in the line
			string expr = line.substr(i, this->mode_);

			// Update the frequency count for the extracted n-gram
			if (const auto find = this->counter_.find(expr); find == this->counter_.end()) {
				// If the n-gram is not found in the counter, add it with frequency 1
				auto pair = std::pair<const string, int>(expr.c_str(), 1);
				this->counter_.insert(pair);
			} else {
				// If the n-gram is already in the counter, increment its frequency
				find->second += 1;
			}

			// Increment the total count of processed n-grams
			this->total_++;
		}
	}

	// Get the map containing n-gram frequencies
	const map<const std::string, int> &NgramsUtil::getCounter() const {
		return counter_;
	}

	// Get the total count of processed n-grams
	int64_t NgramsUtil::getTotal() const {
		return total_;
	}

	// Reset the internal state of the NgramsUtil object
	void NgramsUtil::reset() {
		this->total_ = 0;
		this->counter_.clear();
	}
}

```

* main.cpp

``` C++
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

```


### Wyniki

Do testów zadań użyto następującego tekstu referencyjnego
```
She stood by the window, gazing out at the city below as the sun dipped low on the horizon. It had been a long day at work, but the weariness melted away as she heard the familiar sound of his footsteps approaching. With a soft smile playing on her lips, she turned to face him, her heart skipping a beat at the sight of him.

"Hey," he said, his voice warm and filled with affection as he crossed the room to wrap her in his arms. "Rough day?"

She nodded, leaning into his embrace, finding solace in his presence. "But seeing you makes it all better."

They stood there for a moment, lost in each other's arms, the world outside fading into insignificance. In that moment, nothing else mattered but the love they shared.

The night was still, the air heavy with anticipation as Detective Miller surveyed the crime scene. A chill ran down his spine as he studied the scene before him – the victim lying motionless on the ground, surrounded by a pool of blood that glistened in the moonlight.

Something didn't add up. There were no signs of struggle, no clues left behind to hint at the perpetrator. It was as if the killer had vanished into thin air, leaving nothing but questions in their wake.

Miller narrowed his eyes, his mind racing as he pieced together the puzzle before him. This was no ordinary case; this was a challenge unlike any he had faced before. But he was determined to crack it, to bring justice to the victim and closure to their loved ones.

The darkness pressed in around her as she navigated the labyrinthine corridors of the abandoned asylum. Every sound echoed ominously, sending shivers down her spine as she pressed on, her heart pounding in her chest.

She knew the risks of coming here alone, but the lure of the unknown was too strong to resist. There were secrets hidden within these walls, secrets that begged to be uncovered, no matter the cost.

As she rounded a corner, a figure loomed before her, their eyes gleaming in the darkness. She froze, her breath catching in her throat as fear gripped her heart. But she refused to back down, steeling herself for whatever lay ahead.

The forest was alive with magic, the air humming with the whispers of ancient spells and enchantments. Creatures of myth and legend darted through the underbrush, their eyes alight with curiosity as they watched the lone traveler making her way through the dense foliage.

She was on a quest, driven by a sense of purpose that burned bright within her soul. With each step, she drew closer to her destiny, guided by the wisdom of the stars and the guidance of her trusty companions.

But danger lurked around every corner, testing her resolve and pushing her to the limits of her strength. Yet she pressed on, fueled by courage and determination, knowing that the fate of the world rested on her shoulders.

These longer examples offer a glimpse into the immersive worlds and captivating narratives often found in light literature.
```

Dla wygodnego korzystania z aplikacji dodano dodatkowe dwie flagi do rozróżniania szyfru którym aplikacja szyfruje, deszyfruje i próbuje 
złamać szyfr.

Szyfr Cezara
```
-cc
```

Szyfr Afiniczny
```
-ca
```

Dla brute force dodano także flagi `n1,n2,n3,n4`, które definiują sposób testowania tekstu deszyfrowanego na podstawie `mono,bi,tri,quad` 
gramów 
przykładowych 

#### Zadanie 1

Szyfracja:
* Uruchomienie szyfracji dla klucza 13 i szyfrem cezara

```
-e -cc -k ../data/key_cesar.txt -i ../data/in_decrypted.txt -o ../result/out_encrypted_cesar.txt
```

Skutkowało rezultatem:

```
GURGHCCQOMHURKVBQCKTNNVBTCIHNHHURPVHMORYCKNGHURGIBQVDDRQYCKCBHURUCFVNCBVHUNQORRBNYCBTQNMNHKCFXOIHHURKRNFVBRGGZRYHRQNKNMNGGURURNFQHURSNZVYVNFGCIBQCSUVGSCCHGHRDGNDDFCNPUVBTKVHUNGCSHGZVYRDYNMVBTCBURFYVDGGURHIFBRQHCSNPRUVZURFURNFHGXVDDVBTNORNHNHHURGVTUHCSUVZ

URMURGNVQUVGJCVPRKNFZNBQSVYYRQKVHUNSSRPHVCBNGURPFCGGRQHURFCCZHCKFNDURFVBUVGNFZGFCITUQNM

GURBCQQRQYRNBVBTVBHCUVGRZOFNPRSVBQVBTGCYNPRVBUVGDFRGRBPROIHGRRVBTMCIZNXRGVHNYYORHHRF

HURMGHCCQHURFRSCFNZCZRBHYCGHVBRNPUCHURFGNFZGHURKCFYQCIHGVQRSNQVBTVBHCVBGVTBVSVPNBPRVBHUNHZCZRBHBCHUVBTRYGRZNHHRFRQOIHHURYCJRHURMGUNFRQ

HURBVTUHKNGGHVYYHURNVFURNJMKVHUNBHVPVDNHVCBNGQRHRPHVJRZVYYRFGIFJRMRQHURPFVZRGPRBRNPUVYYFNBQCKBUVGGDVBRNGURGHIQVRQHURGPRBRORSCFRUVZHURJVPHVZYMVBTZCHVCBYRGGCBHURTFCIBQGIFFCIBQRQOMNDCCYCSOYCCQHUNHTYVGHRBRQVBHURZCCBYVTUH

GCZRHUVBTQVQBHNQQIDHURFRKRFRBCGVTBGCSGHFITTYRBCPYIRGYRSHORUVBQHCUVBHNHHURDRFDRHFNHCFVHKNGNGVSHURXVYYRFUNQJNBVGURQVBHCHUVBNVFYRNJVBTBCHUVBTOIHEIRGHVCBGVBHURVFKNXR

ZVYYRFBNFFCKRQUVGRMRGUVGZVBQFNPVBTNGURDVRPRQHCTRHURFHURDINNYRORSCFRUVZHUVGKNGBCCFQVBNFMPNGRHUVGKNGNPUNYYRBTRIBYVXRNBMURUNQSNPRQORSCFROIHURKNGQRHRFZVBRQHCPFNPXVHHCOFVBTWIGHVPRHCHURJVPHVZNBQPYCGIFRHCHURVFYCJRQCBRG

HURQNFXBRGGDFRGGRQVBNFCIBQURFNGGURBNJVTNHRQHURYNOMFVBHUVBRPCFFVQCFGCSHURNONBQCBRQNGMYIZRJRFMGCIBQRPUCRQCZVBCIGYMGRBQVBTGUVJRFGQCKBURFGDVBRNGGURDFRGGRQCBURFURNFHDCIBQVBTVBURFPURGH

GURXBRKHURFVGXGCSPCZVBTURFRNYCBROIHHURYIFRCSHURIBXBCKBKNGHCCGHFCBTHCFRGVGHHURFRKRFRGRPFRHGUVQQRBKVHUVBHURGRKNYYGGRPFRHGHUNHORTTRQHCORIBPCJRFRQBCZNHHRFHURPCGH

NGGURFCIBQRQNPCFBRFNSVTIFRYCCZRQORSCFRURFHURVFRMRGTYRNZVBTVBHURQNFXBRGGGURSFCNRURFOFRNHUPNHPUVBTVBURFHUFCNHNGSRNFTFVDDRQURFURNFHOIHGURFRSIGRQHCONPXQCKBGHRRYVBTURFGRYSSCFKUNHRJRFYNMNURNQ

HURSCFRGHKNGNYVJRKVHUZNTVPHURNVFUIZZVBTKVHUHURKUVGDRFGCSNBPVRBHGDRYYGNBQRBPUNBHZRBHGPFRNHIFRGCSZMHUNBQYRTRBQQNFHRQHUFCITUHURIBQRFOFIGUHURVFRMRGNYVTUHKVHUPIFVCGVHMNGHURMKNHPURQHURYCBRHFNJRYRFZNXVBTURFKNMHUFCITUHURQRBGRSCYVNTR

GURKNGCBNEIRGHQFVJRBOMNGRBGRCSDIFDCGRHUNHOIFBRQOFVTUHKVHUVBURFGCIYKVHURNPUGHRDGURQFRKPYCGRFHCURFQRGHVBMTIVQRQOMHURKVGQCZCSHURGHNFGNBQHURTIVQNBPRCSURFHFIGHMPCZDNBVCBG

OIHQNBTRFYIFXRQNFCIBQRJRFMPCFBRFHRGHVBTURFFRGCYJRNBQDIGUVBTURFHCHURYVZVHGCSURFGHFRBTHUMRHGURDFRGGRQCBSIRYRQOMPCIFNTRNBQQRHRFZVBNHVCBXBCKVBTHUNHHURSNHRCSHURKCFYQFRGHRQCBURFGUCIYQRFG

HURGRYCBTRFRLNZDYRGCSSRFNTYVZDGRVBHCHURVZZRFGVJRKCFYQGNBQPNDHVJNHVBTBNFFNHVJRGCSHRBSCIBQVBYVTUHYVHRFNHIFR

```

Deszyfracja:

* Uruchomienie deszyfracji dla klucza 13

```
-d -cc -k ../data/key_cesar.txt -i ../data/in_decrypted.txt -o ../result/out_encrypted_cesar.txt
```

Daje rezultat początkowy:

```
SHESTOODBYTHEWINDOWGAAINGOUTATTHECITYBELOWASTHESUNDIPPEDLOWONTHEHORIAONITHADBEENALONGDAYATWORKBUTTHEWEARINESSMELTEDAWAYASSHEHEARDTHEFAMILIARSOUNDOFHISFOOTSTEPSAPPROACHINGWITHASOFTSMILEPLAYINGONHERLIPSSHETURNEDTOFACEHIMHERHEARTSKIPPINGABEATATTHESIGHTOFHIM

HEYHESAIDHISVOICEWARMANDFILLEDWITHAFFECTIONASHECROSSEDTHEROOMTOWRAPHERINHISARMSROUGHDAY

SHENODDEDLEANINGINTOHISEMBRACEFINDINGSOLACEINHISPRESENCEBUTSEEINGYOUMAKESITALLBETTER

THEYSTOODTHEREFORAMOMENTLOSTINEACHOTHERSARMSTHEWORLDOUTSIDEFADINGINTOINSIGNIFICANCEINTHATMOMENTNOTHINGELSEMATTEREDBUTTHELOVETHEYSHARED

THENIGHTWASSTILLTHEAIRHEAVYWITHANTICIPATIONASDETECTIVEMILLERSURVEYEDTHECRIMESCENEACHILLRANDOWNHISSPINEASHESTUDIEDTHESCENEBEFOREHIMTHEVICTIMLYINGMOTIONLESSONTHEGROUNDSURROUNDEDBYAPOOLOFBLOODTHATGLISTENEDINTHEMOONLIGHT

SOMETHINGDIDNTADDUPTHEREWERENOSIGNSOFSTRUGGLENOCLUESLEFTBEHINDTOHINTATTHEPERPETRATORITWASASIFTHEKILLERHADVANISHEDINTOTHINAIRLEAVINGNOTHINGBUTQUESTIONSINTHEIRWAKE

MILLERNARROWEDHISEYESHISMINDRACINGASHEPIECEDTOGETHERTHEPUAALEBEFOREHIMTHISWASNOORDINARYCASETHISWASACHALLENGEUNLIKEANYHEHADFACEDBEFOREBUTHEWASDETERMINEDTOCRACKITTOBRINGJUSTICETOTHEVICTIMANDCLOSURETOTHEIRLOVEDONES

THEDARKNESSPRESSEDINAROUNDHERASSHENAVIGATEDTHELABYRINTHINECORRIDORSOFTHEABANDONEDASYLUMEVERYSOUNDECHOEDOMINOUSLYSENDINGSHIVERSDOWNHERSPINEASSHEPRESSEDONHERHEARTPOUNDINGINHERCHEST

SHEKNEWTHERISKSOFCOMINGHEREALONEBUTTHELUREOFTHEUNKNOWNWASTOOSTRONGTORESISTTHEREWERESECRETSHIDDENWITHINTHESEWALLSSECRETSTHATBEGGEDTOBEUNCOVEREDNOMATTERTHECOST

ASSHEROUNDEDACORNERAFIGURELOOMEDBEFOREHERTHEIREYESGLEAMINGINTHEDARKNESSSHEFROAEHERBREATHCATCHINGINHERTHROATASFEARGRIPPEDHERHEARTBUTSHEREFUSEDTOBACKDOWNSTEELINGHERSELFFORWHATEVERLAYAHEAD

THEFORESTWASALIVEWITHMAGICTHEAIRHUMMINGWITHTHEWHISPERSOFANCIENTSPELLSANDENCHANTMENTSCREATURESOFMYTHANDLEGENDDARTEDTHROUGHTHEUNDERBRUSHTHEIREYESALIGHTWITHCURIOSITYASTHEYWATCHEDTHELONETRAVELERMAKINGHERWAYTHROUGHTHEDENSEFOLIAGE

SHEWASONAQUESTDRIVENBYASENSEOFPURPOSETHATBURNEDBRIGHTWITHINHERSOULWITHEACHSTEPSHEDREWCLOSERTOHERDESTINYGUIDEDBYTHEWISDOMOFTHESTARSANDTHEGUIDANCEOFHERTRUSTYCOMPANIONS

BUTDANGERLURKEDAROUNDEVERYCORNERTESTINGHERRESOLVEANDPUSHINGHERTOTHELIMITSOFHERSTRENGTHYETSHEPRESSEDONFUELEDBYCOURAGEANDDETERMINATIONKNOWINGTHATTHEFATEOFTHEWORLDRESTEDONHERSHOULDERS

THESELONGEREXAMPLESOFFERAGLIMPSEINTOTHEIMMERSIVEWORLDSANDCAPTIVATINGNARRATIVESOFTENFOUNDINLIGHTLITERATURE

```

#### Zadanie 2

Brute force:
* Uruchomienie brute force dla szyfru cezara w stosunku do monogramów

```
-a bf -cc -n1 -i ../data/in_encrypted_cesar.txt -o ../result/out_decrypted_brute_force.txt
```

Daje rezultat:

```
[
encrypt_mode_: 0
inputFile_: ../data/in_encrypted_cesar.txt
outputFile_: ../result/out_decrypted_brute_force.txt
keyFile_:
analize_mode_: 1
coder_type_: 1
]

End of iteration: 1, and the critical val is:2440.34, current chiSquare is:46836.007837093
End of iteration: 2, and the critical val is:2440.33776737175, current chiSquare is:4320.06847027907
End of iteration: 3, and the critical val is:2440.33776737175, current chiSquare is:9813.17310058036
End of iteration: 4, and the critical val is:2440.33776737175, current chiSquare is:24453.1623117086
End of iteration: 5, and the critical val is:2440.33776737175, current chiSquare is:16402.4733410899
End of iteration: 6, and the critical val is:2440.33776737175, current chiSquare is:4478.66586453871
End of iteration: 7, and the critical val is:2440.33776737175, current chiSquare is:13770.3289022791
End of iteration: 8, and the critical val is:2440.33776737175, current chiSquare is:30412.2325008463
End of iteration: 9, and the critical val is:2440.33776737175, current chiSquare is:12989.2836618498
End of iteration: 10, and the critical val is:2440.33776737175, current chiSquare is:16529.3972854837
End of iteration: 11, and the critical val is:2440.33776737175, current chiSquare is:21052.732199893
End of iteration: 12, and the critical val is:2440.33776737175, current chiSquare is:9422.40570031137
End of iteration: 13, and the critical val is:2440.33776737175, current chiSquare is:81.1663746990747
The cesar encoding has been broken, and the key was: 13

Process finished with exit code 0
```

#### Zadanie 3

Szyfracja:
* Uruchomienie szyfracji afinicznej dla klucza

```
A V
B E
C Z
D I
E G
F M
g B
H F
I P
J U
K O
L R
M A
N K
O N
P C
Q S
R T
S Q
T L
U W
V Y
W J
X D
Y X
Z H
```

```
-e -ca -k ../data/keys_affine.txt -i ../data/in_decrypted.txt -o ../result/out_encrypted_affine.txt
```

Daje rezultat:

```
QFGQLNNIEXLFGJPKINJBVHPKBNWLVLLFGZPLXEGRNJVQLFGQWKIPCCGIRNJNKLFGFNTPHNKPLFVIEGGKVRNKBIVXVLJNTOEWLLFGJGVTPKGQQAGRLGIVJVXVQQFGFGVTILFGMVAPRPVTQNWKINMFPQMNNLQLGCQVCCTNVZFPKBJPLFVQNMLQAPRGCRVXPKBNKFGTRPCQQFGLWTKGILNMVZGFPAFGTFGVTLQOPCCPKBVEGVLVLLFGQPBFLNMFPA

FGXFGQVPIFPQYNPZGJVTAVKIMPRRGIJPLFVMMGZLPNKVQFGZTNQQGILFGTNNALNJTVCFGTPKFPQVTAQTNWBFIVX

QFGKNIIGIRGVKPKBPKLNFPQGAETVZGMPKIPKBQNRVZGPKFPQCTGQGKZGEWLQGGPKBXNWAVOGQPLVRREGLLGT

LFGXQLNNILFGTGMNTVANAGKLRNQLPKGVZFNLFGTQVTAQLFGJNTRINWLQPIGMVIPKBPKLNPKQPBKPMPZVKZGPKLFVLANAGKLKNLFPKBGRQGAVLLGTGIEWLLFGRNYGLFGXQFVTGI

LFGKPBFLJVQQLPRRLFGVPTFGVYXJPLFVKLPZPCVLPNKVQIGLGZLPYGAPRRGTQWTYGXGILFGZTPAGQZGKGVZFPRRTVKINJKFPQQCPKGVQFGQLWIPGILFGQZGKGEGMNTGFPALFGYPZLPARXPKBANLPNKRGQQNKLFGBTNWKIQWTTNWKIGIEXVCNNRNMERNNILFVLBRPQLGKGIPKLFGANNKRPBFL

QNAGLFPKBIPIKLVIIWCLFGTGJGTGKNQPBKQNMQLTWBBRGKNZRWGQRGMLEGFPKILNFPKLVLLFGCGTCGLTVLNTPLJVQVQPMLFGOPRRGTFVIYVKPQFGIPKLNLFPKVPTRGVYPKBKNLFPKBEWLSWGQLPNKQPKLFGPTJVOG

APRRGTKVTTNJGIFPQGXGQFPQAPKITVZPKBVQFGCPGZGILNBGLFGTLFGCWHHRGEGMNTGFPALFPQJVQKNNTIPKVTXZVQGLFPQJVQVZFVRRGKBGWKRPOGVKXFGFVIMVZGIEGMNTGEWLFGJVQIGLGTAPKGILNZTVZOPLLNETPKBUWQLPZGLNLFGYPZLPAVKIZRNQWTGLNLFGPTRNYGINKGQ

LFGIVTOKGQQCTGQQGIPKVTNWKIFGTVQQFGKVYPBVLGILFGRVEXTPKLFPKGZNTTPINTQNMLFGVEVKINKGIVQXRWAGYGTXQNWKIGZFNGINAPKNWQRXQGKIPKBQFPYGTQINJKFGTQCPKGVQQFGCTGQQGINKFGTFGVTLCNWKIPKBPKFGTZFGQL

QFGOKGJLFGTPQOQNMZNAPKBFGTGVRNKGEWLLFGRWTGNMLFGWKOKNJKJVQLNNQLTNKBLNTGQPQLLFGTGJGTGQGZTGLQFPIIGKJPLFPKLFGQGJVRRQQGZTGLQLFVLEGBBGILNEGWKZNYGTGIKNAVLLGTLFGZNQL

VQQFGTNWKIGIVZNTKGTVMPBWTGRNNAGIEGMNTGFGTLFGPTGXGQBRGVAPKBPKLFGIVTOKGQQQFGMTNHGFGTETGVLFZVLZFPKBPKFGTLFTNVLVQMGVTBTPCCGIFGTFGVTLEWLQFGTGMWQGILNEVZOINJKQLGGRPKBFGTQGRMMNTJFVLGYGTRVXVFGVI

LFGMNTGQLJVQVRPYGJPLFAVBPZLFGVPTFWAAPKBJPLFLFGJFPQCGTQNMVKZPGKLQCGRRQVKIGKZFVKLAGKLQZTGVLWTGQNMAXLFVKIRGBGKIIVTLGILFTNWBFLFGWKIGTETWQFLFGPTGXGQVRPBFLJPLFZWTPNQPLXVQLFGXJVLZFGILFGRNKGLTVYGRGTAVOPKBFGTJVXLFTNWBFLFGIGKQGMNRPVBG

QFGJVQNKVSWGQLITPYGKEXVQGKQGNMCWTCNQGLFVLEWTKGIETPBFLJPLFPKFGTQNWRJPLFGVZFQLGCQFGITGJZRNQGTLNFGTIGQLPKXBWPIGIEXLFGJPQINANMLFGQLVTQVKILFGBWPIVKZGNMFGTLTWQLXZNACVKPNKQ

EWLIVKBGTRWTOGIVTNWKIGYGTXZNTKGTLGQLPKBFGTTGQNRYGVKICWQFPKBFGTLNLFGRPAPLQNMFGTQLTGKBLFXGLQFGCTGQQGINKMWGRGIEXZNWTVBGVKIIGLGTAPKVLPNKOKNJPKBLFVLLFGMVLGNMLFGJNTRITGQLGINKFGTQFNWRIGTQ

LFGQGRNKBGTGDVACRGQNMMGTVBRPACQGPKLNLFGPAAGTQPYGJNTRIQVKIZVCLPYVLPKBKVTTVLPYGQNMLGKMNWKIPKRPBFLRPLGTVLWTG

```

Deszyfracja:
* Uruchomienie deszyfracji

```
-d -ca -k ../data/keys_affine.txt -i ../data/in_encrypted_affine.txt -o ../result/out_decrypted_affine.txt
```

Daje rezultat początkowy:

```
SHESTOODBYTHEWINDOWGAZINGOUTATTHECITYBELOWASTHESUNDIPPEDLOWONTHEHORIZONITHADBEENALONGDAYATWORKBUTTHEWEARINESSMELTEDAWAYASSHEHEARDTHEFAMILIARSOUNDOFHISFOOTSTEPSAPPROACHINGWITHASOFTSMILEPLAYINGONHERLIPSSHETURNEDTOFACEHIMHERHEARTSKIPPINGABEATATTHESIGHTOFHIM

HEYHESAIDHISVOICEWARMANDFILLEDWITHAFFECTIONASHECROSSEDTHEROOMTOWRAPHERINHISARMSROUGHDAY

SHENODDEDLEANINGINTOHISEMBRACEFINDINGSOLACEINHISPRESENCEBUTSEEINGYOUMAKESITALLBETTER

THEYSTOODTHEREFORAMOMENTLOSTINEACHOTHERSARMSTHEWORLDOUTSIDEFADINGINTOINSIGNIFICANCEINTHATMOMENTNOTHINGELSEMATTEREDBUTTHELOVETHEYSHARED

THENIGHTWASSTILLTHEAIRHEAVYWITHANTICIPATIONASDETECTIVEMILLERSURVEYEDTHECRIMESCENEACHILLRANDOWNHISSPINEASHESTUDIEDTHESCENEBEFOREHIMTHEVICTIMLYINGMOTIONLESSONTHEGROUNDSURROUNDEDBYAPOOLOFBLOODTHATGLISTENEDINTHEMOONLIGHT

SOMETHINGDIDNTADDUPTHEREWERENOSIGNSOFSTRUGGLENOCLUESLEFTBEHINDTOHINTATTHEPERPETRATORITWASASIFTHEKILLERHADVANISHEDINTOTHINAIRLEAVINGNOTHINGBUTQUESTIONSINTHEIRWAKE

MILLERNARROWEDHISEYESHISMINDRACINGASHEPIECEDTOGETHERTHEPUZZLEBEFOREHIMTHISWASNOORDINARYCASETHISWASACHALLENGEUNLIKEANYHEHADFACEDBEFOREBUTHEWASDETERMINEDTOCRACKITTOBRINGJUSTICETOTHEVICTIMANDCLOSURETOTHEIRLOVEDONES

THEDARKNESSPRESSEDINAROUNDHERASSHENAVIGATEDTHELABYRINTHINECORRIDORSOFTHEABANDONEDASYLUMEVERYSOUNDECHOEDOMINOUSLYSENDINGSHIVERSDOWNHERSPINEASSHEPRESSEDONHERHEARTPOUNDINGINHERCHEST

SHEKNEWTHERISKSOFCOMINGHEREALONEBUTTHELUREOFTHEUNKNOWNWASTOOSTRONGTORESISTTHEREWERESECRETSHIDDENWITHINTHESEWALLSSECRETSTHATBEGGEDTOBEUNCOVEREDNOMATTERTHECOST

ASSHEROUNDEDACORNERAFIGURELOOMEDBEFOREHERTHEIREYESGLEAMINGINTHEDARKNESSSHEFROZEHERBREATHCATCHINGINHERTHROATASFEARGRIPPEDHERHEARTBUTSHEREFUSEDTOBACKDOWNSTEELINGHERSELFFORWHATEVERLAYAHEAD

THEFORESTWASALIVEWITHMAGICTHEAIRHUMMINGWITHTHEWHISPERSOFANCIENTSPELLSANDENCHANTMENTSCREATURESOFMYTHANDLEGENDDARTEDTHROUGHTHEUNDERBRUSHTHEIREYESALIGHTWITHCURIOSITYASTHEYWATCHEDTHELONETRAVELERMAKINGHERWAYTHROUGHTHEDENSEFOLIAGE

SHEWASONAQUESTDRIVENBYASENSEOFPURPOSETHATBURNEDBRIGHTWITHINHERSOULWITHEACHSTEPSHEDREWCLOSERTOHERDESTINYGUIDEDBYTHEWISDOMOFTHESTARSANDTHEGUIDANCEOFHERTRUSTYCOMPANIONS

BUTDANGERLURKEDAROUNDEVERYCORNERTESTINGHERRESOLVEANDPUSHINGHERTOTHELIMITSOFHERSTRENGTHYETSHEPRESSEDONFUELEDBYCOURAGEANDDETERMINATIONKNOWINGTHATTHEFATEOFTHEWORLDRESTEDONHERSHOULDERS

THESELONGEREXAMPLESOFFERAGLIMPSEINTOTHEIMMERSIVEWORLDSANDCAPTIVATINGNARRATIVESOFTENFOUNDINLIGHTLITERATURE

```

#### Zadanie 4

Brute force:

* Weryfikacją monogramów

```
-a bf -ca -n1 -i ../data/in_encrypted_affine.txt -o ../result/out_decrypted_brute_force_affine.txt
```

Nie daje za dobrych rezultatów:

```
...
End of iteration: 1592, and the critical val is:2440.33776737175, current chiSquare is:19783.1113817505
End of iteration: 1593, and the critical val is:2440.33776737175, current chiSquare is:2035.13014502121
The affine encoding has been broken, and the keys were:
Key:A -> Val:I
Key:B -> Val:N
Key:C -> Val:Q
Key:D -> Val:M
Key:E -> Val:A
Key:F -> Val:K
Key:G -> Val:R
Key:H -> Val:F
Key:I -> Val:L
Key:J -> Val:X
Key:K -> Val:Z
Key:L -> Val:B
Key:M -> Val:E
Key:N -> Val:G
Key:O -> Val:P
Key:P -> Val:C
Key:Q -> Val:S
Key:R -> Val:H
Key:S -> Val:V
Key:T -> Val:W
Key:U -> Val:O
Key:V -> Val:Y
Key:W -> Val:T
Key:X -> Val:U
Key:Y -> Val:J
Key:Z -> Val:D
```

* Bigramów

Program przy ponad 100 000 iteracji nie natrafił na oryginalny klucz, który spełniał by oczekiwania co do prawdopobieństwa poprawności 
zdeszyfrowanego tekstu:

```
End of iteration: 115807, and the critical val is:2425.99966995021, current chiSquare is:8495471.25683956
End of iteration: 115808, and the critical val is:2425.99966995021, current chiSquare is:6217579.03337141
End of iteration: 115809, and the critical val is:2425.99966995021, current chiSquare is:655824.968374314
End of iteration: 115810, and the critical val is:2425.99966995021, current chiSquare is:79064248.9210879
End of iteration: 115811, and the critical val is:2425.99966995021, current chiSquare is:10230104.7034258
End of iteration: 115812, and the critical val is:2425.99966995021, current chiSquare is:1550096.15458144
End of iteration: 115813, and the critical val is:2425.99966995021, current chiSquare is:393894.646826224
End of iteration: 115814, and the critical val is:2425.99966995021, current chiSquare is:3275402.33901982
End of iteration: 115815, and the critical val is:2425.99966995021, current chiSquare is:1133905.41205518
End of iteration: 115816, and the critical val is:2425.99966995021, current chiSquare is:895981.041583318
End of iteration: 115817, and the critical val is:2425.99966995021, current chiSquare is:1001959.02803066
End of iteration: 115818, and the critical val is:2425.99966995021, current chiSquare is:390157.685861408
End of iteration: 115819, and the critical val is:2425.99966995021, current chiSquare is:1322865.73327057
End of iteration: 115820, and the critical val is:2425.99966995021, current chiSquare is:1930809.03264175
End of iteration: 115821, and the critical val is:2425.99966995021, current chiSquare is:4404465.65727648
End of iteration: 115822, and the critical val is:2425.99966995021, current chiSquare is:3036790.96190565
End of iteration: 115823, and the critical val is:2425.99966995021, current chiSquare is:4271256.45637742
End of iteration: 115824, and the critical val is:2425.99966995021, current chiSquare is:3749871.80917459
End of iteration: 115825, and the critical val is:2425.99966995021, current chiSquare is:1987119.46424285
End of iteration: 115826, and the critical val is:2425.99966995021, current chiSquare is:8130418.68202182
```

* Tri/Quad gramów

Testowanie różnych szyfrów idzie już w miliony iteracji i nie daje końcowych rezultatów, przynajmniej po 3 godzinnym uruchomieniu 
algorytmu, który testuje tylko oryginalne klucze bez duplikatów testów.

Łączna liczba kombinacji kluczy możliwych do przetestowania to:

403 291 461 126 605 650 322 784 256