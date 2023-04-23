#pragma once
#include <vector>
#include "Branch.h"

// Flow Main Class
class Flow {
private:
	std::vector<Branch> branches;

public:
	Flow();
	~Flow();

	int Add();
};

