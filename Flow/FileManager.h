#pragma once
#include <SDL.h>
#include <string>
#include <json/json.h>
#define _SILENCE_EXPERIMENTAL_FILESYSTEM_DEPRECATION_WARNING

enum FileMode { RES, DAT, EDIT };

class FileManager {
public:
	//내부 주소 반환 함수
	static std::string Location(FileMode f, std::string name, std::string pos = "");
	
	//Json 파일 추출
	static Json::Value GetJsonFile(std::string location);
};