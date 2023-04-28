#include "Branch.h"
#include "FileIO.h"
#include <chrono>
#include "Log.h"
using namespace std;

Branch::Branch() {
	this->id = NULL_ID;
	this->file_path = "";
	this->last_commit_time = 0;
	this->name = "";
}

Branch::~Branch() {
}

int Branch::CreateBranch(std::string branch_path) {
	if (this->id == NULL_ID) {
		Log::Debug("Branch", "CreateBranch", "Branch has already assigned");
		return 1;
	}

	UUIDv4::UUIDGenerator<std::mt19937_64> uuidGenerator;
	this->id = uuidGenerator.getUUID();
	this->file_path = branch_path + this->id.str() + ".branch";
	this->last_commit_time = chrono::system_clock::to_time_t(chrono::system_clock::now());
	this->name = "Main";

	Json::Value branch;
	branch["BranchID"] = this->id.str();
	branch["LastCommitTime"] = this->last_commit_time;
	branch["Name"] = this->name;
	branch["Origin"];

	this->history.CreateHistory(branch_path + this->id.str() + ".history");

	FileIO::SaveFile(this->file_path, branch);
	return 0;
}

int Branch::LoadBranch(std::string path) {
	if (this->id == NULL_ID) {
		Log::Debug("Branch", "LoadBranch", "Branch has already assigned");
		return 1;
	}
	this->file_path = path + ".branch";
	Json::Value flow = FileIO::GetJsonFile(this->file_path);
	this->id.bytes((char*)flow["BranchID"].asString().c_str());
	this->name = flow["Name"].asString();
	this->last_commit_time = flow["LastCommitTime"].asLargestUInt();
	this->history.LoadHistory(path + ".history");
	return 0;
}

int Branch::SaveBranch() {
	return 0;
}

const BranchID Branch::GetBranchID() const {
	return this->id;
}

int Branch::ChangeName(std::string name) {
	this->name = name;
	return 0;
}
