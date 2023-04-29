#include "Branch.h"
#include "FileIO.h"
#include <chrono>
#include <filesystem>
#include "Log.h"
using namespace std;

Branch::Branch() {
	this->id = NULL_ID;
	this->file_path = "";
	this->last_commit_time = 0;
	this->name = "";
	this->origin = NULL_ID;
}

Branch::~Branch() {
}

int Branch::CreateBranch(std::string branch_path, std::string name, BranchID& origin, std::string* target) {
	if (this->id != NULL_ID) {
		Log::Debug("Branch", "CreateBranch", "Branch has already assigned");
		return 1;
	}

	UUIDv4::UUIDGenerator<std::mt19937_64> uuidGenerator;
	this->id = uuidGenerator.getUUID();
	this->file_path = branch_path + this->id.str() + ".branch";
	this->last_commit_time = chrono::system_clock::to_time_t(chrono::system_clock::now());
	this->name = name;
	this->origin = origin;
	this->target_path = target;

	Json::Value branch;
	branch["BranchID"] = this->id.str();
	branch["LastCommitTime"] = this->last_commit_time;
	branch["Name"] = this->name;
	branch["Origin"] = this->origin.str();
	branch["History"] = Json::arrayValue;
	
	filesystem::create_directory(branch_path + this->id.str() + ".history");



	FileIO::SaveFile(this->file_path, branch);
	return 0;
}

int Branch::LoadBranch(std::string path, std::string* target) {
	if (this->id != NULL_ID) {
		Log::Debug("Branch", "LoadBranch", "Branch has already assigned");
		return 1;
	}
	this->file_path = path + ".branch";
	Json::Value branch = FileIO::GetJsonFile(this->file_path);
	this->id.bytes((char*)branch["BranchID"].asString().c_str());
	this->name = branch["Name"].asString();
	this->last_commit_time = branch["LastCommitTime"].asLargestUInt();
	this->origin.bytes((char*)branch["Origin"].asString().c_str());
	this->target_path = target;
	Json::Value hst = branch["History"];
	for (int i = 0; i < hst.size(); i++) {
		History h;
		h.LoadHistory(hst[i]);
		this->history.push_back(h);
	}
	return 0;
}

int Branch::SaveBranch() {
	Json::Value branch;
	branch["BranchID"] = this->id.str();
	branch["LastCommitTime"] = this->last_commit_time;
	branch["Name"] = this->name;
	branch["Origin"] = this->origin.str();
	branch["History"] = Json::arrayValue;
	for (int i = 0; i < this->history.size(); i++) {
		branch["History"].append(this->history[i].SaveHistory());
	}
	FileIO::SaveFile(this->file_path, branch);
	return 0;
}

const BranchID Branch::GetBranchID() const {
	return this->id;
}

int Branch::ChangeName(std::string name) {
	this->name = name;
	return 0;
}

int Branch::Commit() {

	return 0;
}
