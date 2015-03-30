#include "GameState.h"
#include "EventPoller.h"


namespace DXEngine
{
	void GameState::OnActivated()
	{
		m_elapsedTime = 0;

		TheEventPoller::Instance()->AddHandler(this);
	}

	void GameState::OnDeActivated()
	{
		TheEventPoller::Instance()->RemoveHandler(this);
	}
}