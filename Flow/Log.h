#pragma once
#include <string>
using namespace std;

class Log {
public:
	static void PrintLog(string class_name, string function_name, string log = "");
};

