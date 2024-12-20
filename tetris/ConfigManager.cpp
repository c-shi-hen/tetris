#include "ConfigManager.h"
#include <iostream>
#include <fstream>
#include <regex>
#include <filesystem>

namespace fs = std::filesystem;

//检查文件是否存在
bool fileExists(std::string& filename) {
    try {
        return fs::exists(filename);
    }
    catch (fs::filesystem_error& e) {
        std::cout << "文件不存在: " << e.what() << std::endl;
        return false;
    }
}

// 确认目录存在，如果不存在则创建
bool createDirectoryIfNotExists(std::string& path) {
    try {
        if (fs::create_directories(path)) {
            std::cout << "目录已创建: " << path << std::endl;
        }
        return true;
    }
    catch (fs::filesystem_error& e) {
        std::cout << "创建目录失败: " << e.what() << std::endl;
        return false;
    }
}

// 构造函数：初始化默认配置
ConfigManager::ConfigManager() {
    initializeDefaults();
}

// 初始化默认配置
void ConfigManager::initializeDefaults() {
    configMap["gameSpeed"] = "5";
    configMap["randomSeed"] = "-1";
    configMap["initialLevel"] = "1";
}

// 加载指定配置文件
bool ConfigManager::loadConfig(const std::string& filename) {
    try {
        if (!fileExists(filename)) {
            std::cerr << "配置文件不存在: " << filename << std::endl;
            return false;
        }

        std::ifstream infile(filename);
        if (!infile.is_open()) {
            std::cerr << "无法打开配置文件: " << filename << std::endl;
            return false;
        }

        configMap.clear();
        std::string line;
        while (std::getline(infile, line)) {
            std::regex kvRegex("^([a-zA-Z0-9_]+)=(.+)$");
            std::smatch match;
            if (std::regex_match(line, match, kvRegex)) {
                setConfig(match[1], match[2]);
            }
            else {
                std::cerr << "配置文件中存在无效行: " << line << std::endl;
            }
        }
        infile.close();

        return isValid();
    }
    catch (const std::exception& e) {
        std::cerr << "加载配置失败: " << e.what() << std::endl;
        return false;
    }
}

// 保存当前配置到指定文件
bool ConfigManager::saveConfig(const std::string& filename) const {
    try {
        std::ofstream outfile(filename);
        if (!outfile.is_open()) {
            std::cerr << "无法打开文件进行写入: " << filename << std::endl;
            return false;
        }

        for (const auto& [key, value] : configMap) {
            outfile << key << "=" << value << "\n";
        }
        outfile.close();
        return true;
    }
    catch (const std::exception& e) {
        std::cerr << "保存配置失败: " << e.what() << std::endl;
        return false;
    }
}

// 用户交互：新建配置文件
bool ConfigManager::createConfig() {
    std::string name;
    std::cout << "请输入新配置文件名称（仅限字母、数字和下划线，输入 'q' 退出）：";
    std::cin >> name;

    if (name == "q") {
        std::cout << "取消新建配置。\n";
        return false;
    }

    std::regex validName("^[A-Za-z0-9_]+$");
    if (!std::regex_match(name, validName)) {
        std::cerr << "无效的配置名称。\n";
        return false;
    }

    std::string filename = "config/" + name + ".config";
    if (!saveConfig(filename)) {
        std::cerr << "保存配置文件失败。\n";
        return false;
    }

    std::cout << "配置文件已保存为: " << filename << std::endl;
    return true;
}

// 加载上次使用的配置
bool ConfigManager::loadLastConfig() {
    return loadConfig("config/last.config");
}

// 保存当前配置为上次使用的配置
bool ConfigManager::saveLastConfig() const {
    return saveConfig("config/last.config");
}

// 获取某个配置项的值
std::optional<std::string> ConfigManager::getConfig(const std::string& key) const {
    auto it = configMap.find(key);
    if (it != configMap.end()) {
        return it->second;
    }
    return std::nullopt;
}

// 设置某个配置项的值
void ConfigManager::setConfig(const std::string& key, const std::string& value) {
    if (validateKeyValue(key, value)) {
        configMap[key] = value;
    }
    else {
        std::cerr << "无效的配置值: " << key << "=" << value << std::endl;
    }
}

// 重置为默认配置
void ConfigManager::resetToDefault() {
    initializeDefaults();
}

// 验证整个配置是否合法
bool ConfigManager::isValid() const {
    for (const auto& [key, value] : configMap) {
        if (!validateKeyValue(key, value)) {
            return false;
        }
    }
    return true;
}

// 验证单个键值对是否合法
bool ConfigManager::validateKeyValue(const std::string& key, const std::string& value) const {
    if (key == "gameSpeed") {
        int speed = std::stoi(value);
        return speed >= 1 && speed <= 10;
    }
    else if (key == "randomSeed") {
        return std::regex_match(value, std::regex("^-?\\d+$"));
    }
    else if (key == "initialLevel") {
        int level = std::stoi(value);
        return level >= 1;
    }
    return false;
}


bool ConfigManager::testValidateKeyValue(const std::string& key, const std::string& value) const {
    return validateKeyValue(key, value);
}