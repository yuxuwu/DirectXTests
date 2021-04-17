//
// Created by Yu on 4/17/2021.
//

#include "Shader.h"

static std::string CreateShaderCompileMessage(ID3DBlob* compileErrors) {
	std::string result{};

	if(compileErrors) {
		result = "A compile error was found for the shader: " +
				std::string((char*)compileErrors->GetBufferPointer());
		compileErrors->Release();
	}
	return result;
}

void CreateVertexShader(const std::string& filepath, const std::string& entrypoint, D3D11_INPUT_ELEMENT_DESC bufferDescription[], UINT numDesc,
						Microsoft::WRL::ComPtr<ID3D11VertexShader>* OUTshader, Microsoft::WRL::ComPtr<ID3D11InputLayout>* OUTinputLayout) {
	/// Compile Shader
	ID3D10Blob* compileResult = nullptr;
	ID3DBlob* compileErrors = nullptr;
	DEBUG_HR(
			D3DCompileFromFile(
					std::wstring(filepath.begin(), filepath.end()).c_str(),                                 // filename
					nullptr,                                          // define shader macros (optional)
					nullptr,                                          // shader include files (optional)
					entrypoint.c_str(),                               // shader entry point function
					"vs_4_0", // compilation target
					0,                                                // compile options bitfield (optional)
					0,                                                // compile options 2 bitfield (optional)
					&compileResult,  // p to compiled code
					&compileErrors)                                   // p to error msgs, NULL if no errors (optional)
	);

	std::string compileMsg(CreateShaderCompileMessage(compileErrors));
	if(!compileMsg.empty()) {
		std::cout << "Vertex Shader Compile Error Message: " << std::endl;
		std::cout << compileMsg << std::endl;
	}

	/// Create Shader
	DEBUG_HR(d3dDevice->CreateVertexShader(
			compileResult->GetBufferPointer(),
			compileResult->GetBufferSize(),
			nullptr,
			OUTshader->GetAddressOf()
	));

	/// Vertex Input Layout
	DEBUG_HR(d3dDevice->CreateInputLayout(
			bufferDescription,
			numDesc,
			compileResult->GetBufferPointer(),
			compileResult->GetBufferSize(),
			&*OUTinputLayout
	));
}

void CreatePixelShader(const std::string& filepath, const std::string& entrypoint,
					   Microsoft::WRL::ComPtr<ID3D11PixelShader>* OUTshader) {
	/// Compile Shader
	ID3D10Blob* compileResult = nullptr;
	ID3DBlob* compileErrors = nullptr;
	DEBUG_HR(
			D3DCompileFromFile(
					std::wstring(filepath.begin(), filepath.end()).c_str(),                                 // filename
					nullptr,                                          // define shader macros (optional)
					nullptr,                                          // shader include files (optional)
					entrypoint.c_str(),                               // shader entry point function
					"ps_4_0", // compilation target
					0,                                                // compile options bitfield (optional)
					0,                                                // compile options 2 bitfield (optional)
					&compileResult,  // p to compiled code
					&compileErrors)                                   // p to error msgs, NULL if no errors (optional)
	);

	std::string compileMsg(CreateShaderCompileMessage(compileErrors));
	if(!compileMsg.empty()) {
		std::cout << "Pixel Shader Compile Error Message: " << std::endl;
		std::cout << compileMsg << std::endl;
	}

	/// Create Shader
	DEBUG_HR(d3dDevice->CreatePixelShader(
			compileResult->GetBufferPointer(),
			compileResult->GetBufferSize(),
			nullptr,
			OUTshader->GetAddressOf()
	));
}