#include "FileIO.h"
#include <iostream>
#include <string>
#include <fstream>
#include <cstdio>
#include "Config.h"
#include "Log.h"
#include "FileIO.h"
#include "ProtableFileDialogs.h" //For Open Files with Multiplatforms

using namespace std;

std::string FileIO::Location(std::string name, std::string pos) {
	std::string loc;
	loc = name;
	if (pos != "") {
		loc = pos + "\\" + loc;
	}
	if (true) {
		return (std::string)getenv("APPDATA") + "\\" + "Flow" + "\\" + loc;
	}
	else {
		return loc;
	}
}

Json::Value FileIO::GetJsonFile(std::string location) {
	Log::Debug("FileManager", "GetJsonFile", "Location : ", location);
	Json::Value root;
	Json::CharReaderBuilder reader;
	ifstream is(location, ifstream::binary);
	string errorMessage;
	auto bret = Json::parseFromStream(reader, is, &root, &errorMessage);

	if (bret == false) {
		cout << "Error to parse JSON file !!!" << endl;
		cout << "Details : " << errorMessage << endl;
	}

	return root;
}

std::string FileIO::OpenFlowFile() {
	auto selection = pfd::open_file("Open Flow", "", { "Flow (*.flow)", "*.flow" }, pfd::opt::force_path).result();
	if (selection.empty()) {
		Log::Debug("FileIO", "OpenFlowFile", "Connot open flow file - Not selected");
		return "";
	}
	Log::Debug("FileIO", "OpenFlowFile", "File : ", selection.front());
	return selection.front();
}

std::string FileIO::OpenFileName() {
	auto selection = pfd::open_file("Open File", "", { "All Files", "*" }, pfd::opt::force_path).result();
	if (selection.empty()) {
		Log::Debug("FileIO", "OpenFileName", "Connot open file - Not selected");
		return "";
	}
	Log::Debug("FileIO", "OpenFileName", "File : ", selection.front());
	return selection.front();
}

static int CALLBACK BrowseFolderCallback(
	HWND hwnd, UINT uMsg, LPARAM lParam, LPARAM lpData)
{
	if (uMsg == BFFM_INITIALIZED) {
		LPCTSTR path = reinterpret_cast<LPCTSTR>(lpData);
		::SendMessage(hwnd, BFFM_SETSELECTION, true, (LPARAM)path);
	}
	return 0;
}

std::string FileIO::OpenFolderName() {
	#if WIN_BUILD
	BROWSEINFO   bi;
	LPITEMIDLIST  idl;
	TCHAR szPathname[MAX_PATH] = { 0, };
	ZeroMemory(&bi, sizeof(BROWSEINFO));
	bi.hwndOwner = NULL;
	bi.pszDisplayName = szPathname;
	bi.ulFlags = BIF_EDITBOX | BIF_NEWDIALOGSTYLE | BIF_USENEWUI;
	bi.lParam = reinterpret_cast<LPARAM>("");
	bi.lpfn = BrowseFolderCallback;
	idl = SHBrowseForFolder(&bi);
	if (idl) {
		SHGetPathFromIDList(idl, szPathname);
	}
	wstring conv(szPathname);

	string ret(conv.begin(), conv.end());
	if (ret.empty()) {
		Log::Debug("FileIO", "OpenFileName", "Connot open file - Not selected");
		return "";
	}
	Log::Debug("FileIO", "OpenFileName", "File : ", ret);
	return ret;
	#elif MAC_BUILD
	//Do Something
	Log::Debug("FileIO", "OpenFileName", "You should define this function for MAC BUILD");
	return "";
	#endif
	return "";
}

int FileIO::SaveFile(std::string path, std::string value) {
	std::ofstream fout;
	fout.open(path, std::ios::out | std::ios::binary);
	if (fout.is_open()) {
		fout.write(value.c_str(), value.size());
		fout.close();
	}
	return 0;
}

int FileIO::SaveFile(std::string path, Json::Value &value) {
	Json::StreamWriterBuilder builder;
	std::unique_ptr<Json::StreamWriter> writer(builder.newStreamWriter());
	std::ofstream outputFileStream(path);
	writer->write(value, &outputFileStream);
	return 0;
}
