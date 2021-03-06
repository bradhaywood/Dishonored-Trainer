#include "stdafx.h"
#include <iostream>
#include <Windows.h>

using namespace std;

int main()
{
	HWND dWin = FindWindow(0, _T("Dishonored"));
	HANDLE hProcess;
	DWORD pid;

	cout << ">> Searching for Dishonored window ";
	if (!dWin) {
		cout << "[ FAIL ]\n";
		cin.get();
		return 1;
	}

	GetWindowThreadProcessId(dWin, &pid);
	cout << "[ OK ] (" << pid << ")\n";

	cout << ">> Attempting to open process ";

	hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pid);

	if (!hProcess) {
		cout << "[ FAIL ]\n";
		cin.get();
		return 1;
	}

	cout << "[ OK ]\n";

	int ammo;
	int addammo = 100;
	int canRead, canWrite;
	int ammoAddress = 0x1239DA50;

	while (1) {
		canRead = ReadProcessMemory(hProcess, (void*)ammoAddress, (void *)&ammo, sizeof(ammo), NULL);

		if (!canRead) {
			cout << "(!) Failed to read memory address. Aborting\n";
			cin.get();
			return 1;
		}

		if (ammo < 2) {
			canWrite = WriteProcessMemory(hProcess, (void *)ammoAddress, &addammo, sizeof(addammo), NULL);
			if (!canWrite) {
				cout << "(!) Failed to write to memory. Aborting\n";
				cin.get();
				return 1;
			}

			cout << ">> Added 100 ammo\n";
		}

		Sleep(1);
	}

	CloseHandle(hProcess);
	cin.get();
	return 0;

}



