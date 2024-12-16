// ConfigManager.h 实现自定义配置功能
#pragma once

#include <string>

// 定义配置结构体
struct Config {
    int gameSpeed;      // 1到10的正整数
    int randomSeed;     // 任意整数，-1表示不固定随机种子
    int initialLevel;   // 正整数

    Config(); // 构造函数

    // 验证配置的合法性
    bool isValid() const;

    // 保存配置到文件
    bool saveToFile(const std::string& filename) const;

    // 从文件加载配置
    bool loadFromFile(const std::string& filename);
};

// 配置管理函数声明
bool createConfig();
bool loadConfig(Config& config);
bool loadLastConfig(Config& config);
bool createDirectoryIfNotExists(const std::string& path);
bool fileExists(const std::string& filename);
