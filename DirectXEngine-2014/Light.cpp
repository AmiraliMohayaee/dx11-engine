#include "Light.h"

namespace DXEngine
{
	void Light::SetLookAt(XMVECTOR pos, XMVECTOR target, XMVECTOR worldUp)
	{
		m_viewMatrix = XMMatrixLookAtLH(pos, target, worldUp);
	}

	void Light::SetLightPerspective(float fovY, float aspect, float zn, float zf)
	{
		m_projMatrix = XMMatrixPerspectiveFovLH(fovY, aspect, zn, zf);
	}

	XMMATRIX Light::GetView() const
	{
		return m_viewMatrix;
	}

	XMMATRIX Light::GetProj() const
	{
		return m_projMatrix;
	}
}