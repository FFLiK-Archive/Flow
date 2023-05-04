#include <iostream>
#include <string>
#include "Flow.h"
using namespace std;

int main(int argc, char *argv[]) {
	Flow flow;
	//flow.CreateFlow(FLOW_FILE_STORAGE);
	
	flow.LoadFlow();

	BranchID id = flow.GetBranchIDList()[0];
	flow.ActivateBranch(id);
	//flow.GetActivatedBranch()->Commit("Commit", "");
	//flow.CreateSubBranch("Sub Branch");
	//flow.GetActivatedBranch()->Revert(1);

	flow.SaveFlow();
	return 0;
}