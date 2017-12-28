#include <windows.h>
#include <tchar.h>
#include <stdio.h>
#include <psapi.h>
#include <iostream>
#include <fstream>

using namespace std;

TCHAR szModNames[1024][MAX_PATH];
int current_index_modules = 0;

int CollectModuleNames( DWORD processID )
{
    HMODULE hMods[1024];
    HANDLE hProcess;
    DWORD cbNeeded;
    unsigned int i;

    hProcess = OpenProcess( PROCESS_QUERY_INFORMATION |
                            PROCESS_VM_READ,
                            FALSE, processID );
    if (NULL == hProcess)
        return 1;

    if( EnumProcessModules(hProcess, hMods, sizeof(hMods), &cbNeeded))
    {
        for ( i = 0; i < (cbNeeded / sizeof(HMODULE)); i++ )
        {
            TCHAR szModName[MAX_PATH];

            if ( GetModuleFileNameEx( hProcess, hMods[i], szModName, sizeof(szModName) / sizeof(TCHAR)))
            {
								bool wasThisModule = false;
								for (int j = 0; j < current_index_modules; j++){
									if (strcmp(szModNames[j], szModName) == 0){
										wasThisModule = true;
										break;
									}
								}
								if (!wasThisModule){
									GetModuleFileNameEx( hProcess, hMods[i], szModNames[current_index_modules], sizeof(szModNames[current_index_modules]) / sizeof(TCHAR));
									current_index_modules++;
								}
            }
        }
    }

    CloseHandle( hProcess );

    return 0;
}

int PrintProcessesForModule( DWORD processID, int module_index )
{
    HMODULE hMods[1024];
    HANDLE hProcess;
    DWORD cbNeeded;
    unsigned int i;

		hProcess = OpenProcess( PROCESS_QUERY_INFORMATION |
                            PROCESS_VM_READ,
                            FALSE, processID );

		if( EnumProcessModules(hProcess, hMods, sizeof(hMods), &cbNeeded))
    {
    	for ( i = 0; i < (cbNeeded / sizeof(HMODULE)); i++ )
      {
      	TCHAR szModName[MAX_PATH];
				TCHAR szProcessName[MAX_PATH];
        if ( GetModuleFileNameEx( hProcess, hMods[i], szModName, sizeof(szModName) / sizeof(TCHAR)))
        {
					if (strcmp(szModNames[module_index], szModName) == 0){
						if (GetModuleFileNameEx(hProcess, 0, szProcessName, MAX_PATH)){
							_tprintf( TEXT("\t%s\n"),szProcessName);
							return 0;
						}
					}
      	}
      }
		}
    return 0;
}

int main( void )
{
		freopen( "file.txt", "w", stdout );

    DWORD aProcesses[1024];
    DWORD cbNeeded;
    DWORD cProcesses;
    unsigned int i;


    if ( !EnumProcesses( aProcesses, sizeof(aProcesses), &cbNeeded ) )
        return 1;

    cProcesses = cbNeeded / sizeof(DWORD);

    for ( i = 0; i < cProcesses; i++ )
    {
        CollectModuleNames( aProcesses[i] );
    }

		std::cout << "Found " << current_index_modules << " loaded modules" << endl;

		for ( i = 0; i < current_index_modules; i++){
			_tprintf( TEXT("Module %s is used by\n"),szModNames[i]);
			for (int j = 0; j < cProcesses; j++ )
			{
					PrintProcessesForModule(aProcesses[j], i);
			}
		}

    return 0;
}
