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
	
	// Flow File Data
	FlowID id; // Unique id of Flow project (UUID)
	std::string name; // Name of the flow
	std::string target_path;
	FlowStorageType storage_type; // Folder or File
	std::vector<BranchID> branch_id_list; // Branch ID list

public:
	Flow();
	~Flow();

	int CreateFlow(FlowStorageType type); //Create Flow File (return 0 : Succeed, 1 : Failed)

	int LoadFlow(); //Open Flow File (return 0 : Succeed, 1 : Failed)
	int SaveFlow(); //Save Flow File (return 0 : Succeed, 1 : Failed)

	Branch* operator[](BranchID& id); // Get Branch with id

	int Merge(BranchID& branch1, BranchID& branch2); // Merge branch1 and branch2
	int Replace(BranchID& branch1, BranchID& branch2); // Replace branch1 to branch2
	int Delete(BranchID& branch); // Delete brach
};