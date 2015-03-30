#pragma once

#include "Singleton.h"
#include "GameObject.h"
#include <string>
#include <map>

namespace DXEngine
{
	class GameState;

	class Game : public NonCopyable
	{
	private:
		Game();
		friend Singleton<Game>; 

	public:
		void Run();
		void Draw();
		void Update();
		void SetGameState(GameState* gs);

		void DrawGameObjects();
		void UpdateGameObjects();
		void RemoveGameObjects(GameObject* go);
		void AddGameObject(GameObject* go);


	private:
		GameState* m_state;

		GameObjects m_gameObjects;
	};

	typedef Singleton<Game> TheGame;
}
