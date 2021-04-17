//
// Created by Yu on 4/17/2021.
//

#ifndef DIRECTXTESTS_SHADER_H
#define DIRECTXTESTS_SHADER_H

#include <lib.h>

void CreateVertexShader(const std::string& filepath, const std::string& entrypoint, D3D11_INPUT_ELEMENT_DESC bufferDescription[], UINT numDesc,
						Microsoft::WRL::ComPtr<ID3D11VertexShader>* OUTshader, Microsoft::WRL::ComPtr<ID3D11InputLayout>* OUTinputLayout);

void CreatePixelShader(const std::string& filepath, const std::string& entrypoint,
					   Microsoft::WRL::ComPtr<ID3D11PixelShader>* OUTshader);

#endif //DIRECTXTESTS_SHADER_H
