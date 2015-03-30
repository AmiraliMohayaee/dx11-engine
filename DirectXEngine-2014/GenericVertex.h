#pragma once

#include <d3d11.h>
#include <d3dx11.h>
#include <xnamath.h>
#include "VertexBuffer.h"
#include "Shader.h"


namespace DXEngine
{
	struct GenericVertex
	{
		XMFLOAT4 Pos;
		XMFLOAT4 Color;
		XMFLOAT3 Normal;
		XMFLOAT2 Texture;

		GenericVertex() {}
		GenericVertex(XMFLOAT4 pos, XMFLOAT4 color, XMFLOAT3 normal, XMFLOAT2 texture) 
			: Pos(pos), Color(color), Normal(normal), Texture(texture) {}
	};

	class GenericVertexBuffer : public VertexBuffer<GenericVertex>
	{
	public:
		bool CreateInputLayout(Shader* shader) override;


	};

}