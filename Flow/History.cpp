#include "History.h"
#include "FileIO.h"

History::History() {
}

History::~History() {
}

int History::CreateHistory(std::string path) {
	FileIO::SaveFile(path, "");
	return 0;
}

int History::LoadHistory(std::string path) {
	return 0;
}

int History::SaveHistory(std::string path) {
	return 0;
}
