#pragma once


namespace DXEngine
{
	class EventHandler
	{
	public:
		virtual ~EventHandler() = 0 {}

		void HandleEvent();

		virtual void OnKeyboardEvent(unsigned int buttonState, unsigned int key) {}

		virtual void OnMouseMotionEvent(unsigned int x, unsigned int y) {}

		virtual void OnMouseButtonEvent(unsigned int state, unsigned int x, unsigned int y) {}
	};
}