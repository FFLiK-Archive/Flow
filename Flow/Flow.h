#pragma once
#include <map>
#include <string>
#include "Branch.h"

using FlowID = unsigned long long int;

// Flow Main Class
class Flow {
private:
	std::map<BranchID, Branch> branch_table; // Branch table with key (branch_table[key] = Branch)
	std::string file_path; // Absolute file path of the flow file (path//[NAME].flow)
	
	FlowID id; // Unique id of Flow project

public:
	Flow();
	~Flow();

	int LoadFlow(std::string path); //Open Flow File
	int SaveFlow(); //Save Flow File

	Branch* operator[](BranchID id); // Get Branch with id

	int Merge(BranchID branch1, BranchID branch2); // Merge branch1 and branch2
	int Replace(BranchID branch1, BranchID branch2); // Replace branch1 to branch2
	int Delete(BranchID branch); // Delete brach
};

