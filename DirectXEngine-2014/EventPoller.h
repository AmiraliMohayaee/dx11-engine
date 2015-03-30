#pragma once

#include "Non-Copyable.h"
#include "Singleton.h"
#include <vector>
#include <Windows.h>


namespace DXEngine
{
	class EventHandler;

	class EventPoller : public NonCopyable
	{
	private:
		EventPoller() {}

		typedef std::vector<EventHandler*> Handlers;	// Perhaps change to List to prevent huge shifts?
		Handlers m_handlers;

	public:
		friend Singleton <EventPoller>;

		void Update();	// Message loop

		void AddHandler(EventHandler*);

		void RemoveHandler(EventHandler*);

		LRESULT WndProc(HWND hwnd, UINT umessage, WPARAM wparam, LPARAM lparam);
	};

	typedef Singleton<EventPoller> TheEventPoller;
}