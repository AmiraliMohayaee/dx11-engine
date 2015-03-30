#include "Game.h"
#include "Graphics.h"
#include "GameState.h"
#include "EventPoller.h"
#include "GameObject.h"
#include <assert.h>
#include "Timer.h"


namespace DXEngine
{
	Game::Game()
	{
		m_state = 0;
	}

	void Game::Run()
	{
		while(true)
		{
			Update();
			TheGraphics::Instance() -> ClearBackBuffer();
			Draw();
			TheGraphics::Instance() -> FlipBuffer();
		}
	}


	void Game::Draw()
	{
		m_state->Draw();
	}

	void Game::Update()
	{
		TheTimer::Instance() -> Update();

		TheEventPoller::Instance() -> Update();

		m_state->Update();

		//UpdateCollision();
	}

	void Game::SetGameState(GameState* gs)
	{
		if(m_state)
		{
			m_state->OnDeActivated();
			TheEventPoller::Instance()->RemoveHandler(m_state);
		}

		m_state = gs;

		m_state->OnActivated();
		TheEventPoller::Instance()->AddHandler(m_state);
	}

	void Game::AddGameObject(GameObject* go)
	{
		m_gameObjects[go->GetId()] = go;	
	}

	void Game::DrawGameObjects()
	{
		for(GameObjects::iterator it = m_gameObjects.begin();
			it != m_gameObjects.end();
			++it)
		{
			it->second->Draw();
			//(*it).second->Draw; //Another way to call the second
		}
	}

	void Game::RemoveGameObjects(GameObject* go)
	{
		for(GameObjects::iterator it = m_gameObjects.begin();
		it != m_gameObjects.end();
		++it)
		{
		delete &it->second;
		//it->second->Update();
		//(*it).second->Draw; //Alternative way of the above method
		}
	}

	void Game::UpdateGameObjects()
	{
		for(GameObjects::iterator it = m_gameObjects.begin();
			it != m_gameObjects.end();
			++it)
		{
			it->second->Update();
			//(*it).second->Draw; //Alternative way of the above method
		}
	}
}