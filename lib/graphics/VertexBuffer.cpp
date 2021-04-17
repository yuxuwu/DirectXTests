//
// Created by Yu on 4/17/2021.
//

#include "VertexBuffer.h"

void CreateVertexBuffer(VERTEX vertices[], UINT numVertices,
						Microsoft::WRL::ComPtr<ID3D11Buffer>* OUTbuffer) {
	// Create Vertex Buffer
	D3D11_BUFFER_DESC bd = {0};
	bd.ByteWidth = sizeof(VERTEX) * numVertices;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	D3D11_SUBRESOURCE_DATA srd = {vertices, 0, 0};

	DEBUG_HR(d3dDevice->CreateBuffer(&bd, &srd, &*OUTbuffer));
}