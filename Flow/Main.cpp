#include <iostream>
#include <string>
#include "Flow.h"
using namespace std;

int main(int argc, char *argv[]) {
	Flow flow;

	//flow.CreateFlow(FLOW_FILE_STORAGE);

	flow.LoadFlow();

	BranchID id = flow.GetBranchIDList()[1];
	flow.DeleteBranch();
	//flow.ActivateBranch(id);
	//flow[id]->Commit("Branch Commit", "");
	//flow.ActivateBranch(id);
	//flow.CreateSubBranch("Sub Branch");
	
	//flow[id]->Delete();

	//flow[id]->Commit("Test", "");
	//Metadata::PrintLog(flow[id]->GetChange());
	flow.SaveFlow();
	return 0;
}