//
// Created by Yu on 1/17/2021.
//

#include "platform/Window.h"
#include <iostream>

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

void Window::registerAndCreateWindow(HINSTANCE hInstance) {
	/// Register the window class.
	const wchar_t CLASS_NAME[]  = L"DirectXTest";

	WNDCLASS wc = { };
	wc.lpfnWndProc   = WindowProc;
	wc.hInstance     = hInstance;
	wc.lpszClassName = CLASS_NAME;

	RegisterClass(&wc);

	// Create the window.
	HWND hwnd = CreateWindowEx(
			0,                              // Optional window styles.
			CLASS_NAME,                     // Window class
			L"DirectXTest",                 // Window text
			WS_OVERLAPPEDWINDOW,            // Window style

			// Size and position
			CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,

			NULL,       // Parent window
			NULL,       // Menu
			hInstance,  // Instance handle
			NULL        // Additional application data
	);

	if (hwnd == NULL)
	{
		std::cout << "Window not created" << std::endl;
	} else {
		std::cout << "Window was created" << std::endl;
	}

	this->windowHandler = hwnd;
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
		case WM_DESTROY:
			PostQuitMessage(0);
			return 0;

		case WM_PAINT:
		{
			PAINTSTRUCT ps;
			HDC hdc = BeginPaint(hwnd, &ps);

			FillRect(hdc, &ps.rcPaint, (HBRUSH) (COLOR_WINDOW+1));
			EndPaint(hwnd, &ps);
		}
			return 0;

	}
	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

HWND Window::getWindowHandler() {
	return this->windowHandler;
}
