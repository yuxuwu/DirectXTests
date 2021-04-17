#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

#include <Windows.h>
#include <wrl/client.h>

using Microsoft::WRL::ComPtr;

#include <dxgi.h>
#include <d3d11.h>
#pragma comment(lib, "d3d11.lib")
#include <d3dcompiler.h>
#pragma comment(lib, "d3dcompiler.lib")

#include <iostream>
#include <string>

#include "error_handling/WindowsErrorHandling.h"