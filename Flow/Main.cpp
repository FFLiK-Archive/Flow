#include <iostream>
#include <string>
#include "Flow.h"
using namespace std;

int main(int argc, char *argv[]) {
	Flow flow;

	//flow.CreateFlow(FLOW_FILE_STORAGE);

	flow.LoadFlow();

	BranchID id = flow.GetBranchIDList()[0];
	
	flow[id]->Delete();

	//flow[id]->Commit("Test", "");
	Metadata::PrintLog(flow[id]->GetChange());
	return 0;
}