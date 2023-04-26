#pragma once
#include <vector>
#include <string>
#include "History.h"
using BranchID = unsigned int;

// Branch Management Class
class Branch {
private:
	BranchID id; // Unique id of branch (Main Branch : Always 0)

	std::vector<BranchID> parent_brach_id;
	std::vector<BranchID> child_branch_id;
	History history;

	std::string file_path; // Absolute file path of the branch file (path//[NAME].flow)

public:
	Branch();
	~Branch();

	int LoadBranch(std::string path); // Open Branch File
	int SaveBranch(); // Save Branch File

	const int GetBranchID() const;
};