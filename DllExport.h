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

// forward declaration, so following classes are not necessary to be exported
class IniFile;
class Settings;

// see Severity definition in Log.h
class ValidationSeverity {
public:
	enum _ {
		Default,
		Info,
		Warning,
		Error,
		__Count,
		__First = 0,
	};

	constexpr ValidationSeverity(const int val) :
		value(val) {}

	constexpr ValidationSeverity(const _ val = _::__First) :
		value(val) {}

	operator const char* () const {
		return ToString();
	}

	auto const ToInteger() const {
		return value;
	}

	const char* ToString() const {
		switch (_(value)) {
		case ValidationSeverity::Default:
			return "Default";
		case ValidationSeverity::Info:
			return "Info";
		case ValidationSeverity::Warning:
			return "Warning";
		case ValidationSeverity::Error:
			return "Error";
		default:
			return "Undefined";
		}
	}
private:
	int value{ Default };
};

class INI_VALIDATOR_EXPORT Validator {
public:
	using ValidationDetails = std::vector<std::string>;
	static constexpr ValidationSeverity ErrorSeverity = ValidationSeverity::Error;
	struct ValidationReport {
		ValidationSeverity severity{};
		ValidationDetails details{};
	};
	using ValidationResults = std::vector<ValidationReport>;

	static Validator& Instance();

	/**
	* @brief Load booting ini, which is designed to load when program starts once only.
	* @param path config Ini file path
	*/
	void LoadBootSetting(const std::string& path);

	/**
	* @brief Reload configurable rules for validation
	* @param path rule Ini file path
	*/
	void ReloadConfigRule(const std::string& path);

	/**
	* @brief Do instant validation and get results. Note results will not be cleared,
	*		 make it clean before calling again. Or you will get aggregated result if you want.
	* @param targetFilePath Ini file path to validate
	* @param errors Store reports, severity accordingly
	*/
	bool Validate(const std::string& targetFilePath,
		ValidationResults& results);

	Validator(const Validator&) = delete;
	auto operator=(const Validator&) = delete;

private:
	Validator() = default;
	~Validator() = default;

	std::unique_ptr<IniFile> bootSettingIni;
	std::unique_ptr<Settings> bootSettings;// hold instance memory
	std::unique_ptr<IniFile> configIni;
};