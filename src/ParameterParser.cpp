#include "../include/ParameterParser.hpp"
#include "../include/strings.h"
#include <iostream>
#include <stdlib.h>

using namespace dColoring;
using namespace std;

ParameterParser::ParameterParser(int argc, char* argv[]){
	switch(argc){
	case 2:
		mMode = TO_STDOUT;
		mInFilePath = argv[1];
		break;
	case 3:
		mMode = TO_FILE;
		mInFilePath = argv[1];
		mOutFilePath = argv[2];
		break;
	default:
		std::cerr << USAGE;
		exit(EXIT_FAILURE);
	}
}

ParameterParser::~ParameterParser(){
	if(mInFile.is_open()){
		mInFile.close();
	}
	if(mOutFile.is_open()){
		mOutFile.close();
	}
}

inline DeltaColoringMode ParameterParser::getMode() const{
	return mMode;
}

ostream& ParameterParser::getOutput(){
	switch(mMode){
	case TO_STDOUT:
		return cout;
	case TO_FILE:
		if(!mOutFile.is_open()){
			mOutFile.open(mOutFilePath.c_str());
		}
		return mOutFile;
	}
}

istream& ParameterParser::getInput(){
	if(!mInFile.is_open()){
		mInFile.open(mInFilePath.c_str());
	}
	return mInFile;
}

void ParameterParser::closeOutput(){
	if(mOutFile.is_open()){
		mOutFile.close();
	}
}

void ParameterParser::closeInput(){
	if(mInFile.is_open()){
		mInFile.close();
	}
}