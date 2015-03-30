#pragma once 

#include "EventHandler.h"


namespace DXEngine
{
	class GameState : public EventHandler
	{
	public:
		virtual ~GameState() = 0 {}

		virtual void Draw() = 0;
		virtual void Update() = 0;

		virtual void OnActivated();
		virtual void OnDeActivated();

	private:
		float m_elapsedTime;

	};


}