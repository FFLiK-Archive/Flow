#include <iostream>
#include <string>
#include "Flow.h"
using namespace std;

int main(int argc, char *argv[]) {
	Flow flow;

	//flow.CreateFlow(FLOW_FILE_STORAGE);

	flow.LoadFlow();

	flow.GetActivatedBranch()->Revert(1);

	flow.SaveFlow();
	return 0;
}