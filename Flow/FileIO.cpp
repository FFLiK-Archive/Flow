#include "FileIO.h"
#include <iostream>
#include <string>
#include <fstream>
#include <cstdio>
#include "Config.h"
#include "Log.h"
#include "FileIO.h"
#include <filesystem>
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

Json::Value FileIO::GetJsonFile(std::string path) {
	Log::Debug("FileIO", "GetJsonFile", "Path : ", path);
	Json::Value root;
	Json::CharReaderBuilder reader;
	ifstream is(filesystem::path(filesystem::u8path(path)).string(), ifstream::binary);
	string errorMessage;
	auto bret = Json::parseFromStream(reader, is, &root, &errorMessage);

	if (bret == false) {
		Log::DebugFree("Error to parse JSON file !!!");
		Log::DebugFree("Details :", errorMessage);
		Log::Error(L"Error to parse JSON file - Fatal");
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
	for (int i = 0; i < selection.front().size(); i++) {
		if (selection.front()[i] < 0) {
			Log::Error(L"Root path should contain only ASCII characters. - Fatal");
		}
	}
	return selection.front();
}

std::string FileIO::OpenFileName() {
	auto selection = pfd::open_file("Open File", "", { "All Files", "*" }, pfd::opt::force_path).result();
	if (selection.empty()) {
		Log::Debug("FileIO", "OpenFileName", "Connot open file - Not selected");
		return "";
	}
	Log::Debug("FileIO", "OpenFileName", "File : ", selection.front());
	for (int i = 0; i < selection.front().size(); i++) {
		if (selection.front()[i] < 0) {
			Log::Error(L"Root path should contain only ASCII characters. - Fatal");
		}
	}
	return selection.front();
}

#if WIN_BUILD
static int CALLBACK BrowseFolderCallback(
HWND hwnd, UINT uMsg, LPARAM lParam, LPARAM lpData)
{
	if (uMsg == BFFM_INITIALIZED) {
		LPCTSTR path = reinterpret_cast<LPCTSTR>(lpData);
		::SendMessage(hwnd, BFFM_SETSELECTION, true, (LPARAM)path);
	}
	return 0;
}
#endif

char* ConvertTCharToChar(const TCHAR* tcharString, UINT codePage)
{
	int charCount = WideCharToMultiByte(codePage, 0, tcharString, -1, NULL, 0, NULL, NULL);
	char* charString = new char[charCount];
	WideCharToMultiByte(codePage, 0, tcharString, -1, charString, charCount, NULL, NULL);
	return charString;
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

	string ret = ConvertTCharToChar(szPathname, CP_UTF8);

	for (int i = 0; i < ret.size(); i++) {
		if (ret[i] < 0) {
			Log::Error(L"Root path should contain only ASCII characters. - Fatal");
		}
	}

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

std::string FileIO::OpenFile(std::string path) {
	FILE* file;
	fopen_s(&file, path.c_str(), "rb");
	string data_bin = "";
	while (feof(file) == 0)
		data_bin += fgetc(file);
	fclose(file);
	data_bin.pop_back();
	return data_bin;
}

int FileIO::SaveFile(std::string path, std::string value) {
	FILE* f;
	fopen_s(&f, path.c_str(), "wb");
	for (int i = 0; i < value.size(); i++) {
		fputc(value[i], f);
	}
	fclose(f);
	return 0;
}

int FileIO::SaveFile(std::string path, Json::Value &value) {
	Json::StreamWriterBuilder builder;
	builder.settings_["emitUTF8"] = true;
	std::unique_ptr<Json::StreamWriter> writer(builder.newStreamWriter());
	std::ofstream outputFileStream(filesystem::path(filesystem::u8path(path)).string());
	writer->write(value, &outputFileStream);
	return 0;
}

int FileIO::SpecializedMsgBox_SelectNotFoundFileOrFolder() {
	return MessageBox(NULL, L"Cannot find target path to store \nPlease select the new target path", L"Flow", MB_OKCANCEL | MB_SYSTEMMODAL);
}
