#pragma once
#include <string>
#include "UUID.h"
#include "Config.h"
#include "json/json.h"
#include "Metadata.h"

enum HistoryType { COMMIT, REVERT, REPLACE };

using HistoryID = UUIDv4::UUID;

// History Management Class
class History {
public:
	std::string title;
	std::string description;
	HistoryID id;
	HistoryType type;
	Time time;
	unsigned long long int size;

	History();
	~History();

	int CreateHistory(HistoryType type, std::string title, std::string description, unsigned long long int size); //Create History (return 0 : Succeed, 1 : Failed)

	int LoadHistory(Json::Value data); //Read History (return 0 : Succeed, 1 : Failed)
	Json::Value SaveHistory(); //Save History
};
