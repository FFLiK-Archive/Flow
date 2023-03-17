#include <FileManager.h>
#include <iostream>
#include <string>
#include <fstream>
#include <Windows.h>
#include <cstdio>
#include <Config.h>
#include <Log.h>
using namespace std;

std::string FileManager::Location(FileMode f, std::string name, std::string pos) {
	std::string loc;
	loc = name;

	if (pos != "") {
		loc = pos + "\\" + loc;
	}

	switch (f) {
	case RES:
		loc = "res\\" + loc;
		break;
	case DAT:
		loc = "dat\\" + loc;
		break;
	case EDIT:
		loc = "edit\\" + loc;
		break;
	}

	if (Release) {
		Log::PrintLog("FileManager", "Location", "loc = " + (std::string)getenv("APPDATA") + "\\ColorDrop\\" + loc);
		return (std::string)getenv("APPDATA") + "\\ColorDrop\\" + loc;
	}
	else {
		Log::PrintLog("FileManager", "Location", "loc = " + loc);
		return loc;
	}
}

Json::Value FileManager::GetJsonFile(std::string location) {
	Log::PrintLog("FileManager", "GetJsonFile", "loc = " + location);
	Json::Value root;
	Json::CharReaderBuilder reader;
	ifstream is(location, ifstream::binary);
	string errorMessage;
	auto bret = Json::parseFromStream(reader, is, &root, &errorMessage);

	if (bret == false) {
		cout << "Error to parse JSON file !!!" << endl;
	}

	return root;
}