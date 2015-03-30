#include "GameObject.h"


namespace DXEngine
{
	GameObject::GameObject()
	{
		static int id = 0;
		m_id = id;
		id++;
	}
}