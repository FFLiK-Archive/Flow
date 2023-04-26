#pragma once
#include <map>
#include "Branch.h"

// Flow Main Class
class Flow {
private:
	std::map<BranchID, Branch> branch_table; // Branch table with key (branch_table[key] = Branch)

public:
	Flow();
	~Flow();

	Branch* operator[](BranchID id); // Get Branch with id

	int Merge(BranchID branch1, BranchID branch2); // Merge branch1 and branch2
	int Replace(BranchID branch1, BranchID branch2); // Replace branch1 to branch2
	int Delete(BranchID branch); // Delete brach
};

