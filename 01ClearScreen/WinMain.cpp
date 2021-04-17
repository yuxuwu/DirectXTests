#ifndef UNICODE
#define UNICODE
#endif

#include <lib.h>
#include "../lib/graphics/D3DInit.h"

D3D_FEATURE_LEVEL d3dFeatureLevel;
Microsoft::WRL::ComPtr<ID3D11Device> d3dDevice;
Microsoft::WRL::ComPtr<ID3D11DeviceContext> d3dContext;
Microsoft::WRL::ComPtr<IDXGISwapChain> d3dSwapChain;
Microsoft::WRL::ComPtr<ID3D11RenderTargetView> backBuffer;

static void CreateConsoleForOutput();

static void RenderFrame() {
	d3dContext->OMSetRenderTargets(1, backBuffer.GetAddressOf(), nullptr);

	float color[4] = {0.0f, 0.2f, 0.4f, 1.0f};
	d3dContext->ClearRenderTargetView(backBuffer.Get(), color);

	d3dSwapChain->Present(1, 0);
}

int WINAPI WinMain(HINSTANCE hinstance, HINSTANCE, PSTR pCmdLine, int nCmdShow) {
	CreateConsoleForOutput();

	// Window init
	Window gameWindow;
	gameWindow.registerAndCreateWindow(hinstance);
	HWND hwnd = gameWindow.getWindowHandler();

	// Graphics Init
	D3D_INIT(hwnd);

	/// Main Loop
	ShowWindow(hwnd, nCmdShow);
	MSG msg = { };
	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
		RenderFrame();
	}

	return 0;
}

void CreateConsoleForOutput() {
	AllocConsole();
	freopen_s((FILE**)stdout, "CONOUT$", "w", stdout); // redirect stdout to console
	HWND console_hwnd = GetConsoleWindow();
}