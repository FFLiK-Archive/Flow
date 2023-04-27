#include "Flow.h"
#include "FileIO.h"
#include "json/json.h"
#include <filesystem>
using namespace std;
#define NULL_ID ((char*)"00000000-0000-0000-0000-000000000000")

void Flow::Init() {
	this->id = UUIDv4::UUID::fromStrFactory(NULL_ID);
	this->name = "";
	this->storage_type = FLOW_FILE_STORAGE;
	this->branch_id_list.clear();
	this->branch_table.clear();
	this->file_path = "";
}

Flow::Flow() {
	this->Init();
}

Flow::~Flow() {
}

int Flow::CreateFlow(FlowStorageType type) {
	this->Init();
	string origin_path;
	switch(type) {
	case FLOW_FILE_STORAGE:
		origin_path = FileIO::OpenFileName();
		break;
	case FLOW_FOLDER_STORAGE:
		origin_path = FileIO::OpenFolderName();
		break;
	}

	if (origin_path.empty())
		return 1;

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
	string flow_path = FileIO::OpenFlowFile();
	if (flow_path.empty())
		return 1;
	this->Init();
	this->file_path = flow_path;
	while (flow_path.back() != '\\') 
		flow_path.pop_back();
	Json::Value flow = FileIO::GetJsonFile(this->file_path);
	this->id.bytes((char*)flow["FlowID"].asString().c_str());
	this->name = flow["Name"].asString();
	this->storage_type = static_cast<FlowStorageType>(flow["StorageType"].asInt());
	for (int i = 0; i < flow["BranchList"].size(); i++) {
		string id = flow["BranchList"][i].asString();
		this->branch_id_list.push_back(BranchID(id));
		Branch branch;
		branch.LoadBranch(flow_path + id + ".branch");
		this->branch_table[this->branch_id_list.back().hash()] = branch;
	}
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
