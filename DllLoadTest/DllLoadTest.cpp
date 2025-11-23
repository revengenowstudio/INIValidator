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

	Validator::ValidationResults results;
	auto const successful = validator.Validate("Test.ini", results);
	cout << endl << "successful: " << successful << endl;

	for (auto const& err : results[Validator::ErrorSeverity.ToInteger()].details) {
		cout << err << endl;
	}
	for (auto idx = 0u; idx < ValidationSeverity::Error; ++idx) {
		auto const& report = results[idx];
		cout << "---" << report.severity << "---" << endl;
		for (auto const& msg : report.details) {
			cout << msg << endl;
		}
	}
}
