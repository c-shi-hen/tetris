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

	/*
	* @brief 程序开始时，仅初始化一次
	* @param animation : 图片资源指针
	*/
	Begin_frame(Animation* animation);
	~Begin_frame();

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

	//游戏速度
	int gameSpeed;
	//随机种子
	int randomSeed;
	//游戏难度
	int initialLevel;
	// 存储配置项的键值对
	std::unordered_map<std::string, std::string> configMap;

	//消息结构体
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

public:

	/*
	* @brief 初始化游戏主界面
	*/
	void initial();

	/*
	* @brief 默认参数
	*/
	void default_param();

	/*
	* @brief 绘制地图背景
	*/
	void inline draw_backgroud();

	/*
	* @brief 绘制菜单
	*/
	void inline draw_menu();

	/*
	* @brief 获取消息
	*/
	bool getMainMenuMessage(MainMenuMessage& msg);

	/*
	* @brief 加载指定配置文件
	*/
	bool loadConfig(const std::string& filename);

	/*
	* @brief 保存当前配置到指定文件
	*/
	bool saveConfig(const std::string& filename) const;

	/*
	* @brief 用户交互：新建配置文件
	*/
	bool createConfig(std::string &name);

	/*
	* @brief 加载上次使用的配置文件
	*/
	bool loadLastConfig();

	/*
	* @brief 保存当前配置为上次使用的配置
	*/
	bool saveLastConfig() const;

	/*
	* @brief 获取某个配置项的值
	*/
	std::optional<std::string> getConfig(const std::string& key) const;

	/*
	* @brief 设置某个配置项的值
	*/
	void setConfig(const std::string& key, const std::string& value);

	/*
	* @brief 重置为默认配置
	*/
	void resetToDefault();

	/*
	* @brief 验证整个配置是否合法
	*/
	bool isValid() const;

	/*
	* @brief 验证单个键值对是否合法
	*/
	bool validateKeyValue(const std::string& key, const std::string& value) const;

	/*
	* @brief 初始化默认配置
	*/
	void initializeDefaults();

	/*
	* @brief 公共方法，用于测试键值对是否合法
	*/
	bool testValidateKeyValue(const std::string& key, const std::string& value) const;

	/*
	* @brief 判断文件是否存在
	*/
	bool fileExists(const std::string& filename);

	/*
	* @brief 确认目录存在，如果不存在则创建
	*/
	bool createDirectoryIfNotExists(const std::string& path);
	
};

