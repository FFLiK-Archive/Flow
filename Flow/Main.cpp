#include <iostream>
#include <string>
#include "Flow.h"
using namespace std;

int main(int argc, char *argv[]) {
	Flow flow;

	flow.CreateFlow(FLOW_FOLDER_STORAGE);

	//flow.LoadFlow();

	BranchID id = flow.GetBranchIDList()[0];

	for (int i = 0; i < 50; i++) {
		flow[id]->Commit("Test" + to_string(i), "This is the Test Commit!");
	}

	flow[id]->SaveBranch();
	return 0;
}