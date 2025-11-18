// DllLoadTest.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <DllExport.h>
#include <Windows.h>

using std::cout;
using std::endl;

int main()
{
	SetConsoleOutputCP(CP_UTF8);
	auto& validator = Validator::Instance();
	validator.LoadBootSetting("Settings.ini");
	validator.ReloadConfigRule("INICodingCheck.ini");

	Validator::ValidateResults errors, others;
	auto const successful = validator.Validate("Test.ini", errors, others);
	cout << endl << "successful: " << successful << endl;

	for (auto const& err : errors) {
		cout << err << endl;
	}
	for (auto const& msg : others) {
		cout << msg << endl;
	}
}
