#include "Log.h"
#include <Windows.h>

void Log::Error(std::wstring message) {
#if DEBUG_BUILD
	std::cout << "[Error] ";
	std::wcout << message << std::endl;
#endif
	while (message.size() < 60) {
		message += L" ";
	}
	if (message.find(L"Fatal") != std::string::npos) {
		MessageBox(NULL, message.c_str(), L"Flow", MB_OK | MB_ICONERROR | MB_SYSTEMMODAL);
		exit(-1);
	}
	else {
		std::cout << "\a";
		MessageBox(NULL, message.c_str(), L"Flow", MB_OK | MB_SYSTEMMODAL);
	}
}
