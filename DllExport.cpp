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
	bootSettingIni = std::make_unique<IniFile>(path, true);// will set into global instance
	bootSettings = std::make_unique<Settings>(*bootSettingIni);
}
void Validator::ReloadConfigRule(const std::string& path) {
	configIni = std::make_unique<IniFile>(path, true);
}

bool Validator::Validate(
	const std::string& targetFilePath,
	ValidateResults& errors,
	ValidateResults& others) {
	if (!configIni)
		return false;
	IniFile targetIni;
	IniFile::FileType = "rules";
	targetIni.load(targetFilePath, true);
	Checker checker(*configIni, targetIni, false);
	checker.checkFile();

	size_t errCount = 0;
	for (const auto& log : Log::Logs) {
		auto&& msg = log.getFileMessage();
		if (log.getSeverity() == Severity::ERROR) {
			errCount++;
			errors.emplace_back(std::move(msg));
			continue;
		}
		others.emplace_back(std::move(msg));
	}

	return errCount == 0;
}
