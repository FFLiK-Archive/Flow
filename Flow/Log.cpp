#include "Log.h"
#include "Config.h"
#if WIN_BUILD
#include <Windows.h>
#else
#endif

void Log::Error(std::wstring message) {
#if DEBUG_BUILD
	std::cout << "[Error] ";
	std::wcout << message << std::endl;
#endif
	while (message.size() < 60) {
		message += L" ";
	}
	if (message.find(L"Fatal") != std::string::npos) {
		#if WIN_BUILD
		MessageBox(NULL, message.c_str(), L"Flow", MB_OK | MB_ICONERROR | MB_SYSTEMMODAL);
		#else
		#endif
		exit(-1);
	}
	else {
		std::cout << "\a";
		#if WIN_BUILD
		MessageBox(NULL, message.c_str(), L"Flow", MB_OK | MB_SYSTEMMODAL);
		#else
		#endif
	}
}
