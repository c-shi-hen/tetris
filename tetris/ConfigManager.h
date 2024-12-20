#pragma once
#include <string>
#include <unordered_map>
#include <optional>

class ConfigManager {
public:
    ConfigManager();

    // 加载指定配置文件
    bool loadConfig(const std::string& filename);

    // 保存当前配置到指定文件
    bool saveConfig(const std::string& filename) const;

    // 用户交互：新建配置文件
    bool createConfig();

    // 加载上次使用的配置文件
    bool loadLastConfig();

    // 保存当前配置为上次使用的配置
    bool saveLastConfig() const;

    // 获取某个配置项的值
    std::optional<std::string> getConfig(const std::string& key) const;

    // 设置某个配置项的值
    void setConfig(const std::string& key, const std::string& value);

    // 重置为默认配置
    void resetToDefault();

    // 验证整个配置是否合法
    bool isValid() const;

    // 验证单个键值对是否合法
    bool validateKeyValue(const std::string& key, const std::string& value) const;

    // 初始化默认配置
    void initializeDefaults();

    std::unordered_map<std::string, std::string> configMap; // 存储配置项的键值对

public:
    // 公共方法，用于测试键值对是否合法
    bool testValidateKeyValue(const std::string& key, const std::string& value) const;
};

// 辅助函数声明
bool fileExists(const std::string& filename);
bool createDirectoryIfNotExists(const std::string& path);
