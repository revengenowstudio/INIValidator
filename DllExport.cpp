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
	ValidationResults& results) {
	if (!configIni)
		return false;
	IniFile targetIni;
	IniFile::FileType = "rules";
	targetIni.load(targetFilePath, true);
	Checker checker(*configIni, targetIni, false);
	checker.checkFile();

	results.resize(static_cast<int>(ValidationSeverity::__Count));
	for (auto idx = 0u; idx < ValidationSeverity::__Count; ++idx) {
		results[idx].severity = ValidationSeverity(idx);
	}

	for (const auto& log : Log::Logs) {
		auto&& msg = log.getFileMessage();
		auto const severity = static_cast<int>(log.getSeverity());
		auto& result = results[severity];
		result.details.emplace_back(std::move(msg));
	}

	return results[static_cast<int>(ValidationSeverity::Error)].details.size() == 0;
}
