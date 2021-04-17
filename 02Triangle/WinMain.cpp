#ifndef UNICODE
#define UNICODE
#endif

#include <lib.h>

D3D_FEATURE_LEVEL d3dFeatureLevel;
Microsoft::WRL::ComPtr<ID3D11Device> d3dDevice;
Microsoft::WRL::ComPtr<ID3D11DeviceContext> d3dContext;
Microsoft::WRL::ComPtr<IDXGISwapChain> d3dSwapChain;
Microsoft::WRL::ComPtr<ID3D11RenderTargetView> backBuffer;

static void CreateConsoleForOutput() {
	AllocConsole();
	freopen_s((FILE**)stdout, "CONOUT$", "w", stdout); // redirect stdout to console
	HWND console_hwnd = GetConsoleWindow();
}


static void Triangle() {
	/// Create Assets
	D3D11_INPUT_ELEMENT_DESC ied[] = {
			{"Position", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0}
	};
	// Create Shaders
	ComPtr<ID3D11VertexShader> vertShader = nullptr;
	ComPtr<ID3D11InputLayout> inputLayout = nullptr;
	ComPtr<ID3D11PixelShader> pixShader = nullptr;


	CreateVertexShader("assets/shaders.shader", "VShader", ied, 1,
					   &vertShader, &inputLayout);
	CreatePixelShader("assets/shaders.shader", "PShader",
					  &pixShader);

	VERTEX TriangleVertices[] = {
			{0.0f, 0.5f, 0.0f},
			{0.45f, -0.5f, 0.0f},
			{-0.45f, -0.5f, 0.0f}
	};

	// Create Vertex Buffer
	UINT stride = sizeof(VERTEX);
	UINT offset = 0;
	ComPtr<ID3D11Buffer> vertBuffer = nullptr;
	CreateVertexBuffer(TriangleVertices, 3, &vertBuffer);

	/// Set Triangle
	// Set Shaders
	d3dContext->IASetInputLayout(inputLayout.Get());
	d3dContext->VSSetShader(vertShader.Get(), nullptr, 0);
	d3dContext->PSSetShader(pixShader.Get(), nullptr, 0);
	// Set Vertex Buffer
	d3dContext->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	d3dContext->IASetVertexBuffers(0, 1, vertBuffer.GetAddressOf(), &stride, &offset);
}

static void RenderFrame() {
	d3dContext->OMSetRenderTargets(1, backBuffer.GetAddressOf(), nullptr);

	float color[4] = {0.0f, 0.2f, 0.4f, 1.0f};
	d3dContext->ClearRenderTargetView(backBuffer.Get(), color);

	d3dContext->Draw(3, 0);

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

	Triangle();

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
