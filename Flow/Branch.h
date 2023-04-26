#pragma once
#include <vector>
#include <string>
#include "History.h"
using BranchID = int;

// Branch Management Class
class Branch {
private:
	BranchID id;

	std::vector<BranchID> parent_brach_id;
	std::vector<BranchID> child_branch_id;
	History history;

public:
	Branch();
	~Branch();

	int LoadBranch(std::string path); // Open Branch File
	int SaveBranch(std::string path); // Save Branch File

	const int GetBranchID() const;
};