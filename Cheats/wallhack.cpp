#include <windows.h>
#include <Tlhelp32.h>
#include <iostream>

DWORD GetProcId(const char* procName) {
	HANDLE hSnapshot;
	PROCESSENTRY32 pe;
	int pid = 0;
	BOOL hResult;

	hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (INVALID_HANDLE_VALUE == hSnapshot) return 0;

	pe.dwSize = sizeof(PROCESSENTRY32);

	hResult = Process32First(hSnapshot, &pe);

	while (hResult) {
	if (strcmp(procName, pe.szExeFile) == 0) {
	  pid = pe.th32ProcessID;
	  break;
	}
	hResult = Process32Next(hSnapshot, &pe);
	}

	CloseHandle(hSnapshot);
	return pid;
}

uintptr_t GetModuleBaseAddress(DWORD dwProcID, char* szModuleName) {
    uintptr_t ModuleBaseAddress = 0;
    HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, dwProcID);
    if (hSnapshot != INVALID_HANDLE_VALUE) {
        MODULEENTRY32 ModuleEntry32;
        ModuleEntry32.dwSize = sizeof(MODULEENTRY32);
        if (Module32First(hSnapshot, &ModuleEntry32)) {
            do {
                if (strcmp(ModuleEntry32.szModule, szModuleName) == 0) {
                    ModuleBaseAddress = (uintptr_t)ModuleEntry32.modBaseAddr;
                    break;
                }
            }
			while (Module32Next(hSnapshot, &ModuleEntry32));
        }
        CloseHandle(hSnapshot);
    }
    return ModuleBaseAddress;
}

int main() {
	DWORD dwProcId = GetProcId("BIL520_DonemOdevi.exe");
	HANDLE pHandle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, dwProcId);
	int enableVal = 1;
	while(1 == 1) {
		WriteProcessMemory(pHandle, (LPVOID)0xC2494E8, &enableVal, sizeof(int), NULL);
		WriteProcessMemory(pHandle, (LPVOID)0xC2ADF70, &enableVal, sizeof(int), NULL);
		WriteProcessMemory(pHandle, (LPVOID)0xC2AE868, &enableVal, sizeof(int), NULL);
	}
	CloseHandle(pHandle); 
}