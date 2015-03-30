#include "ReportError.h"
#ifdef _WINDOWS
#include <Windows.h>
#else
#include <iostream>
#endif 

void DXEngine::ReportError(const std::string& text)
{
#ifdef _WINDOWS
	MessageBoxA(0, text.c_str(), "Error!", MB_ICONSTOP); //using c strings (c_str)
#else
	std::cout << "ERROR: " << text << "\n";
#endif
}