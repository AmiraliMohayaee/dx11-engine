#include "Camera.h"


namespace DXEngine
{
	XMVECTOR Camera::GetPosXM() const
	{
		return XMLoadFloat3(&m_pos);
	}

	XMFLOAT3 Camera::GetPos() const
	{
		return m_pos;
	}

	// Set frustum
	void Camera::SetLens(float fovY, float aspect, float zn, float zf)
	{
		m_fovY = fovY;
		m_aspect = aspect;
		m_nearZ = zn;
		m_farZ = zf;

/*		m_nearWindowHeight = 2.0f * m_nearZ * tanf(0.5f * m_fovY);
		m_farWindowHeight = 2.0f * m_farZ * tanf(0.5f * m_fovY);*/

		m_projMatrix = XMMatrixPerspectiveFovLH(m_fovY, m_aspect, m_nearZ, m_farZ);
		//XMSTOREmatr(&m_projMatrix, p);
	}

	float Camera::GetFovX() const
	{
		float halfWidth = 0.5f * GetNearWindowWidth();
		return 2.0f * atan(halfWidth / m_nearZ);
	}

	float Camera::GetNearWindowWidth() const
	{
		return m_aspect * m_nearWindowHeight;
	}

	float Camera::GetNearWindowHeight() const
	{
		return m_nearWindowHeight;
	}

	float Camera::GetFarWindowWidth() const
	{
		return m_aspect * m_farWindowHeight;
	}

	float Camera::GetFarWindowHeight() const
	{
		return m_farWindowHeight;
	}

	// Functions for camera transoforms
	void Camera::Walk(float d)
	{
		// m_pos += direction * m_look vector;
		XMVECTOR s = XMVectorReplicate(d);
		XMVECTOR l = XMLoadFloat3(&m_look);
		XMVECTOR p = XMLoadFloat3(&m_pos);
		XMStoreFloat3(&m_pos, XMVectorMultiplyAdd(s, l, p));
	}

	void Camera::Strafe(float d)
	{
		// m_pos += direction * m_right vector;
		XMVECTOR s = XMVectorReplicate(d);
		XMVECTOR r = XMLoadFloat3(&m_right);
		XMVECTOR p = XMLoadFloat3(&m_pos);
		XMStoreFloat3(&m_pos, XMVectorMultiplyAdd(s, r, p));
	}

	void Camera::Pitch(float angle)
	{
		// Rotate up and look vector about the right vector
		XMMATRIX R = XMMatrixRotationAxis(XMLoadFloat3(&m_right), angle);

		XMStoreFloat3(&m_up, XMVector3TransformNormal(XMLoadFloat3(&m_up), R));
		XMStoreFloat3(&m_look, XMVector3TransformNormal(XMLoadFloat3(&m_look), R));
	}

	void Camera::RotateY(float angle)
	{
		// Rotate up and look vector about the world y-axis

		XMMATRIX R = XMMatrixRotationY(angle);

		XMStoreFloat3(&m_right, XMVector3TransformNormal(XMLoadFloat3(&m_right), R));

		XMStoreFloat3(&m_up, XMVector3TransformNormal(XMLoadFloat3(&m_up), R));
		XMStoreFloat3(&m_look, XMVector3TransformNormal(XMLoadFloat3(&m_look), R));
	}


	XMMATRIX Camera::GetView() const
	{
		return m_viewMatrix;
	}

	XMMATRIX Camera::GetProj() const
	{
		return m_projMatrix;
	}


	void Camera::LookAt(XMVECTOR pos, XMVECTOR target, XMVECTOR worldUp)
	{
		m_viewMatrix = XMMatrixLookAtLH(pos, target, worldUp);
	}

	// Updating the view matrix
	void Camera::UpdateViewMatrix()
	{
		XMVECTOR R = XMLoadFloat3(&m_right);
		XMVECTOR U = XMLoadFloat3(&m_up);
		XMVECTOR L = XMLoadFloat3(&m_look);
		XMVECTOR P = XMLoadFloat3(&m_pos);

		// Orthonormalizing right, up and look vectors

		// Making vector unit length
		L = XMVector3Normalize(L);

		// Compute a new corrected "up" vector and normalize it
		U = XMVector3Normalize(U);

		// Compute a new corrected "right" vector and normalize
		// U & L are already ortho-nomal, so no need to normalize cross product
		// ||U x L|| = ||U|| ||L|| sin90 = 1
		R = XMVector3Cross(U, L);

		// View matrix entries
		float x = -XMVectorGetX(XMVector3Dot(P, R));
		float y = -XMVectorGetX(XMVector3Dot(P, U));
		float z = -XMVectorGetX(XMVector3Dot(P, L));

		XMStoreFloat3(&m_right, R);
		XMStoreFloat3(&m_up, U);
		XMStoreFloat3(&m_look, L);

		m_viewMatrix(0, 0) = m_right.x;
		m_viewMatrix(1, 0) = m_right.y;
		m_viewMatrix(2, 0) = m_right.z;
		m_viewMatrix(3, 0) = x;

		m_viewMatrix(0, 1) = m_up.x;
		m_viewMatrix(1, 1) = m_up.y;
		m_viewMatrix(2, 1) = m_up.z;
		m_viewMatrix(3, 1) = y;

		m_viewMatrix(0, 2) = m_look.x;
		m_viewMatrix(1, 2) = m_look.y;
		m_viewMatrix(2, 2) = m_look.z;
		m_viewMatrix(3, 2) = z;

		m_viewMatrix(0, 3) = 0.0f;
		m_viewMatrix(1, 3) = 0.0f;
		m_viewMatrix(2, 3) = 0.0f;
		m_viewMatrix(3, 3) = 1.0f;
	}
}