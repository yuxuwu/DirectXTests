//
// Created by Yu on 1/17/2021.
//

#include "../include/error_handling/FileHandling.h"

std::string Utils::importFileToString(std::string filename) {
	std::string result;
	std::ifstream fileStream(filename);

	if(fileStream.is_open()){
		result = std::string(
				(std::istreambuf_iterator<char>(fileStream)),
				(std::istreambuf_iterator<char>()));
		fileStream.close();
	}

	return result;
}
