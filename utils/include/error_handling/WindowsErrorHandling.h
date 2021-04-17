#ifndef ROGUELIKE_ENGINE_WINDOWSERRORHANDLING_H
#define ROGUELIKE_ENGINE_WINDOWSERRORHANDLING_H

#ifndef UNICODE
#define UNICODE
#endif

#include <Windows.h>
#include <d3dcompiler.h>
#include <string>
#include <iostream>
#pragma comment(lib, "d3dcompiler.lib")

#ifndef NDEBUG
#define DEBUG_HR(hr_call) { \
	::WindowsErrorHandling::ComStatus status = ::WindowsErrorHandling::GetHRStatus(hr_call); \
	if(status.status == ::WindowsErrorHandling::ComStatus::Status::FAILURE){            \
    	std::wcout << L"DEBUG_HR: On line " << __LINE__ << L" in file " << __FILE__ << std::endl;  \
		std::wcout << status.message << std::endl;                                      \
	}                                                                                   \
}
#else
#define DEBUG_HR(x)
#endif

namespace WindowsErrorHandling {
	struct ComStatus {
		enum class Status {FAILURE, SUCCESS};

		Status status;
		std::wstring message;
	};

	/*
	 * Usage:: Used to get info about Microsoft COM error codes.
	 *         This works for both DirectX11 and generic HR values.
	 */
	ComStatus GetHRStatus(HRESULT hr);
}

#endif // ROGUELIKE_ENGINE_WINDOWSERRORHANDLING_H