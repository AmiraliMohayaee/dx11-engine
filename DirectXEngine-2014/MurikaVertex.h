#pragma once

#include <d3d11.h>
#include <d3dx11.h>
#include <xnamath.h>
#include "VertexBuffer.h"
#include "Shader.h"


namespace DXEngine
{
	struct MurikaVertex
	{
		XMFLOAT4 Pos;
		XMFLOAT4 Color;

		MurikaVertex() {}
		MurikaVertex(XMFLOAT4 pos, XMFLOAT4 color) : Pos(pos), Color(color) {}
	};

	class MurikaVertexBuffer : public VertexBuffer<MurikaVertex>
	{
	public:
		bool CreateInputLayout(Shader* shader) override;
	};
}