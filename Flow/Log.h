#pragma once
#include <string>
#include <iostream>
#include "Config.h"

class Log {
private:
	template<typename T, typename... Ts> static void Print(T arg, Ts... args) {
		std::cout << arg << " ";
		Log::Print(args...);
	}

	template<typename T> static void Print(T arg) {
		std::cout << arg << std::endl;
	}

public:	
	template<typename... Ts> static void Debug(std::string class_name, std::string function_name, Ts... args) {
		#if DEBUG_BUILD
		std::cout << "[Debug Log] " + class_name + "::" + function_name + "(...)" + " - ";
		Log::Print(args...);
		#endif
	}

	template<typename... Ts> static void DebugFree(Ts ...args) {
		#if DEBUG_BUILD
		std::cout << "[Debug Log] ";
		Log::Print(args...);
		#endif
	}

	template<typename... Ts> static void System(Ts ...args) {
		std::cout << "[Flow System Log] ";
		if (sizeof...(args)) Log::Print(args...);
		else std::cout << std::endl;
	}

	template<typename... Ts> static void Flow(Ts... args) {
		#if DEBUG_BUILD
		std::cout << "[Flow] ";
		#endif
		if (sizeof...(args)) Log::Print(args...);
		else std::cout << std::endl;
	}

	template<typename... Ts> static void Print(Ts... args) {
		if (sizeof...(args)) Log::Print(args...);
		else std::cout << std::endl;
	}

	static void Error(std::wstring message);
};
