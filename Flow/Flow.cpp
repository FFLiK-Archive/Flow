#include "Flow.h"
#include "FileIO.h"
#include "json/json.h"
#include <filesystem>
#include <CkZip.h>
#include "Log.h"
using namespace std;

Flow::Flow() {
	this->id = NULL_ID;
	this->name = "";
	this->storage_type = FLOW_FILE_STORAGE;
	this->branch_id_list.clear();
	this->branch_table.clear();
	this->file_path = "";
	this->activated_branch_id = NULL_ID;
}

Flow::~Flow() {
}

int Flow::CreateFlow(FlowStorageType type) {
	if (this->id != NULL_ID) {
		Log::Debug("Flow", "CreateFlow", "Flow has already assigned");
		return 1;
	}
	Log::Debug("Flow", "CreateFlow");

	string origin_path;
	switch (type) {
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

	this->target_path = origin_path;
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
	BranchID null = NULL_ID;
	main_branch.CreateBranch(header_path + this->name + ".flowdata\\", "Main", null, &this->target_path);
	this->branch_id_list.push_back(main_branch.GetBranchID());
	this->branch_table[main_branch.GetBranchID()] = main_branch;
	this->activated_branch_id = main_branch.GetBranchID();

	CkZip zip;
	zip.NewZip((header_path + this->name + ".flowdata\\" + main_branch.GetBranchID().str() + ".dat").c_str());
	zip.put_OemCodePage(65001);
	zip.WriteZipAndClose();
	return 0;
}

int Flow::LoadFlow() {
	if (this->id != NULL_ID) {
		Log::Debug("Flow", "LoadFlow", "Flow has already assigned");
		return 1;
	}
	Log::Debug("Flow", "LoadFlow");
	string flow_path = FileIO::OpenFlowFile();
	if (flow_path.empty())
		return 1;
	this->file_path = flow_path;
	while (flow_path.back() != '\\')
		flow_path.pop_back();
	Json::Value flow = FileIO::GetJsonFile(this->file_path);
	this->id = UUIDv4::UUID::fromStrFactory(flow["FlowID"].asString().c_str());
	this->name = flow["Name"].asString();
	this->target_path = flow["TargetPath"].asString();
	this->storage_type = static_cast<FlowStorageType>(flow["StorageType"].asInt());
	this->activated_branch_id = UUIDv4::UUID::fromStrFactory(flow["ActivatedBranchID"].asString().c_str());
	for (int i = 0; i < flow["BranchList"].size(); i++) {
		BranchID id = UUIDv4::UUID::fromStrFactory(flow["BranchList"][i].asString().c_str());
		this->branch_id_list.push_back(id);
		Branch branch;
		branch.LoadBranch(flow_path + this->name + ".flowdata\\" + id.str(), &this->target_path);
		this->branch_table[this->branch_id_list.back()] = branch;
	}
	return 0;
}

int Flow::SaveFlow() {
	if (this->id == NULL_ID) {
		Log::Debug("Flow", "SaveFlow", "Flow is empty");
		return 1;
	}
	Log::Debug("Flow", "SaveFlow");
	Json::Value flow;
	flow["FlowID"] = this->id.str();
	flow["Name"] = this->name;
	flow["TargetPath"] = this->target_path;
	flow["StorageType"] = this->storage_type;
	flow["ActivatedBranchID"] = this->activated_branch_id.str();
	for (int i = 0; i < this->branch_id_list.size(); i++) {
		this->branch_table[this->branch_id_list[i]].SaveBranch();
		flow["BranchList"].append(this->branch_id_list[i].str());
	}
	FileIO::SaveFile(this->file_path, flow);
	return 0;
}

Branch* Flow::operator[](BranchID& id) {
	if (this->id == NULL_ID) {
		Log::Debug("Flow", "operator[]", "Flow is empty");
		return nullptr;
	}
	return &(this->branch_table[id]);
}

int Flow::CreateSubBranch(std::string name) {
	Log::Debug("Flow", "CreateSubBranch");
	Branch sub_branch;
	string header_path = this->target_path;
	while (header_path.back() != '\\') {
		header_path.pop_back();
	}
	BranchID original_id = this->GetActivatedBranch()->GetBranchID();
	this->GetActivatedBranch()->Activate();

	sub_branch.CreateBranch(header_path + this->name + ".flowdata\\", name, original_id, &this->target_path);
	this->branch_id_list.push_back(sub_branch.GetBranchID());
	this->branch_table[sub_branch.GetBranchID()] = sub_branch;

	BranchID sub_id = sub_branch.GetBranchID();
	this->ActivateBranch(sub_id);

	CkZip zip;
	zip.NewZip((header_path + this->name + ".flowdata\\" + sub_branch.GetBranchID().str() + ".dat").c_str());
	zip.put_OemCodePage(65001);
	zip.WriteZipAndClose();
	return 0;
}

int Flow::Merge(BranchID& target_branch) {
	return 0;
}

int Flow::Replace(BranchID& target_branch) {

	return 0;
}

int Flow::DeleteBranch() {
	if (this->GetActivatedBranch()->GetOriginBranchID() == NULL_ID) {
		Log::Debug("Flow", "Delete", "Main Branch cannot be deleted");
		return 1;
	}
	
	auto del_i_iter = find(this->branch_id_list.begin(), this->branch_id_list.end(), this->activated_branch_id);
	if (del_i_iter == this->branch_id_list.end()) {
		Log::Debug("Flow", "Delete", "Cannot find Activated Branch in branch_id_list -> Fatal Error");
		return 1;
	}
	this->branch_id_list.erase(del_i_iter);


	//수정필요
	BranchID branch_del_id = this->activated_branch_id;
	this->activated_branch_id = this->GetActivatedBranch()->GetOriginBranchID();
	
	this->branch_table.erase(branch_del_id);
	this->GetActivatedBranch()->Activate();

	string path = this->target_path + ".flowdata\\" + branch_del_id.str();

	filesystem::remove(path + ".branch");
	filesystem::remove_all(path + ".history");
	filesystem::remove(path + ".dat");
	return 0;
}

int Flow::ActivateBranch(BranchID& branch) {
	this->activated_branch_id = branch;
	this->GetActivatedBranch()->Activate();
	return 0;
}

Branch* Flow::GetActivatedBranch() {
	if (this->activated_branch_id == NULL_ID) {
		Log::Debug("Flow", "GetActivatedBranch", "Activated Branch does not exist");
		return nullptr;
	}
	return (*this)[this->activated_branch_id];
}

const std::vector<BranchID>& Flow::GetBranchIDList() const {
	return this->branch_id_list;
}
