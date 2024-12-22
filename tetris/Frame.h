#pragma once
#include <wtypes.h>
#include"Block.h"
#include <vector>
#include"Animation.h"
#include"Begin_frame.h"

#define VK_W 0x57
#define VK_S 0x53
#define VK_A 0x41
#define VK_D 0x44
#define VK_G 0x47
#define VK_P 0x50

class Frame
{
public:

	/*
	* @brief 游戏初始化时构造，主函数中调用一次
	* @param animation: 资源类指针， begin_frame : 主界面指针
	*/
	Frame(Animation* animation, Begin_frame* begin_frame);

	/*
	* @brief 游戏结束后调用，主函数中析构
	*/
	~Frame();

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

	//W,A,S,D,SPACE各个按键的状态
	bool is_up;
	bool is_down;
	bool is_left;
	bool is_right;
	bool is_space;
	bool is_pause;
	bool is_generate_end_game;
	bool is_over;

	//方块矩阵
	std::vector<std::vector<Block*>> block;

	//当前下落方块组合
	std::vector<std::vector<Block*>> block_group;
	//下一个方块组合
	std::vector<std::vector<Block*>> next_block_group;

	//方块组合字符表示的index
	int block_group_png_index;

	//方块组合图片显示的坐标
	int next_group_block_x_axis;
	int next_group_block_y_axis;

	//玩家得分
	int score;

	//得分坐标
	int score_x_axis;
	int score_y_axis;

	//游戏暂停坐标
	int pause_x_axis;
	int pause_y_axis;

	//速度坐标
	int speed_x_axis;
	int speed_y_aixs;

	//关卡难度坐标
	int level_x_axis;
	int level_y_axis;

	//下落速度
	int SPEED;

	//随机数种子
	int seed;

	//关卡数
	int level;

	//残局信息
	//地图状态
	std::vector<std::vector<bool>> map;
	// 方块颜色
	std::vector<std::vector<int>> blockColors;

	//主界面指针
	Begin_frame* begin_frame;
	//图片资源指针
	Animation* animation;
	//背景照片
	IMAGE* background;
	//方块组合照片
	std::vector<IMAGE*>* block_group_png;

	enum blcok_group
	{
		S, Z, L, J, I, O, T//方块组合，待定，仍可添加，顺序和加载方块图片的顺序一致
	};

	//游戏是否正在进行
	bool running;

public:
	/*
	* @brief 开始游戏
	*/
	void game_begin();

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
	*@brief 显示速度
	*/
	void draw_speed();

	/*
	*@brief 显示关卡
	*/
	void draw_level();

	/*
	*@brief 显示下一个方块组合的照片
	*/
	void draw_block_group_png();

	/*
	*@brief 控制方块移动：左
	*/
	bool moveLeft();
	/*
	*@brief 控制方块移动：右
	*/
	bool moveRight();
	/*
	*@brief 控制方块移动：下落
	*/
	bool moveDown();
	/*
	*@brief 控制方块移动：下落到最底
	*/
	bool moveToLowestPosition();

	/*
	*@brief 旋转方块
	*/
	void rotate();

	/*
	* @param targetRow : 目标行， targetColumn : 目标列
	* @brief 检查目标位置是否有碰撞
	* 以行列偏移量（deltaRow, deltaColumn）为参数，用于在移动或旋转方块之前进行检测。
	* 当准备向某个方向（左、右、下）移动或在旋转后变换坐标时，
	* 只需根据新坐标计算出相对于当前坐标的偏移（或新位置），然后调用该函数检查是否有碰撞
	*/
	bool checkCollision(int targetRow, int targetColumn);

	/*
	* @brief 绘制地图背景
	*/
	void draw_backgroud();

	/*
	* @brief 初始化方块，即生成方块对象
	*/
	void initial_block();

	/*
	* @brief 生成方块组合
	*/
	void generate_block_group();

	/*
	* @brief 更新block_group
	*/
	void rewnew_block_group();

	/*
	* @brief 在方块落地后，将next_block_group传递给block_group
	*/
	void trans_block_group();

	/*
	* @brief 方块组合落地
	*/
	void block_group_ground();

	/*
	* @brief 释放方块组合的内存
	*/
	void delete_block_group();

	/*
	* @brief 判断是否出现溢出地图上边界，也即游戏结束
	*/
	void check_over_map();

	/*
	* @brief 判断游戏结束。当出现方块组合第一次溢出的时候，游戏结束
	*/
	void game_over();

	/*
	* @brief 生成残局
	*/
	void generate_end_game();

	/*
	* @brief 显示游戏暂停文字
	*/
	void draw_pause();

	/*
	* @brief 显示游戏结束文字
	*/
	void draw_game_over();
};