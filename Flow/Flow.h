#pragma once
#include <map>
#include <string>
#include "Branch.h"
#include "UUID.h"

enum FlowStorageType { FLOW_FILE_STORAGE = 0, FLOW_FOLDER_STORAGE = 1 };

using FlowID = UUIDv4::UUID;

// Flow Main Class
class Flow {
private:
	std::map<BranchID, Branch> branch_table; // Branch table with key (branch_table[key] = Branch)
	std::string file_path; // Absolute file path of the flow file (path//[NAME].flow)
	BranchID activated_branch_id;

	// Flow File Data
	FlowID id; // Unique id of Flow project (UUID)
	std::string name; // Name of the flow
	std::string target_path;
	FlowStorageType storage_type; // Folder or File
	std::vector<BranchID> branch_id_list; // Branch ID list

	void Deleter(BranchID& id);

public:
	Flow();
	~Flow();

	// General Flow Internal Functions
	int CreateFlow(FlowStorageType type); //Create Flow File (return 0 : Succeed, 1 : Failed)

	int LoadFlow(); //Open Flow File (return 0 : Succeed, 1 : Failed)
	int SaveFlow(); //Save Flow File (return 0 : Succeed, 1 : Failed)

	int LoadWithPath(std::string flow_path);
	std::string GetFlowPath();

	Branch* operator[](BranchID& id); // Get Branch with id

	int CreateSubBranch(std::string name);
	int Merge(BranchID& target_branch); // Merge target_branch to activated_branch
	int Replace(BranchID& target_branch); // Replace target_branch to activated_branch
	int DeleteBranch(); // Delete activated_branch
	int ActivateBranch(BranchID& branch);

	Branch* GetActivatedBranch();

	const std::vector<BranchID>& GetBranchIDList() const;

	int PrintBranch();

	int ChangeBranchName(BranchID& id, std::string name);
};