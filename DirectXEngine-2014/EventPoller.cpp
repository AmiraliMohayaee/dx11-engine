#include "EventPoller.h"
#include "EventHandler.h"
#include <algorithm>
#include <Windows.h>


namespace DXEngine
{
	 LRESULT EventPoller::WndProc(HWND hwnd, UINT umessage, WPARAM wparam, LPARAM lparam)
	 {
		 // Creating the switch cases for the message loop
		PAINTSTRUCT ps;
		HDC hdc;

		switch( umessage )
		{
			case WM_PAINT:
				hdc = BeginPaint( hwnd, &ps );
				EndPaint( hwnd, &ps );
				break;

			case WM_DESTROY:
				PostQuitMessage( 0 );
				break;

			case WM_KEYDOWN:
				for (auto it = m_handlers.begin();
					it != m_handlers.end();
					it++)
					{
						(*it)->OnKeyboardEvent(wparam, lparam);
					}
				break;

			case WM_MOUSEMOVE:
				for (auto it = m_handlers.begin();
					it != m_handlers.end();
					it++)
				{
					(*it)->OnMouseMotionEvent(static_cast<unsigned int> (wparam), static_cast<unsigned int> (lparam));
				}
				break;

			// FUCK YOU WINDOWS YOU FAT PIECE OF SHIT!
			case WM_LBUTTONDOWN:
			case WM_LBUTTONUP:
			case WM_RBUTTONDOWN:
			case WM_RBUTTONUP:
			case WM_MBUTTONDOWN:
			case WM_MBUTTONUP:
				for (auto it = m_handlers.begin();
					it != m_handlers.end();
					it++)
				{
					(*it)->OnMouseButtonEvent(umessage,
						static_cast<unsigned int> (wparam),
						static_cast<unsigned int> (lparam));
				}
				break;

			case WM_QUIT:
				break;
		}

		return DefWindowProc(hwnd, umessage, wparam, lparam);
	 }

	 void EventPoller::Update()
	 {
		// Creating the message loop
		MSG msg;

		ZeroMemory(&msg, sizeof(MSG));

		if(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			// translate keystroke messages into the right format
			TranslateMessage(&msg);

			// send the message to the WindowProc function
			DispatchMessage(&msg);
		}
	 }

	 void EventPoller::AddHandler(EventHandler* eh)
	 {
		 m_handlers.push_back(eh);
	 }

	 void EventPoller::RemoveHandler(EventHandler* eh)
	 {
		 // Looking for the handler within the handlers container to remove
		 auto it = std::find(m_handlers.begin(), m_handlers.end(), eh);

		 if (it != m_handlers.end())
		 {
			 m_handlers.erase(it);
		 }
	 }
}