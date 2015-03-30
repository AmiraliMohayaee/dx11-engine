#pragma once

#include <d3d11.h>
#include <d3dx11.h>
#include <xnamath.h>
#include "Vec3.h"
#include "ConstantBuffer.h"


namespace DXEngine
{
	struct LightBuffer
	{
		XMMATRIX LightView;
		XMMATRIX LightProj;
		Vec3f LightPos;
		float padding;
	};

	typedef ConstantBuffer<LightBuffer> LightConstBuffer;

}