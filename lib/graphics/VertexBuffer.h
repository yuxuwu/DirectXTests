//
// Created by Yu on 4/17/2021.
//

#ifndef DIRECTXTESTS_VERTEXBUFFER_H
#define DIRECTXTESTS_VERTEXBUFFER_H

#include <lib.h>

struct VERTEX {
	float X, Y, Z;
	float COLOR[3];
};

void CreateVertexBuffer(VERTEX vertices[], UINT numVertices,
						Microsoft::WRL::ComPtr<ID3D11Buffer>* OUTbuffer);


#endif //DIRECTXTESTS_VERTEXBUFFER_H
