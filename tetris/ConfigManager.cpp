#include "ConfigManager.h"
#include <iostream>
#include <regex>
#include <filesystem>
#include <fstream>
#include <ctime>

namespace fs = std::filesystem;

// 构造函数，初始化默认值
Config::Config() : gameSpeed(5), randomSeed(-1), initialLevel(1) {}

// 验证配置的合法性
bool Config::isValid() const {
    return (gameSpeed >= 1 && gameSpeed <= 10) &&
        (initialLevel >= 1);
    // randomSeed 可以是任意整数
}

// 保存配置到文件
bool Config::saveToFile(const std::string& filename) const {
    std::ofstream ofs(filename);
    if (!ofs.is_open()) return false;
    ofs << gameSpeed << "\n" << randomSeed << "\n" << initialLevel << "\n";
    ofs.close();
    return true;
}

// 从文件加载配置
bool Config::loadFromFile(const std::string& filename) {
    std::ifstream ifs(filename);
    if (!ifs.is_open()) return false;
    ifs >> gameSpeed >> randomSeed >> initialLevel;
    if (ifs.fail()) {
        ifs.close();
        return false;
    }
    ifs.close();
    return isValid();
}

// 创建目录（使用 std::filesystem）
bool createDirectoryIfNotExists(const std::string& path) {
    try {
        return fs::create_directories(path);
    }
    catch (const fs::filesystem_error& e) {
        std::cerr << "创建目录失败: " << e.what() << std::endl;
        return false;
    }
}

// 检查文件是否存在（使用 std::filesystem）
bool fileExists(const std::string& filename) {
    try {
        return fs::exists(filename);
    }
    catch (const fs::filesystem_error& e) {
        std::cerr << "检查文件存在性失败: " << e.what() << std::endl;
        return false;
    }
}

// 创建配置文件
bool createConfig() {
    std::string configName;
    std::cout << "请输入配置文件名称（仅限英文字母、数字和下划线，输入 'q' 取消）：";
    std::cin >> configName;

    if (configName == "q") {
        std::cout << "取消新建配置。" << std::endl;
        return false;
    }

    // 验证配置文件名
    std::regex validNameRegex("^[A-Za-z0-9_]+$");
    if (!std::regex_match(configName, validNameRegex)) {
        std::cout << "配置文件名称无效。只能包含英文字母、数字和下划线。" << std::endl;
        return false;
    }

    Config newConfig;
    // 输入游戏基本速度
    while (true) {
        std::cout << "请输入游戏基本速度（1-10）：";
        std::cin >> newConfig.gameSpeed;
        if (std::cin.fail() || newConfig.gameSpeed < 1 || newConfig.gameSpeed > 10) {
            std::cin.clear(); // 清除错误标志
            std::cin.ignore(10000, '\n'); // 忽略错误输入
            std::cout << "输入无效，请输入1到10的正整数。" << std::endl;
        }
        else {
            break;
        }
    }

    // 输入随机种子
    while (true) {
        std::cout << "请输入随机种子（整数，-1表示不固定随机种子）：";
        std::cin >> newConfig.randomSeed;
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            std::cout << "输入无效，请输入一个整数。" << std::endl;
        }
        else {
            break;
        }
    }

    // 输入初始关卡
    while (true) {
        std::cout << "请输入初始关卡（正整数）：";
        std::cin >> newConfig.initialLevel;
        if (std::cin.fail() || newConfig.initialLevel < 1) {
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            std::cout << "输入无效，请输入一个正整数。" << std::endl;
        }
        else {
            break;
        }
    }

    // 创建 config 目录（如果不存在）
    if (!createDirectoryIfNotExists("config")) {
        std::cout << "无法创建 'config' 目录。" << std::endl;
        return false;
    }

    // 保存配置文件
    std::string configFilePath = "config/" + configName + ".config";
    if (!newConfig.saveToFile(configFilePath)) {
        std::cout << "保存配置文件失败。" << std::endl;
        return false;
    }

    // 更新最后使用的配置
    std::string lastConfigPath = "config/last.config";
    Config lastConfig = newConfig;
    if (!lastConfig.saveToFile(lastConfigPath)) {
        std::cout << "更新最后使用的配置文件失败。" << std::endl;
    }

    std::cout << "配置文件 '" << configName << ".config' 创建成功并保存。" << std::endl;
    return true;
}

// 加载配置文件
bool loadConfig(Config& config) {
    std::string currentConfigName;
    std::cout << "请输入要加载的配置文件名称（仅限英文字母、数字和下划线，输入 'q' 取消）：";
    std::cin >> currentConfigName;

    if (currentConfigName == "q") {
        std::cout << "取消加载配置。" << std::endl;
        return false;
    }

    // 验证配置文件名
    std::regex validNameRegex("^[A-Za-z0-9_]+$");
    if (!std::regex_match(currentConfigName, validNameRegex)) {
        std::cout << "配置文件名称无效。只能包含英文字母、数字和下划线。" << std::endl;
        return false;
    }

    std::string configFilePath = "config/" + currentConfigName + ".config";
    if (!fileExists(configFilePath)) {
        std::cout << "配置文件 '" << currentConfigName << ".config' 不存在。" << std::endl;
        return false;
    }

    Config loadedConfig;
    if (!loadedConfig.loadFromFile(configFilePath)) {
        std::cout << "加载配置文件失败或配置文件内容无效。" << std::endl;
        return false;
    }

    config = loadedConfig;

    // 更新最后使用的配置
    std::string lastConfigPath = "config/last.config";
    Config lastConfig = loadedConfig;
    if (!lastConfig.saveToFile(lastConfigPath)) {
        std::cout << "更新最后使用的配置文件失败。" << std::endl;
    }

    std::cout << "配置文件 '" << currentConfigName << ".config' 加载成功并应用。" << std::endl;
    return true;
}

// 加载最后使用的配置
bool loadLastConfig(Config& config) {
    std::string lastConfigPath = "config/last.config";
    if (!fileExists(lastConfigPath)) {
        std::cout << "没有找到最后使用的配置文件，使用默认配置。" << std::endl;
        return false;
    }

    Config loadedConfig;
    if (!loadedConfig.loadFromFile(lastConfigPath)) {
        std::cout << "加载最后使用的配置文件失败或内容无效，使用默认配置。" << std::endl;
        return false;
    }

    config = loadedConfig;
    std::cout << "加载最后使用的配置文件成功。" << std::endl;
    return true;
}
