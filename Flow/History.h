#pragma once
#include <string>

// History Management Class
class History {
public:
	History();
	~History();

	int CreateHistory(std::string path);

	int LoadHistory(std::string path);
	int SaveHistory(std::string path);
};

