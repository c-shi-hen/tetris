#pragma once
#include<easyx.h>
#include <string>
#include <unordered_map>
#include <optional>
#include <iostream>
#include <fstream>
#include <regex>
#include <filesystem>
#include"Animation.h"

class Begin_frame
{
public:

	Begin_frame(Animation* animation);
	~Begin_frame();

	/*
	* @brief 初始化游戏主界面
	*/
	void initial();

	/*
	* @brief 默认参数
	*/
	void default_param();

	int gameSpeed;
	int randomSeed;
	int initialLevel;

public:
	//默认窗口宽度
	const int begin_frame_width = 800;
	//默认窗口高度
	const int begin_frame_height = 800;
	//地图大小
	int map_width;
	int map_height;

	//残局信息
	std::vector<std::vector<bool>> map;           // 地图状态
	std::vector<std::vector<int>> blockColors;    // 方块颜色

	//资源指针
	Animation* animation;
	IMAGE* background;

	/*
	* @brief 绘制地图背景
	*/
	void inline draw_backgroud();

public:
	struct MainMenuMessage {
		bool startGame = false;
		bool quitGame = false;
		bool createConfig = false;
		bool loadConfig = false;
		bool challengeEndGame = false;
		bool createEndGame = false;
	};
	// 主菜单消息循环
	MainMenuMessage menuMsg;
	bool getMainMenuMessage(MainMenuMessage& msg);

public:
	
	/*
	* @brief 绘制菜单
	*/
	void inline draw_menu();

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
	// 判断文件是否存在
	bool fileExists(const std::string& filename);
	// 确认目录存在，如果不存在则创建
	bool createDirectoryIfNotExists(const std::string& path);
	
};

