#pragma once
#include <wtypes.h>
#include"Block.h"
#include <vector>

//定义按下的方向键
#define NON_BUTTON 0
#define LEFT 1
#define RIGHT 2
#define UP 3
#define DOWN 4

class Frame
{
public:
	/*
	* @brief 游戏初始化时构造，主函数中调用一次
	* @param map_width: 横向可容纳方块的数量，map_height:纵向可容纳方块的数量
	*/
	Frame(int map_width, int map_height);

	/*
	* @brief 游戏结束后调用，主函数中析构
	*/
	~Frame();

	/*
	* @brief 开始游戏
	*/
	void begin();

	/*
	* @brief 获得下一个方块组合，
	*/
	void get_next_block_group();

	/*
	* @brief 获得玩家操作信息
	* @param message 用于存储信息的结构体
	*/
	void get_message(ExMessage& message);

	/*
	* @brief 检查是否可以消除
	*/
	void check_line();

public:
	int menu_width;
	int menu_height;
	int frame_width;
	int frame_height;
	int map_width;
	int map_height;
	ExMessage message;
	std::vector<std::vector<Block*>> block;

private:
	IMAGE background;
	IMAGE block_group[7];
	enum blcok_group
	{
		S, Z, L, J, I, O, T//方块组合，待定，仍可添加，顺序和加载方块图片的顺序一致
	};
	int button_down;
private:

	/*
	* @brief 绘制地图背景
	*/
	void draw_backgroud();

	/*
	* @brief 初始化方块，即生成方块对象
	*/
	void initial_block();
	void load_image();
};
