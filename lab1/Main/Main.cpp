#include <iostream>
#include <Windows.h>
#include <string>
#include <tchar.h>
#include <fstream>
#include "Employee.h"
using namespace std;

LPWSTR convert_string(string& inStr) {
	const int buffer_len = MultiByteToWideChar(CP_ACP, 0, inStr.c_str(), static_cast<int>(inStr.size()), nullptr, 0);

	if (buffer_len == 0) {
		cerr << GetLastError();
		return nullptr;
	}

	const auto wide_str = new WCHAR[buffer_len + 1];

	MultiByteToWideChar(CP_ACP, 0, inStr.c_str(), static_cast<int>(inStr.size()), wide_str, buffer_len);
	
	wide_str[buffer_len] = 0;
	
	return wide_str;
}

int main() {
	
	setlocale(LC_ALL, "rus");

	string binFileName;
	string number;

	cout << "Write the name of binary file\n";
	cin >> binFileName;

	cout << "Write the number of entries in binary file\n";
	cin >> number;

	STARTUPINFO siCreator;
	PROCESS_INFORMATION piCreator;

	ZeroMemory(&siCreator, sizeof siCreator);
	siCreator.cb = sizeof siCreator;

	string argsC = binFileName + " " + number;
	LPCTSTR cmd_prog = _tcsdup(TEXT("Creator.exe"));
	wstring wstr(argsC.begin(), argsC.end());
	LPWSTR cmdArgs = convert_string(argsC);

	if (CreateProcessW(cmd_prog, cmdArgs, nullptr, nullptr, FALSE, 0, nullptr, nullptr, &siCreator, &piCreator)){
		WaitForSingleObject(piCreator.hProcess, INFINITE);
	}
	else {
		cout << "ERROR! Creator crashed!";
	}

	CloseHandle(piCreator.hThread);
	CloseHandle(piCreator.hProcess);


	string txtFileName;
	double salaryPerHour;

	cout << "Write the name of Reporter txt file\n";
	cin >> txtFileName;
	
	cout << "Write salary per hour\n";
	cin >> salaryPerHour;

	cmd_prog = _tcsdup(TEXT("Reporter.exe"));
	string argsR = binFileName + " " + txtFileName + " " + to_string(salaryPerHour);
	
	wstring wstr1(argsR.begin(), argsR.end());
	
	cmdArgs = convert_string(argsR);
	
	STARTUPINFO siReporter;
	PROCESS_INFORMATION piReporter;
	
	ZeroMemory(&siReporter, sizeof siReporter);
	siReporter.cb = sizeof siReporter;
	ZeroMemory(&piReporter, sizeof piReporter);
	
	if (CreateProcessW(cmd_prog, cmdArgs, nullptr, nullptr, false, 0, nullptr, nullptr, &siReporter, &piReporter)) {
		WaitForSingleObject(piReporter.hProcess, INFINITE);
	}
	else cout << "ERROR! Reporter crashed!";

	WaitForSingleObject(piReporter.hProcess, INFINITE);

	CloseHandle(piReporter.hThread);
	CloseHandle(piReporter.hProcess);

	return 0;
}
