#include <iostream>
#include <string>
#include <filesystem>
#include "Flow.h"
#include "FileIO.h"
#include "Log.h"
using namespace std;

#define arg(x) (argc > x ? input[x] : "")

int main(int argc, char* argv[]) {
	vector<string> input;
	for (int i = 1; i < argc; i++) {
		input.push_back(argv[i]);
	}

	if (input.empty())
		return 0;
	
	Flow flow;
	string cmd = input.front();

	//Open Flow
	if (cmd == "create") {
		if (arg(1) == "folder") flow.CreateFlow(FLOW_FOLDER_STORAGE);
		else if (arg(1) == "file") flow.CreateFlow(FLOW_FILE_STORAGE);
	}
	else if (cmd == "open") {
		flow.LoadFlow();
	}
	else {
		FILE* f;
		string cur_flow_path = FileIO::OpenFile("flow.cur");
		if (filesystem::exists(cur_flow_path)) {
			flow.LoadWithPath(cur_flow_path);
		}
	}

	// Getter
	if (cmd == "get_branch") {
		flow.PrintBranch();
	}
	else if (cmd == "get_activated_branch") {
		Log::Flow(flow.GetActivatedBranch()->GetBranchID().str());
	}
	else if (cmd == "get_change_log") {
		Metadata::PrintLog(flow.GetActivatedBranch()->GetChange());
	}
	else if (cmd == "get_history") {
		flow.GetActivatedBranch()->PrintHistory();
	}
	else if (cmd == "check_changed") {
		Log::Flow(flow.GetActivatedBranch()->CheckChanged());
	}

	// Branch External Command
	else if (cmd == "create_sub_branch") {
		flow.CreateSubBranch(arg(1));
	}
	else if (cmd == "merge") {
		BranchID id = UUIDv4::UUID::fromStrFactory(arg(1).c_str());
		flow.Merge(id);
	}
	else if (cmd == "replace") {
		BranchID id = UUIDv4::UUID::fromStrFactory(arg(1).c_str());
		flow.Replace(id);
	}
	else if (cmd == "delete_branch") {
		flow.DeleteBranch();
	}
	else if (cmd == "activate_branch") {
		BranchID id = UUIDv4::UUID::fromStrFactory(arg(1).c_str());
		flow.ActivateBranch(id);
	}
	else if (cmd == "change_name") {
		BranchID id = UUIDv4::UUID::fromStrFactory(arg(1).c_str());
		flow.ChangeBranchName(id, arg(2));
	}

	// Branch Internal Command
	else if (cmd == "commit") {
		flow.GetActivatedBranch()->Commit(arg(1), arg(2));
	}
	else if (cmd == "revert") {
		flow.GetActivatedBranch()->Revert(stoi(arg(1)));
	}
	else if (cmd == "delete") {
		flow.GetActivatedBranch()->Delete(stoi(arg(1)));
	}

	flow.SaveFlow();
	FileIO::SaveFile("flow.cur", flow.GetFlowPath());
	return 0;
}

/*
	[Command Table]
	
	flow create file (or folder) #flow 만들기

	flow open #flow 열기

	flow create_sub_branch [name] #sub branch 만들기

	flow merge [branch id] #branch id에 해당하는 branch에 activated branch merge
	>> [path string] origin (or target or duplicate)
	>> [path string] origin (or target or duplicate)
	>> ...
	input : list of 0 or 1 or 2 (0은 넣지 않음, 1은 origin 반영, 2는 target 반영, 위 출력값 개수만큼의 element를 가지는 수열)

	flow replace [branch id] #branch id에 해당하는 branch를 activated branch로 replace

	flow delete_branch #activated branch 삭제

	flow activate_branch [branch id] #branch id에 해당하는 branch 활성화

	flow get_branch
	>> [branch id] [name] [origin branch id] [last commit time]
	>> [branch id] [name] [origin branch id] [last commit time]
	>> ...

	flow get_activated_branch
	>> [activated branch id]

	flow change_name [branch id] [new_name] #브랜치 이름 바꾸기

	flow check_changed #브랜치에 변경사항이 있는지 확인
	>> 0 or 1 (0이면 바뀌지 않음, 1이면 바뀜)

	flow get_change_log
	>> [path] added or deleted or modified
	>> [path] added or deleted or modified
	>> ...

	flow commit [title] [description] #커밋

	flow revert [n] #n번째 히스토리로 revert (0부터 시작)

	flow delete [n] #n번째 히스토리 삭제 (0부터 시작)

	flow get_history
	>> [title] [description] [commit time]
	>> [title] [description] [commit time]
	>> ...
*/