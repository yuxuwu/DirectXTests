//
// Created by Yu on 4/16/2021.
//

#include "D3DInit.h"

static void setupD3DDeviceAndSwapChain(const HWND&);
static void setupRenderTargets();
static void setupViewport(const HWND&);

static constexpr D3D_FEATURE_LEVEL _levels[] = {
		D3D_FEATURE_LEVEL_11_1,
		D3D_FEATURE_LEVEL_11_0,
		D3D_FEATURE_LEVEL_10_1,
		D3D_FEATURE_LEVEL_10_0,
		D3D_FEATURE_LEVEL_9_3,
		D3D_FEATURE_LEVEL_9_2,
		D3D_FEATURE_LEVEL_9_1
};

static void setupD3DDeviceAndSwapChain(const HWND& hwnd) {
	UINT deviceFlags = D3D11_CREATE_DEVICE_BGRA_SUPPORT;
	deviceFlags |= D3D11_CREATE_DEVICE_DEBUG;

	DXGI_SWAP_CHAIN_DESC swapChainDesc;
	ZeroMemory(&swapChainDesc, sizeof(DXGI_SWAP_CHAIN_DESC));
	swapChainDesc.Windowed = TRUE;
	swapChainDesc.BufferCount = 2;
	swapChainDesc.BufferDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
	swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	swapChainDesc.SampleDesc.Count = 1;
	swapChainDesc.SampleDesc.Quality = 0;
	swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_SEQUENTIAL;
	swapChainDesc.OutputWindow = hwnd;

	DEBUG_HR(
			D3D11CreateDeviceAndSwapChain(
					nullptr,                  //Pointer to: Video Adapter, null being default adapter
					D3D_DRIVER_TYPE_HARDWARE, //Driver ShaderType
					0,                        //Software Rasterizer
					deviceFlags,              //Flags
					_levels,                  //Feature levels
					ARRAYSIZE(_levels),       //Number Feature Levels given
					D3D11_SDK_VERSION,        //SDK Version
					&swapChainDesc,           //Pointer to: Swap Chain Desc
					&(d3dSwapChain),         //Pointer to Output: Swap Chain
					&(d3dDevice),            //Pointer to Output: D3D Device
					&(d3dFeatureLevel),      //Pointer to Output: Determined Feature Level
					&(d3dContext)            //Pointer to Output: D3D Device Context
			)
	);
}



void setupRenderTargets() {
	Microsoft::WRL::ComPtr<ID3D11Resource> currentBackBuffer;

	d3dSwapChain->GetBuffer(
			0,
			__uuidof(ID3D11Texture2D),
			reinterpret_cast<void**>(currentBackBuffer.ReleaseAndGetAddressOf()));

	d3dDevice->CreateRenderTargetView(
			currentBackBuffer.Get(),
			nullptr,
			backBuffer.ReleaseAndGetAddressOf());

	d3dContext->OMSetRenderTargets(
			1,
			backBuffer.GetAddressOf(),
			nullptr);
}



void setupViewport(const HWND& hwnd) {
	D3D11_VIEWPORT viewport;
	ZeroMemory(&viewport, sizeof(D3D11_VIEWPORT));

	RECT rect{};
	GetWindowRect(hwnd, &rect);

	viewport.TopLeftX = 0;
	viewport.TopLeftY = 0;
	viewport.Width = rect.right - rect.left;
	viewport.Height = rect.bottom - rect.top;

	std::cout << "Width: " << viewport.Width << " Height: " << viewport.Height << std::endl;

	d3dContext->RSSetViewports(1, &viewport);
}

void D3D_INIT(const HWND& hwnd) {
	setupD3DDeviceAndSwapChain(hwnd);
	setupRenderTargets();
	setupViewport(hwnd);
}