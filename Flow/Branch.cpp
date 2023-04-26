#include "Branch.h"
#include "FileIO.h"
#include <chrono>
using namespace std;

Branch::Branch() {
}

Branch::~Branch() {
}

void Branch::CreateBranch(std::string branch_path) {
	UUIDv4::UUIDGenerator<std::mt19937_64> uuidGenerator;
	this->id = uuidGenerator.getUUID();
	this->file_path = branch_path + this->id.str() + ".branch";
	this->last_commit_time = chrono::system_clock::to_time_t(chrono::system_clock::now());
	this->name = "Main";

	Json::Value branch;
	branch["BranchID"] = this->id.str();
	branch["LastCommitTime"] = this->last_commit_time;
	branch["Name"] = this->name;

	this->history.CreateHistory(branch_path + this->id.str() + ".history");

	FileIO::SaveFile(this->file_path, branch);
}

int Branch::LoadBranch(std::string path) {
	return 0;
}

int Branch::SaveBranch() {
	return 0;
}

const BranchID Branch::GetBranchID() const {
	return this->id;
}

void Branch::ChangeName(std::string name) {
	this->name = name;
}
