#pragma once
#include <iostream>
#include "zlib/zip.h"
#include "zlib/unzip.h"
using namespace std;

namespace ZipManager {
	class PackFile
	{
	public:
		void CreateZipFromDir(string dirName, string zipFileName);
		PackFile();
		~PackFile();
	private:
		void CollectFilesInDirToZip(zipFile zf, string strPath, string parentDir);
		void AddFileToZip(zipFile zf, string fileNameInZip, string srcFile);
	};

	static bool IsFileExist(string pPath);

	class UnpackFile
	{
	public:
		UnpackFile();
		~UnpackFile();
		void CreateDirFromZip(string dirName, string zipFileName);//Unzip to folder dirName
		void CreateFileFromZip(string fName, string zipFileName);//Unzip the first file to file fName
	};
};