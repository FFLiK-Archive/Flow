#include <iostream>
#include <string>
#include "Flow.h"
using namespace std;

int main(int argc, char *argv[]) {
	Flow flow;

	//flow.CreateFlow(FLOW_FILE_STORAGE);

	flow.LoadFlow();

	BranchID id = flow.GetBranchIDList()[0];
	
	Metadata::PrintLog(flow[id]->GetChange());
	flow[id]->Revert(1);
	Metadata::PrintLog(flow[id]->GetChange());

	//flow[id]->Commit("Test", "");

	/*
	for (int i = 0; i < 50; i++) {
		flow[id]->Commit("Test" + to_string(i), "This is the Test Commit!");
	}
	*/
	return 0;
}