#include "ZipManager.h"
#include <fstream>
#include <string>
#include <io.h>
#include <direct.h>
#include <windows.h>


using namespace ZipManager;

//Add the file to the zip file, note that if the source file srcFile is empty, add an empty directory    
 //fileNameInZip: the file name in the zip file, including the relative path    
void PackFile::AddFileToZip(zipFile zf, string fileNameInZip, string srcFile)
{
	FILE* srcfp = NULL;

	//Initialize file information written to zip
   //zip_fileinfo zi;
	zip_fileinfo   zi = { 0 };

	zi.tmz_date.tm_sec = zi.tmz_date.tm_min = zi.tmz_date.tm_hour =
		zi.tmz_date.tm_mday = zi.tmz_date.tm_mon = zi.tmz_date.tm_year = 0;
	zi.dosDate = 0;
	zi.internal_fa = 0;
	zi.external_fa = 0;

	//If srcFile is empty, add an empty directory    
	string new_file_name = "";
	new_file_name += fileNameInZip;
	if (srcFile == "")
	{
		new_file_name += "/";
	}

	//Create a new file in the zip file    
	zipOpenNewFileInZip(zf, new_file_name.c_str(), &zi, NULL, 0, NULL, 0, NULL, Z_DEFLATED, Z_DEFAULT_COMPRESSION);


	if (srcFile != "")
	{
		//Open source file    
		fopen_s(&srcfp, srcFile.c_str(), "rb");
		if (srcfp == NULL)
		{
			printf("Cannot add file: %s !\n", srcFile);
			zipCloseFileInZip(zf); //Close the zip file  
			return;
		}

		//Read in the source file and write to the zip file    
		char buf[100 * 1024]; //buffer    
		int numBytes = 0;
		while (!feof(srcfp))
		{
			numBytes = fread(buf, 1, sizeof(buf), srcfp);
			zipWriteInFileInZip(zf, buf, numBytes);
			if (ferror(srcfp))
				break;
		}

		//Close the source file    
		fclose(srcfp);
	}

	//Close the zip file    
	zipCloseFileInZip(zf);
}


//Recursively add subdirectories to the zip file    
void PackFile::CollectFilesInDirToZip(zipFile zf, string strPath, string parentDir) {
	string allfilestr = "";

	allfilestr += strPath;
	allfilestr += "\\*.*";//find all files

	HANDLE handle;
	WIN32_FIND_DATA FileInfo;

	handle = FindFirstFile((LPCWSTR)allfilestr.c_str(), &FileInfo);

	if (handle == INVALID_HANDLE_VALUE)
		return;

	string currentPath;
	string fullPath;

	int result = 1;

	while (result) {
		if (!(strlen((char*)FileInfo.cFileName) == 1 && FileInfo.cFileName[0] == '.'|| strlen((char*)FileInfo.cFileName) == 2 && FileInfo.cFileName[0] == '.'&&FileInfo.cFileName[1] == '.')) {
			if (parentDir.length() != 0)
			{
				fullPath = parentDir;
				fullPath += "/";
				fullPath += (char*)FileInfo.cFileName;
			}
			else
				fullPath = (char*)FileInfo.cFileName;

			currentPath = strPath;
			currentPath += "//";
			currentPath += (char*)FileInfo.cFileName;
			if ((FileInfo.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) == FILE_ATTRIBUTE_DIRECTORY)// is a directory
			{
				AddFileToZip(zf, fullPath, ""); //Generate directory structure in zip file
				CollectFilesInDirToZip(zf, currentPath, fullPath);//Recursively collect subdirectory files    
				continue;
			}
			AddFileToZip(zf, fullPath, currentPath); //Add the file to the zip file
		}
		result = FindNextFile(handle, &FileInfo);
	}
}

//Compress a directory or file (dirName) into a zipFileName (.zip) file
void PackFile::CreateZipFromDir(string dirName, string zipFileName)
{
	long Handle;
	struct _finddata_t FileInfo;

	if ((Handle = _findfirst(dirName.c_str(), &FileInfo)) == -1L)//The directory does not exist
		return;

	zipFile newZipFile = zipOpen(zipFileName.c_str(), APPEND_STATUS_CREATE); //Create zip file    
	if (newZipFile == NULL)
	{
		printf("\nUnable to create zip file!");
		return;
	}



	if (FileInfo.attrib & _A_SUBDIR)// is a directory
	{
		//AddFileToZip(newZipFile, FileInfo.name, "");
		CollectFilesInDirToZip(newZipFile, dirName, "");
	}
	else// is a file
		AddFileToZip(newZipFile, FileInfo.name, dirName);

	zipClose(newZipFile, NULL); //Close the zip file    
}

PackFile::PackFile()
{

}

PackFile::~PackFile()
{

}



static bool ZipManager::IsFileExist(string pPath) {
	//return GetFileAttributesA(pPath.c_str()) != INVALID_FILE_ATTRIBUTES;
	std::ifstream ifile(pPath);
	return (bool)ifile;
}

void UnpackFile::CreateDirFromZip(string dirName, string zipFileName)
{
	bool slashFlag = true;
	unzFile unZipDir = unzOpen(zipFileName.c_str());

	if (unZipDir == NULL)
	{
		printf("Unable to decompress the zip file!");
		return;
	}

	if (!IsFileExist(dirName))
		_mkdir(dirName.c_str());

	int nResult = unzGoToFirstFile(unZipDir);
	unsigned char * buf;

	while (nResult == UNZ_OK)
	{
		char szCurrentFile[260];
		unz_file_info unZipFileInfo;
		unzGetCurrentFileInfo(unZipDir, &unZipFileInfo, szCurrentFile, sizeof(szCurrentFile), NULL, 0, NULL, 0);

		std::string filePath = std::string(szCurrentFile);
		std::string fileName;
		string fileRoot;

		int size = unZipFileInfo.uncompressed_size;
		buf = new unsigned char[size];
		if (!buf)
		{
			printf("No enough Memory!\n");
			return;
		}
		memset(buf, 0, size * sizeof(char));
		int nReadBytes;
		if (UNZ_OK == unzOpenCurrentFilePassword(unZipDir, NULL))
		{
			nReadBytes = unzReadCurrentFile(unZipDir, buf, size);
			unzCloseCurrentFile(unZipDir);
		}
		FILE * pFile;
		string filePos;
		filePos = dirName;
		if (slashFlag)
			filePos += "\\";
		else
			filePos += "/";

		filePos += filePath;

		fopen_s(&pFile, filePos.c_str(), "wb");
		if (pFile)
			fwrite(buf, nReadBytes, 1, pFile);
		else
			printf("Cannot open output file %s \n", filePos);

		fclose(pFile);
		delete buf;

		nResult = unzGoToNextFile(unZipDir);
	}
	unzClose(unZipDir);
}

void UnpackFile::CreateFileFromZip(string fName, string zipFileName)
{
	bool slashFlag = true;
	unzFile unZipDir = unzOpen(zipFileName.c_str());

	if (unZipDir == NULL)
	{
		printf("Unable to decompress the zip file!");
		return;
	}

	int nResult = unzGoToFirstFile(unZipDir);
	unsigned char * buf;

	if (nResult == UNZ_OK)
	{
		char szCurrentFile[260];
		unz_file_info unZipFileInfo;
		unzGetCurrentFileInfo(unZipDir, &unZipFileInfo, szCurrentFile, sizeof(szCurrentFile), NULL, 0, NULL, 0);

		int size = unZipFileInfo.uncompressed_size;
		buf = new unsigned char[size];
		if (!buf)
		{
			printf("No enough Memory!\n");
			return;
		}
		memset(buf, 0, size * sizeof(char));
		int nReadBytes;
		if (UNZ_OK == unzOpenCurrentFilePassword(unZipDir, NULL))
		{
			nReadBytes = unzReadCurrentFile(unZipDir, buf, size);
			unzCloseCurrentFile(unZipDir);
		}
		FILE * pFile;
		fopen_s(&pFile, fName.c_str(), "wb");
		if (pFile)
			fwrite(buf, nReadBytes, 1, pFile);
		else
			printf("Cannot open output file %s \n", fName);

		fclose(pFile);
		delete buf;
	}
	unzClose(unZipDir);
}

UnpackFile::UnpackFile()
{

}

UnpackFile::~UnpackFile()
{

}