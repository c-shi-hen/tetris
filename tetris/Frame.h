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
	void game_begin();

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

	/*
	* @brief 消除满足条件的行，且只下落一次
	* @param row : 行数
	*/
	void erase_line(int row);

	/*
	* @brief 检查是否出现碰撞，也即下落停止位置
	*/
	void check_crash();

	/*
	*@brief 刷新游戏界面
	*/
	void renew_frame();

	/*
	*@brief 绘制方块
	*/
	void draw_block();

	/*
	*@brief 显示得分
	*/
	void draw_score();

	/*
	*@brief 显示下一个方块组合的照片
	*/
	void draw_block_group_png();

public:

	//菜单的宽度
	int menu_width;
	//菜单的长度
	int menu_height;

	//界面的宽度
	int frame_width;
	//界面的长度
	int frame_height;

	//地图的宽度，即能容纳的方块数目
	int map_width;
	//地图的宽度，即能容纳的方块数目
	int map_height;

	//储存时间消息
	ExMessage message;

	//按下的按键
	int button_down;

	//方块矩阵
	std::vector<std::vector<Block*>> block;

	//当前下落方块组合
	std::vector<Block*> block_group;
	std::vector<Block*> next_block_group;
	
	//下一个方块组合字符表示的index
	int next_block_group_png;
	//方块组合图片显示的坐标
	int next_group_block_x_axis;
	int next_group_block_y_axis;

	//玩家得分
	int score;

	//得分坐标
	int score_x_axis;
	int score_y_axis;

	//下落速度
	int speed;

private:
	//背景照片
	IMAGE background;
	//方块组合照片
	IMAGE block_group_png[7];
	
	enum blcok_group
	{
		S, Z, L, J, I, O, T//方块组合，待定，仍可添加，顺序和加载方块图片的顺序一致
	};

private:

	/*
	* @brief 绘制地图背景
	*/
	void draw_backgroud();

	/*
	* @brief 初始化方块，即生成方块对象
	*/
	void initial_block();

	/*
	* @brief 加载图片
	*/
	void load_image();
};
