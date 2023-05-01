#pragma once
#include <vector>
#include <string>
#include "History.h"
#include "UUID.h"
#include "Metadata.h"

using BranchID = UUIDv4::UUID;

// Branch Management Class
class Branch {
private:
	std::vector<History> history;
	std::string file_path; // Absolute file path of the branch file (path//[NAME].flow)
	std::string *target_path;
	std::string history_path;
	Metadata meta;

	// Branch File Data
	BranchID id; // Unique id of branch
	std::string name;
	Time last_commit_time;
	BranchID origin;

	int Reverter(int index);
	int Commmiter(std::string old, std::string dat, HistoryType type, std::string title, std::string description);
 
public:
	Branch();
	~Branch();

	int CreateBranch(std::string branch_path, std::string name, BranchID& origin, std::string* target);
	
	int LoadBranch(std::string path, std::string* target); // Open Branch File (without Extension)
	int SaveBranch(); // Save Branch File

	const BranchID GetBranchID() const;

	int ChangeName(std::string name);

	bool CheckChanged();

	std::vector<FileLog> GetChange();
	int Commit(std::string title, std::string description);
	int Revert(int n = 0);
	int Delete(int n);
};