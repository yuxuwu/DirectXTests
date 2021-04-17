//
// Created by Yu on 4/16/2021.
//

#ifndef DIRECTXTESTS_D3DINIT_H
#define DIRECTXTESTS_D3DINIT_H

#include <lib.h>

void D3D_INIT(const HWND&);

extern D3D_FEATURE_LEVEL d3dFeatureLevel;
extern Microsoft::WRL::ComPtr<ID3D11Device> d3dDevice;
extern Microsoft::WRL::ComPtr<ID3D11DeviceContext> d3dContext;
extern Microsoft::WRL::ComPtr<IDXGISwapChain> d3dSwapChain;
extern Microsoft::WRL::ComPtr<ID3D11RenderTargetView> backBuffer;

#endif //DIRECTXTESTS_D3DINIT_H
