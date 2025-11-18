#pragma once
#if defined(INI_VALIDATOR_IMP)
#define INI_VALIDATOR_EXPORT __declspec(dllexport)
#else
#define INI_VALIDATOR_EXPORT __declspec(dllimport)
#endif

#pragma warning(disable: 4251)

#include <memory>
#include <string>
#include <vector>

class IniFile;
class Settings;

class INI_VALIDATOR_EXPORT Validator {
public:
	using ValidateResults = std::vector<std::string>;

	static Validator& Instance();

	void LoadBootSetting(const std::string& path);
	void ReloadConfigRule(const std::string& path);
	bool Validate(const std::string& targetFilePath, 
		ValidateResults& errors,
		ValidateResults& others);

	Validator(const Validator&) = delete;
	auto operator=(const Validator&) = delete;

private:
	Validator() = default;
	~Validator() = default;

	std::unique_ptr<IniFile> bootSettingIni;
	std::unique_ptr<Settings> bootSettings;// hold instance memory
	std::unique_ptr<IniFile> configIni;
};