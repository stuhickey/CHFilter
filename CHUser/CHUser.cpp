// CHUser.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <windows.h>
#include <fltuser.h>
#include <tchar.h>


// Function to enable priviliges for this process
// required so driver will load
DWORD EnablePrivilege(TCHAR* privilegeStr)
{
    HANDLE hToken; // process token
    TOKEN_PRIVILEGES tp; // token provileges
    TOKEN_PRIVILEGES oldtp; // old token privileges
    DWORD dwSize = sizeof(TOKEN_PRIVILEGES);
    LUID luid;

    if (!OpenProcessToken(GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES |
        TOKEN_QUERY, &hToken))
    {
        return GetLastError();
    }
    // if (!LookupPrivilegeValue(NULL, _T("SeLoadDriverPrivilege"), &luid))
    if (!LookupPrivilegeValue(NULL, privilegeStr, &luid))
    {
        DWORD dwRet = GetLastError();
        CloseHandle(hToken);
        return dwRet;
    }

    ZeroMemory(&tp, sizeof(tp));
    tp.PrivilegeCount = 1;
    tp.Privileges[0].Luid = luid;
    tp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;

    // Adjust Token privileges
    if (!AdjustTokenPrivileges(hToken, FALSE, &tp, sizeof(TOKEN_PRIVILEGES),
        &oldtp, &dwSize))
    {
        DWORD dwRet = GetLastError();
        CloseHandle(hToken);
        return dwRet;
    }
    CloseHandle(hToken);
    return 0;
}

int main()
{
    HANDLE port = INVALID_HANDLE_VALUE;
    HRESULT hResult = S_OK;

    std::cout << "Running ch_test application\n";

    // Application needs to request SeLoadDriverPrivilege 
    // to load the filter driver
    TCHAR priv[] = _T("SeLoadDriverPrivilege");
    EnablePrivilege(priv);

    // Attempt to load the filter
    hResult = FilterLoad(L"CHFilter2");

    if (!SUCCEEDED(hResult))
    {
        std::cout << "Loading CHFilter2 driver failed\n";
    }
    else
    {
        std::cout << "Loading CHFilter2 driver succeeded!!!\n";
    }

    //// Connect to the CHFilter port
    //hResult = FilterConnectCommunicationPort(CH_FILTER_PORT_NAME,
    //    0,
    //    NULL,
    //    0,
    //    NULL,
    //    &port);


    // Create new thread here to monitor port and do work
 
    // create a second thread to wait for user to quit
    

    // Wait until 
    if (INVALID_HANDLE_VALUE != port) {
        CloseHandle(port);
    }

    // clean up
    hResult = FilterUnload(L"CHFilter2");

    if (!SUCCEEDED(hResult))
    {
        std::cout << "unloading CHFilter2 driver failed\n";
    }
    else
    {
        std::cout << "unloading CHFilter2 driver succeeded!!!\n";
    }

    return 0;
}
