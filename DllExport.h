#pragma once
#if defined(INI_VALIDATOR_IMP)
#define INI_VALIDATOR_EXPORT __declspec(dllexport)
#else
#define INI_VALIDATOR_EXPORT __declspec(dllimport)
#endif

#pragma warning(disable: 4251)

#include <memory>
#include <string>

class IniFile;

class INI_VALIDATOR_EXPORT Validator {
public:
	static Validator& Instance();

	void LoadBootSetting(const std::string& path);
	void ReloadConfigRule(const std::string& path);
	bool Validate(const std::string& targetFilePath);

private:
	Validator() = default;
	~Validator() = default;

	std::unique_ptr<IniFile> configIni;
};