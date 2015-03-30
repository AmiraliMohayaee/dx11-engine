#include <d3d11.h>
#include <d3dx11.h>
#include <xnamath.h>
#include "Vec3.h"


namespace DXEngine
{
	class Camera
	{
	public:
		Camera() {}
		~Camera() {}

		// Getting/Setting Camera Pos 
		XMVECTOR GetPosXM() const;
		XMFLOAT3 GetPos() const;
		void SetPos(float x, float y, float z);
		void SetPos(const XMFLOAT3& v);

		// Camera vectors
		XMVECTOR GetRightXM() const;
		XMFLOAT3 GetRight() const;
		XMVECTOR GetUpXM() const;
		XMFLOAT3 GetUp() const;
		XMVECTOR GetLookXM() const;
		XMFLOAT3 GetLook() const;

		// Camera Frustom properties
		float GetNearZ() const;
		float GetFarz() const;
		float Aspect() const;
		float GetFovY() const;
		float GetFovX() const;

		// Camera viewspace near and far plane
		float GetNearWindowWidth() const;
		float GetNearWindowHeight() const;
		float GetFarWindowWidth() const;
		float GetFarWindowHeight() const;

		//Getters for view and projection
		XMMATRIX GetView() const;
		XMMATRIX GetProj() const;

		// Set Frustum and perspective
		void SetLens(float fovY, float aspect, float zn, float zf);

		// Camera LookAt
		void LookAt(XMVECTOR pos, XMVECTOR target, XMVECTOR worldUp);
		//void LookAt(const XMFLOAT3& pos, const XMFLOAT3& target, const XMFLOAT3& up);

		// View/Proj matrix getters
		XMMATRIX View() const;
		XMMATRIX Proj() const;
		XMMATRIX ViewProj() const;

		// Strafe/Walk cameras with 'd' respresenting distance
		void Strafe(float d);
		void Walk(float d);

		// Camera rotate
		void Pitch(float angle);
		void RotateY(float angle);

		// reset vamera view matrix
		void UpdateViewMatrix();


	private:
		XMMATRIX m_viewMatrix;
		XMMATRIX m_projMatrix;
		
		// Camera coords
		XMFLOAT3 m_pos;
		XMFLOAT3 m_right;
		XMFLOAT3 m_up;
		XMFLOAT3 m_look;

		// chache frustum properties
		float m_nearZ;
		float m_farZ;
		float m_aspect;
		float m_fovY;
		float m_nearWindowHeight;
		float m_farWindowHeight;

		// cache vew/proj matrices
		//XMFLOAT4X4 m_view;
		//XMFLOAT4X4 m_proj;

		//Vec3f m_pos;
	};
}