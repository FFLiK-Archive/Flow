#pragma once
#include <vector>
#include <string>
#include "History.h"
#include "UUID.h"
using BranchID = UUIDv4::UUID;

using Time = time_t;

// Branch Management Class
class Branch {
private:
	History history;
	std::string file_path; // Absolute file path of the branch file (path//[NAME].flow)

	// Branch File Data
	BranchID id; // Unique id of branch
	std::string name;
	Time last_commit_time;
	
public:
	Branch();
	~Branch();

	void CreateBranch(std::string branch_path);
	
	int LoadBranch(std::string path); // Open Branch File
	int SaveBranch(); // Save Branch File

	const BranchID GetBranchID() const;

	void ChangeName(std::string name);
};