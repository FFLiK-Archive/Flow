#include "History.h"
#include "FileIO.h"
#include "UUID.h"
#include "Log.h"
#include <chrono>
using namespace std;

History::History() {
	this->id = NULL_ID;
	this->description = "";
	this->title = "";
	this->type = COMMIT;
}

History::~History() {
}

int History::CreateHistory(HistoryType type, std::string title, std::string description, unsigned long long int size) {
	if (this->id != NULL_ID) {
		Log::Debug("History", "CreateHistory", "History has already assigned");
		return 1;
	}
	UUIDv4::UUIDGenerator<std::mt19937_64> uuidGenerator;
	this->type = type;
	this->title = title;
	this->description = description;
	this->id = uuidGenerator.getUUID();
	this->time = chrono::system_clock::to_time_t(chrono::system_clock::now());
	this->size = size;
	return 0;
}

int History::LoadHistory(Json::Value data) {
	if (this->id != NULL_ID) {
		Log::Error(L"History has already assigned - Fatal");
		return 1;
	}
	this->title = data["Title"].asString();
	this->description = data["Description"].asString();
	this->time = data["Time"].asLargestUInt();
	this->type = static_cast<HistoryType>(data["Type"].asInt());
	this->id = UUIDv4::UUID::fromStrFactory(data["HistoryID"].asString().c_str());
	this->size = data["Size"].asLargestUInt();
    return 0;
}

Json::Value History::SaveHistory() {
	Json::Value data;
	data["Title"] = this->title;
	data["Description"] = this->description;
	data["Type"] = (int)this->type;
	data["HistoryID"] = this->id.str();
	data["Time"] = this->time;
	data["Size"] = this->size;
    return data;
}