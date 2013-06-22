#ifndef DELTACOLORING_PARAMETERPARSER
#define DELTACOLORING_PARAMETERPARSER

#include "DeltaColoringMode.hpp"
#include <string>
#include <iostream>
#include <fstream>

using std::string;
using std::ostream;
using std::istream;
using std::ofstream;
using std::ifstream;

namespace dColoring{
	class ParameterParser {
	public:
		ParameterParser(int, char*[]);
		~ParameterParser();
		DeltaColoringMode getMode() const;
		ostream& getOutput();
		istream& getInput();
		void closeOutput();
		void closeInput();
	private:
		DeltaColoringMode mMode;
		string mOutFilePath, mInFilePath;
		ofstream mOutFile;
		ifstream mInFile;
	};
}

#endif //DELTACOLORING_PARAMETERPARSER
