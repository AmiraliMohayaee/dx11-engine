#pragma once

#include <d3d11.h>
#include <d3dx11.h>
#include <xnamath.h>
#include "ConstantBuffer.h"


namespace DXEngine
{
	struct WVPBuffer
	{
		XMMATRIX View;
		XMMATRIX World;
		XMMATRIX Proj;
	};

	typedef ConstantBuffer<WVPBuffer> WVPConstBuffer;
}