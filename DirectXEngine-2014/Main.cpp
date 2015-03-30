#include <Windows.h>
#include <iostream>
#include "Graphics.h"
#include "EventHandler.h"
#include "Game.h"
#include "TestState.h"
#include "Timer.h"


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR pScmdline, int iCmdshow)
{
	// create a "Hello World" message box using MessageBox()
    //MessageBox(NULL,
    //           L"Test Program starting now!",
    //           L"Message",
			 //  MB_ICONINFORMATION | MB_OK);


	DXEngine::TheGraphics::Instance()->Initialize(720, 480, false, L"DX Engine");

	DXEngine::TheTimer::Instance()->Start();

	DXEngine::TheGame::Instance()->SetGameState(DXEngine::TheTestState::Instance());
	DXEngine::TheGame::Instance()->Run();

	return 1;
}