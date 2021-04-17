#include <iostream>
#include <sstream>
#include <string>
#include "../include/error_handling/WindowsErrorHandling.h"


using namespace WindowsErrorHandling;

static std::wstring GetHResultDescription(UINT);

ComStatus WindowsErrorHandling::GetHRStatus(HRESULT hr) {
	if(FAILED(hr)) {
		return {ComStatus::Status::FAILURE, GetHResultDescription(hr)};
	}
	return {ComStatus::Status::SUCCESS, L""};
}

static std::wstring GetHResultDescription(UINT hr) {
	std::wstring result{};

	LPTSTR errorTextBuffer = nullptr;
	FormatMessage(
		FORMAT_MESSAGE_FROM_SYSTEM
		|FORMAT_MESSAGE_ALLOCATE_BUFFER
		|FORMAT_MESSAGE_IGNORE_INSERTS,
		nullptr, //Not used
		hr,
		0, //Language: Default
		(LPTSTR)&errorTextBuffer,
		0, //Memory size, not used since using allocate flag
		nullptr
	);
	if(nullptr != errorTextBuffer){
		std::wstringstream resultString{};
		resultString << "Error code: " << std::hex << "0x" << hr << std::endl;
		resultString << "Error text: " << errorTextBuffer << std::endl;

		result = resultString.str();
		LocalFree(errorTextBuffer);
		errorTextBuffer = nullptr;
	} else {
		std::cout << "errorTextBuffer was empty/null" << std::endl;
	}

	return result;
}

