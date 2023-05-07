#include <iostream>
#include <string>
#include "Flow.h"
using namespace std;

int main(int argc, char *argv[]) {
	Flow flow;
	//flow.CreateFlow(FLOW_FILE_STORAGE);
	
	flow.LoadFlow();

	BranchID id = flow.GetBranchIDList()[1];
	BranchID replace_id = flow.GetBranchIDList()[3];
	flow.ActivateBranch(id);
	flow.Replace(replace_id);
	//flow.GetActivatedBranch()->Commit("Commit", "");
	//flow.CreateSubBranch("Sub Sub Sub Branch");
	//flow.GetActivatedBranch()->ChangeName("Sub Sub Branch");
	//flow.GetActivatedBranch()->Revert(1);

	flow.SaveFlow();
	return 0;
}