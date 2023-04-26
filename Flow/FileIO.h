#pragma once
#include <string>
#include <vector>
#include "json/json.h"
#include "Config.h"
#define _SILENCE_EXPERIMENTAL_FILESYSTEM_DEPRECATION_WARNING

class FileIO {
public:
	//Return Internal Path Function <- Not sure if the Mac will function normally (Maybe Not)
	static std::string Location(std::string name, std::string pos = "");
	
	//Json File Parsing
	static Json::Value GetJsonFile(std::string location);

	//Open Flow File and Get Absolute Path as string
	static std::string OpenFlowFile();

	//Open Files and Get Absolute Path as string
	static std::string OpenFileName();

	//Open Folder and Get Absolute Path as string
	static std::string OpenFolderName();

	//Save File as String (or Binary Data)
	static int SaveFile(std::string path, std::string value);

	//Save File as JSON
	static int SaveFile(std::string path, Json::Value &value);
};