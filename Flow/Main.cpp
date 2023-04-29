#include <iostream>
#include "Flow.h"

int main(int argc, char *argv[]) {
	Flow flow;

	//flow.CreateFlow(FLOW_FOLDER_STORAGE);

	flow.LoadFlow();

	BranchID id = flow.GetBranchIDList()[0];

	while (!flow[id]->CheckChanged());

	flow[id]->SaveBranch();
	return 0;
}