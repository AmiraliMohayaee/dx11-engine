#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include <map>


namespace DXEngine
{
	class File;
	// Setting up GO as an abstract class
	class GameObject
	{
	public:
		GameObject();
		virtual ~GameObject() {}

		int GetId() const { return m_id; }

		virtual void Draw() = 0;
		virtual void Update() = 0;
		virtual bool Load(File*)
		{
			return true;
		}

		virtual const char* GetTypeName() const = 0;

	protected:
		int m_id;
	};

	typedef std::map<int, GameObject*> GameObjects;
}

#endif