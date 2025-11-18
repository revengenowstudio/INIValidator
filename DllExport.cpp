#include "DllExport.h"
#include "IniFile.h"
#include "Log.h"
#include "Settings.h"
#include "Checker.h"

using BOOL = int;

Validator& Validator::Instance() {
	static Validator inst;
	return inst;
}

void Validator::LoadBootSetting(const std::string& path) {
	Settings::Settings(IniFile(path, true));// will set into global instance
}
void Validator::ReloadConfigRule(const std::string& path) {
	configIni = std::make_unique<IniFile>(path, true);
}

bool Validator::Validate(const std::string& targetFilePath) {
	if (!configIni) {
		return false;
	}
	IniFile targetIni(targetFilePath);
	Checker checker(*configIni, targetIni);
	checker.checkFile();
	// TODO: find a way to determine passed or not
	return true;
}
