#pragma once
#include <string>
#include <vector>
#include "json/json.h"
#include "Config.h"

class FileLog {
public:
	enum Type { ADDED, DELETED, MODIFIED };
	std::string path;
	Type type;
};

class Metadata {
private:
	std::string file_path;
	std::string *target_path;

	class Data {
	public:
		std::string path;
		Time last_write_time;
		unsigned long long int file_size;
	};
	std::vector<Data> current_data;

	void Search(std::string path);

public:
	Metadata();
	~Metadata();

	int CreateMetadata(std::string path, std::string* target_path);
	int LoadMetadata(std::string path, std::string* target_path);
	int SaveMetadata();

	int SetEmpty(std::string* target_path);

	std::vector<FileLog> GetChange();

	static void PrintLog(std::vector<FileLog> log);
};

