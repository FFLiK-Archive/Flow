#include "Branch.h"
#include "FileIO.h"
#include <chrono>
#include <filesystem>
#include "Log.h"
#include <CkZip.h>
using namespace std;

int Branch::Reverter(int index) {
	History his = this->history[index];
	string path = this->history_path + "\\" + his.id.str() + ".history";
	CkZip zip;
	zip.OpenZip(path.c_str());
	zip.UnzipInto(this->history_path.c_str());
	zip.CloseZip();

	string delta = FileIO::OpenFile(this->history_path + "\\delta");

	filesystem::remove(this->history_path + "\\delta");

	path = this->file_path;
	while (path.back() != '\\')
		path.pop_back();
	path += this->id.str() + ".dat";

	string data = FileIO::OpenFile(path);

	while (data.size() < delta.size()) data += '\0';
	while (data.size() > delta.size()) delta += '\0';
	for (int i = 0; i < data.size(); i++) {
		data[i] ^= delta[i];
	}
	while (data.size() > this->history[index].size) data.pop_back();

	FileIO::SaveFile(path, data);
	return 0;
}

int Branch::PrintHistory() {
	for (int i = 0; i < this->history.size(); i++) {
		Log::Flow(this->history[i].title, this->history[i].description, this->history[i].time);
	}
	return 0;
}

int Branch::Commmiter(string old, string dat, HistoryType type, string title, string description) {
	string old_bin = FileIO::OpenFile(old);
	string data_bin = FileIO::OpenFile(dat);

	int i;
	string history_bin = "";
	for (i = 0; i < data_bin.size() && i < old_bin.size(); i++) {
		history_bin += data_bin[i] ^ old_bin[i];
	}
	while (i < data_bin.size()) history_bin += data_bin[i++];
	while (i < old_bin.size()) history_bin += old_bin[i++];

	History his;
	his.CreateHistory(type, title, description, old_bin.size());
	this->last_commit_time = his.time;
	string history_save_path = this->history_path + "\\";
	FileIO::SaveFile(history_save_path + "delta", history_bin);
	Metadata metadata;
	metadata.CreateMetadata(history_save_path + his.id.str() + ".metadata", this->target_path);
	metadata.SaveMetadata();

	CkZip zip;
	zip.NewZip((history_save_path + his.id.str() + ".history").c_str());
	zip.put_OemCodePage(65001);
	zip.AppendFiles((history_save_path + "delta").c_str(), false);
	zip.WriteZipAndClose();

	filesystem::remove(old);
	filesystem::remove(history_save_path + "delta");

	this->history.push_back(his);
	return 0;
}

Branch::Branch() {
	this->id = NULL_ID;
	this->file_path = "";
	this->last_commit_time = 0;
	this->name = "";
	this->origin = NULL_ID;
}

Branch::~Branch() {
}

int Branch::CreateBranch(std::string branch_path, std::string name, BranchID &origin, std::string* target) {
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
	if (this->history.empty()) {
		this->meta.SetEmpty(this->target_path);
	}
	else {
		this->meta.LoadMetadata(this->history_path + "\\" + this->history.back().id.str() + ".metadata", this->target_path);
	}
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
	return 0;
}

BranchID Branch::GetBranchID() const {
	return this->id;
}

BranchID Branch::GetOriginBranchID() const {
    return this->origin;
}

int Branch::ChangeName(std::string name) {
	this->name = name;
	return 0;
}

std::string Branch::GetName() const {
	return this->name;
}

Time Branch::GetLastCommitTime() const {
	return this->last_commit_time;
}

bool Branch::CheckChanged() {
	if (this->id == NULL_ID) {
		Log::Debug("Branch", "CheckChanged", "Branch is empty");
		return false;
	}
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

	filesystem::rename(path + this->id.str()  + ".dat", path + this->id.str() + ".old");

	zip.NewZip((path + this->id.str() + ".dat").c_str());
	zip.put_OemCodePage(65001);
	if (filesystem::is_directory(*this->target_path)) {
		zip.AppendFiles((*(this->target_path) + "\\*").c_str(), true);
	}
	else {
		zip.AppendFiles((*(this->target_path)).c_str(), true);
	}
	zip.WriteZipAndClose();

	this->Commmiter(path + this->id.str() + ".old", path + this->id.str() + ".dat", COMMIT, title, description);
	this->meta.LoadMetadata(this->history_path + "\\" + this->history.back().id.str() + ".metadata", this->target_path);
	return 0;
}

int Branch::Revert(int n) {
	if (this->id == NULL_ID) {
		Log::Debug("Branch", "Revert", "Branch is empty");
		return 1;
	}
	if (n >= this->history.size() || n < 0) {
		Log::Debug("Branch", "Revert", "There's not enough history");
		return 1;
	}

	string path = this->file_path;
	while (path.back() != '\\')
		path.pop_back();
	filesystem::copy(path + this->id.str() + ".dat", path + this->id.str() + ".old", filesystem::copy_options::overwrite_existing);

	for (int i = 0; i < n; i++) {
		this->Reverter(this->history.size() - i - 1);
	}

	this->Commmiter(path + this->id.str() + ".old", path + this->id.str() + ".dat", REVERT, "Revert", this->history[this->history.size() - 1].title + " ~ " + this->history[this->history.size() - n - 1].title);

	if(filesystem::is_directory(*this->target_path)) {
		filesystem::remove_all(*this->target_path);

		CkZip zip;
		zip.OpenZip((path + this->id.str() + ".dat").c_str());
		zip.Unzip(this->target_path->c_str());
		zip.CloseZip();
	}
	else {
		filesystem::remove(*this->target_path);

		string save = *this->target_path;
		while (save.back() != '\\') save.pop_back();
		//path.pop_back();

		CkZip zip;
		zip.OpenZip((path + this->id.str() + ".dat").c_str());
		zip.Unzip(save.c_str());
		zip.CloseZip();
	}
	this->meta.LoadMetadata(this->history_path + "\\" + this->history.back().id.str() + ".metadata", this->target_path);
	return 0;
}

int Branch::Delete(int n) {
	if (this->id == NULL_ID) {
		Log::Debug("Branch", "Delete", "Branch is empty");
		return 1;
	}
	if (n >= this->history.size() || n < 0) {
		Log::Debug("Branch", "Delete", "There's not enough history");
		return 1;
	}

	if (this->history.size() - n > 0 && n > 0) {
		int index = this->history.size() - n;
		int prev_index = this->history.size() - 1 - n;
		
		//1. Delta Merge
		CkZip zip;
		
		string path = this->history_path + "\\" + this->history[prev_index].id.str() + ".history";
		zip.OpenZip(path.c_str());
		zip.UnzipInto(this->history_path.c_str());
		zip.CloseZip();
		string old_bin = FileIO::OpenFile(this->history_path + "\\delta");
		filesystem::remove(this->history_path + "\\delta");

		path = this->history_path + "\\" + this->history[index].id.str() + ".history";
		zip.OpenZip(path.c_str());
		zip.UnzipInto(this->history_path.c_str());
		zip.CloseZip();
		string data_bin = FileIO::OpenFile(this->history_path + "\\delta");
		filesystem::remove(this->history_path + "\\delta");
		
		int i;
		string history_bin = "";
		for (i = 0; i < data_bin.size() && i < old_bin.size(); i++) {
			history_bin += data_bin[i] ^ old_bin[i];
		}
		while (i < data_bin.size()) history_bin += data_bin[i++];
		while (i < old_bin.size()) history_bin += old_bin[i++];

		string history_save_path = this->history_path + "\\";
		FileIO::SaveFile(history_save_path + "delta", history_bin);

		zip.NewZip((history_save_path + this->history[index].id.str() + ".history").c_str());
		zip.put_OemCodePage(65001);
		zip.AppendFiles((history_save_path + "delta").c_str(), false);
		zip.WriteZipAndClose();
		filesystem::remove(history_save_path + "delta");

		//2. Size Update
		this->history[index].size = this->history[prev_index].size;
	}

	History delete_target = this->history[this->history.size() - 1 - n];
	filesystem::remove(this->history_path + "\\" + delete_target.id.str() + ".history");
	filesystem::remove(this->history_path + "\\" + delete_target.id.str() + ".metadata");
	this->history.erase(this->history.begin() + this->history.size() - 1 - n);

	if (this->history.empty()) {
		string path = this->file_path;
		while (path.back() != '\\')
			path.pop_back();
		filesystem::remove(path + this->id.str() + ".dat");
		this->meta.SetEmpty(this->target_path);
	}
	else if(n == 0) {
		this->meta.LoadMetadata(this->history_path + "\\" + this->history.back().id.str() + ".metadata", this->target_path);
	}
	return 0;
}

int Branch::Activate() {
	if (this->id == NULL_ID) {
		Log::Debug("Branch", "Activate", "Branch is empty");
		return 1;
	}

	string path = this->file_path;
	while (path.back() != '\\')
		path.pop_back();

	CkZip zip;
	
	if(filesystem::is_directory(*this->target_path)) {
		filesystem::remove_all(*this->target_path);
		if(filesystem::exists(path + this->id.str() + ".cache")) {
			zip.OpenZip((path + this->id.str() + ".cache").c_str());
			zip.Unzip(this->target_path->c_str());
			zip.CloseZip();
			filesystem::remove(path + this->id.str() + ".cache");
		}
		else {
			zip.OpenZip((path + this->id.str() + ".dat").c_str());
			zip.Unzip(this->target_path->c_str());
			zip.CloseZip();
		}
	}
	else {
		filesystem::remove(*this->target_path);

		string save = *this->target_path;
		while (save.back() != '\\') save.pop_back();
		//path.pop_back();
		if (filesystem::exists(path + this->id.str() + ".cache")) {
			zip.OpenZip((path + this->id.str() + ".cache").c_str());
			zip.Unzip(save.c_str());
			zip.CloseZip();
			filesystem::remove(path + this->id.str() + ".cache");
		}
		else {
			zip.OpenZip((path + this->id.str() + ".dat").c_str());
			zip.Unzip(save.c_str());
			zip.CloseZip();
		}
	}
	return 0;
}

int Branch::SaveCache() {
	if (this->id == NULL_ID) {
		Log::Debug("Branch", "SaveCache", "Branch is empty");
		return 1;
	}

	string path = this->file_path;
	while (path.back() != '\\')
		path.pop_back();

	CkZip zip;
	zip.NewZip((path + this->id.str() + ".cache").c_str());
	zip.put_OemCodePage(65001);
	if (filesystem::is_directory(*this->target_path)) {
		zip.AppendFiles((*(this->target_path) + "\\*").c_str(), true);
	}
	else {
		zip.AppendFiles((*(this->target_path)).c_str(), true);
	}
	zip.WriteZipAndClose();
	return 0;
}

