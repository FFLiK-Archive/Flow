#include "Metadata.h"
#include "FileIO.h"
#include <filesystem>
#include "Log.h"
using namespace std;

void Metadata::Search(string path) {
	if (!filesystem::is_directory(path)) {
		auto modifyTime = filesystem::last_write_time(path); // 파일의 수정 시간
		auto systemTime = std::chrono::clock_cast<std::chrono::system_clock>(modifyTime);
		Time time = std::chrono::system_clock::to_time_t(systemTime);
		unsigned long long int filesize = filesystem::file_size(path);
		Data d;
		d.path = path;
		d.last_write_time = time;
		d.file_size = filesize;
		this->current_data.push_back(d);
		return;
	}
	filesystem::directory_iterator itr(path);
	while (itr != filesystem::end(itr)) {
		const filesystem::directory_entry& entry = *itr;
		if (entry.is_directory()) {
			this->Search(entry.path().string());
		}
		else {
			auto modifyTime = filesystem::last_write_time(entry.path()); // 파일의 수정 시간
			auto systemTime = std::chrono::clock_cast<std::chrono::system_clock>(modifyTime);
			Time time = std::chrono::system_clock::to_time_t(systemTime);
			unsigned long long int filesize = filesystem::file_size(entry.path());
			Data d;	
			d.path = entry.path().string();
			d.last_write_time = time;
			d.file_size = filesize;
			this->current_data.push_back(d);
		}
		itr++;
	}
}

Metadata::Metadata() {
}

Metadata::~Metadata() {
}

int Metadata::CreateMetadata(std::string path, std::string* target_path) {
	this->target_path = target_path;
	this->file_path = path + "\\metadata";
	Json::Value meta;
	meta["Metadata"] = Json::arrayValue;
	this->current_data.clear();
	this->Search(*(this->target_path));
	for (int i = 0; i < this->current_data.size(); i++) {
		Json::Value data;
		data["Path"] = this->current_data[i].path;
		data["Time"] = this->current_data[i].last_write_time;
		data["Size"] = this->current_data[i].file_size;
		meta["Metadata"].append(data);
	}
	Log::DebugFree(this->file_path);
	FileIO::SaveFile(this->file_path, meta);
	return 0;
}

int Metadata::LoadMetadata(std::string path, std::string* target_path) {
	this->target_path = target_path;
	this->file_path = path + "\\metadata";
	Json::Value meta = FileIO::GetJsonFile(this->file_path);
	this->current_data.clear();
	for (int i = 0; i < meta["Metadata"].size(); i++) {
		Data d;
		d.path = meta["Metadata"][i]["Path"].asString();
		d.last_write_time = meta["Metadata"][i]["Time"].asLargestUInt();
		d.file_size = meta["Metadata"][i]["Size"].asLargestUInt();
		this->current_data.push_back(d);
	}
	return 0;
}

int Metadata::SaveMetadata() {
	Json::Value meta;
	meta["Metadata"] = Json::arrayValue;
	for (int i = 0; i < this->current_data.size(); i++) {
		Json::Value data;
		data["Path"] = this->current_data[i].path;
		data["Time"] = this->current_data[i].last_write_time;
		data["Size"] = this->current_data[i].file_size;
		meta["Metadata"].append(data);
	}
	FileIO::SaveFile(this->file_path, meta);
	return 0;
}

std::vector<FileLog> Metadata::GetChange() {
	auto prev = this->current_data;
	this->current_data.clear();
	this->Search(*(this->target_path));
	vector<FileLog> log;
	for (int i = 0; i < this->current_data.size(); i++) {
		bool add = true;
		bool mod = false;
		for (int j = 0; j < prev.size(); j++) {
			if (this->current_data[i].path == prev[j].path) {
				mod = true;
				if (this->current_data[i].file_size == prev[j].file_size || this->current_data[i].last_write_time == prev[j].last_write_time) {
					add = false;
					break;
				}
			}
		}
		if (add) {
			FileLog f;
			f.path = this->current_data[i].path;
			if (mod) f.type = FileLog::MODIFIED;
			else f.type = FileLog::ADDED;
			log.push_back(f);
		}
	}
	for (int i = 0; i < prev.size(); i++) {
		bool add = true;
		for (int j = 0; j < this->current_data.size(); j++) {
			if (this->current_data[j].path == prev[i].path) {
				add = false;
			}
		}
		if (add) {
			FileLog f;
			f.path = this->current_data[i].path;
			f.type = FileLog::DELETED;
			log.push_back(f);
		}
	}
	return log;
}
