#include "Log.h"
#include <iostream>
#include <Config.h>

void Log::PrintLog(string class_name, string function_name, string log) {
#if not Release	
	cout << "[Flow LOG] " + class_name + "::" + function_name + "(...)" + " - " + log << endl;
#endif
}
