#include "StringUtility.h"


namespace DXEngine
{
	std::wstring ConvertToWideString(const std::string& string)
	{
		//wchar_t* wString = new wchar_t[string.size() + 1];
		//size_t convertedChars = 0;

		std::wstring result(string.begin(), string.end());

		return result; 
	}
}