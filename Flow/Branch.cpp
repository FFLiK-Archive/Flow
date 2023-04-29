#include "Branch.h"
#include "FileIO.h"
#include <chrono>
#include <filesystem>
#include "Log.h"
#include <CkZip.h>
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

	this->history_path = branch_path + this->id.str() + ".history";
	
	filesystem::create_directory(this->history_path);
	
	FileIO::SaveFile(this->file_path, branch);

	this->meta.CreateMetadata(this->history_path, this->target_path);
	return 0;
}

int Branch::LoadBranch(std::string path, std::string* target) {
	if (this->id != NULL_ID) {
		Log::Debug("Branch", "LoadBranch", "Branch has already assigned");
		return 1;
	}
	this->history_path = path + ".history";
	this->file_path = path + ".branch";
	Json::Value branch = FileIO::GetJsonFile(this->file_path);
	this->id = UUIDv4::UUID::fromStrFactory(branch["BranchID"].asString().c_str());
	this->name = branch["Name"].asString();
	this->last_commit_time = branch["LastCommitTime"].asLargestUInt();
	this->origin = UUIDv4::UUID::fromStrFactory(branch["Origin"].asString().c_str());
	this->target_path = target;
	Json::Value hst = branch["History"];
	for (int i = 0; i < hst.size(); i++) {
		History h;
		h.LoadHistory(hst[i]);
		this->history.push_back(h);
	}
	this->meta.LoadMetadata(this->history_path, this->target_path);
	return 0;
}

int Branch::SaveBranch() {
	if (this->id == NULL_ID) {
		Log::Debug("Branch", "SaveBranch", "Branch is empty");
		return 1;
	}
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
	this->meta.SaveMetadata();
	return 0;
}

const BranchID Branch::GetBranchID() const {
	return this->id;
}

int Branch::ChangeName(std::string name) {
	this->name = name;
	return 0;
}

bool Branch::CheckChanged() {
	if (this->id == NULL_ID) {
		Log::Debug("Branch", "CheckChanged", "Branch is empty");
		return false;
	}
	//Log::Flow(this->meta.GetChange().size());
	return !this->meta.GetChange().empty();
}

std::vector<FileLog> Branch::GetChange() {
	return this->meta.GetChange();
}

int Branch::Commit(std::string title, std::string description) {
	if (this->id == NULL_ID) {
		Log::Debug("Branch", "Commit", "Branch is empty");
		return 1;
	}
	CkZip zip;
	string path = this->file_path;
	while (path.back() != '\\')
		path.pop_back();

	filesystem::rename(path + "data.dat", path + "old.dat");

	zip.NewZip((path + "data.dat").c_str());
	zip.put_OemCodePage(65001);
	zip.AppendFiles((*(this->target_path) + "\\*").c_str(), true);
	zip.WriteZipAndClose();


	FILE* file;
	fopen_s(&file, (path + "data.dat").c_str(), "rb");
	string data_bin = "";
	while (feof(file) == 0)
		data_bin += fgetc(file);
	fclose(file);
	fopen_s(&file, (path + "old.dat").c_str(), "rb");
	string old_bin = "";
	while (feof(file) == 0)
		old_bin += fgetc(file);
	fclose(file);

	int i;
	string history_bin = "";
	for (i = 0; i < data_bin.size() && i < old_bin.size(); i++) {
		history_bin = data_bin[i] ^ old_bin[i];
	}
	while (i < data_bin.size()) history_bin += data_bin[i++];
	while (i < old_bin.size()) history_bin += old_bin[i++];

	History his;
	his.CreateHistory(COMMIT, title, description);
	this->last_commit_time = his.time;
	string history_save_path = this->history_path + "\\";
	FileIO::SaveFile(history_save_path + "delta", history_bin);
	
	zip.NewZip((history_save_path + his.id.str()).c_str());
	zip.put_OemCodePage(65001);
	zip.AppendFiles((history_save_path + "delta").c_str(), false);
	zip.WriteZipAndClose();

	filesystem::remove(path + "old.dat");
	filesystem::remove(history_save_path + "delta");

	this->history.push_back(his);
	this->SaveBranch();
	return 0;
}

