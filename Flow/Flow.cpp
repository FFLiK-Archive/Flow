#include "Flow.h"
#include "FileIO.h"
#include "json/json.h"
#include <filesystem>
using namespace std;

Flow::Flow() {
}

Flow::~Flow() {
}

int Flow::CreateFlow(FlowStorageType type) {
	string origin_path;
	switch(type) {
	case FLOW_FILE_STORAGE:
		origin_path = FileIO::OpenFileName();
		break;
	case FLOW_FOLDER_STORAGE:
		origin_path = FileIO::OpenFolderName();
		break;
	}

	UUIDv4::UUIDGenerator<std::mt19937_64> uuidGenerator;
	string header_path = origin_path;

	
	this->name = "";
	while (header_path.back() != '\\') {
		this->name = header_path.back() + this->name;
		header_path.pop_back();
	}
	this->file_path = header_path + this->name + ".flow";
	this->storage_type = type;
	this->id = uuidGenerator.getUUID();
	filesystem::create_directory(header_path + this->name + ".flowdata");
	Branch main_branch;
	main_branch.CreateBranch(header_path + this->name + ".flowdata\\");
	this->branch_id_list.push_back(main_branch.GetBranchID());
	this->branch_table[main_branch.GetBranchID().hash()] = main_branch;

	Json::Value flow;
	flow["FlowID"] = this->id.str();
	flow["Name"] = this->name;
	flow["StorageType"] = this->storage_type;
	for (int i = 0; i < this->branch_id_list.size(); i++) {
		flow["BranchList"].append(this->branch_id_list[i].str());
	}
	FileIO::SaveFile(this->file_path, flow);
	return 0;
}

int Flow::LoadFlow() {
	return 0;
}

int Flow::SaveFlow() {
	return 0;
}

Branch* Flow::operator[](BranchID& id) {
	return nullptr;
}

int Flow::Merge(BranchID& branch1, BranchID& branch2) {
	return 0;
}

int Flow::Replace(BranchID& branch1, BranchID& branch2) {
	return 0;
}

int Flow::Delete(BranchID& branch) {
	return 0;
}
