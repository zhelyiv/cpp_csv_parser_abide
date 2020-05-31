#include "stdafx.h"
#include "ABD_FileParser.h"
#include "ABD_CsvReader.h"
		 
#ifdef _DEBUG
#define new DEBUG_NEW
#endif
 
CWinApp theApp;

#include <iostream>
#include <string>
#include <algorithm>
#include <fstream>
#include <cstdio>

using namespace std;
		    
int InitializeMFC();
 	 
std::string GetExeFolder()
{
  char szExePath[MAX_PATH] = {0};
  GetModuleFileName( NULL, szExePath, sizeof(szExePath) );
  std::string sExeFilepath(szExePath);
 						    
  size_t found = sExeFilepath.find_last_of("/\\");
  return sExeFilepath.substr(0,found);  			    
}

vector<string> GetAllFiles(std::string folder, std::string ext)
{
    vector<string> names;
    string search_path = folder + "/*.*";
    WIN32_FIND_DATA fd; 
   
	HANDLE hFind = ::FindFirstFile(search_path.c_str(), &fd); 
    if(hFind != INVALID_HANDLE_VALUE) 
	{ 
        do
		{ 													   
            if(! (fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) )
			{								    
				if( ext == PathFindExtension(fd.cFileName))
					names.push_back(fd.cFileName);
            }
        }
		while(::FindNextFile(hFind, &fd)); 
        ::FindClose(hFind); 
    } 
    return names;
}
   
int main(int argc, CHAR* argv[], CHAR* envp[])
{
	if( InitializeMFC() )
		return 1;

 	auto folder =  GetExeFolder();
	auto files = GetAllFiles(folder, ".csv");
	for(size_t i = 0 ; i < files.size(); i++) 
	{
		std::string file = folder + "\\" + files[i];  
		 
		cout << "Reading file: " << file << endl; 
		cout << "Please wait.."<< endl; 

		ABD_CsvReader oCsvReader;
		if(oCsvReader.Parse(file, false))
		{				   
			cout << "...done"<< endl; 
			// prepare copy of the parsed file, generated from the parsed data
			std::string sFileMirror = folder + "\\" +  "mirror_" + files[i];  
			std::remove(sFileMirror.c_str());
				   
			std::ofstream outfile;	  
		    outfile.open(sFileMirror, std::ios_base::app);

			// generate header
			outfile << ABD_TRDPOS_HDR('H', 'I', "7LTWFZYICNSX8D621K86", oCsvReader.m_vCsvLines.size()).ToString() << endl;

			cout << "File: " << files[i] << " parsed" << endl; 
			std::for_each(oCsvReader.m_vCsvLines.begin(), oCsvReader.m_vCsvLines.end(), [&outfile](CABD_TradesPositions* item)
			{  
				// alert if some line was not parsed sucessfully
				if(!item->IsValid()) cout << "	Waring: " << item->GetError();

				// generate csv line and appent to the file
				outfile << item->SerializeToCsvLine() << endl;
			});
		
			outfile.close();	   
		}
		else
		{
			cout << "...done"<< endl; 
			cout<< "Err: " << oCsvReader.GetLastError() << " file: "<< file << endl;
		}
	}

	Sleep(5*1000);

	return 0;
}

int InitializeMFC()
{
    int nRetCode = 0;

	HMODULE hModule = ::GetModuleHandle(NULL);

	if (hModule != NULL)
	{
		// initialize MFC and print and error on failure
		if (!AfxWinInit(hModule, NULL, ::GetCommandLine(), 0))
		{
			// TODO: change error code to suit your needs
			_tprintf(_T("Fatal Error: MFC initialization failed\n"));
			nRetCode = 1;
		}
		else
		{
			// TODO: code your application's behavior here.
		}
	}
	else
	{
		// TODO: change error code to suit your needs
		_tprintf(_T("Fatal Error: GetModuleHandle failed\n"));
		nRetCode = 1;
	}

	return nRetCode;
}
