#include "FileIO.h"
#include <iostream>
#include <string>
#include <fstream>
#include <cstdio>
#include "Config.h"
#include "Log.h"
#include "FileIO.h"

using namespace std;

std::string FileManager::Location(std::string name, std::string pos) {
	std::string loc;
	loc = name;
	if (pos != "") {
		loc = pos + "\\" + loc;
	}
	if (true) {
		return (std::string)getenv("APPDATA") + "\\" + "Flow" + "\\" + loc;
	}
	else {
		return loc;
	}
}

Json::Value FileManager::GetJsonFile(std::string location) {
	Log::Debug("FileManager", "GetJsonFile", "Location : ", location);
	Json::Value root;
	Json::CharReaderBuilder reader;
	ifstream is(location, ifstream::binary);
	string errorMessage;
	auto bret = Json::parseFromStream(reader, is, &root, &errorMessage);

	if (bret == false) {
		cout << "Error to parse JSON file !!!" << endl;
		cout << "Details : " << errorMessage << endl;
	}

	return root;
}

std::string FileManager::OpenFlowFile() {
	return std::string();
}

std::vector<std::string> FileManager::OpenMultipleFiles() {
	return std::vector<std::string>();
}


