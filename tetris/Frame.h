#pragma once
#include <wtypes.h>
#include"Block.h"
#include <vector>
#include"Animation.h"
#include <windows.h> // 包含 Windows API
#include <tchar.h> 


#define VK_W 0x57
#define VK_S 0x53
#define VK_A 0x41
#define VK_D 0x44


class Frame
{
public:
	/*
	* @brief 游戏初始化时构造，主函数中调用一次
	* @param map_width: 横向可容纳方块的数量，map_height:纵向可容纳方块的数量
	*/
	Frame(int map_width, int map_height, Animation* animation);

	/*
	* @brief 游戏结束后调用，主函数中析构
	*/
	~Frame();

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
	*@brief 显示下一个方块组合的照片
	*/
	void draw_block_group_png();

	// 控制方块移动（左、右、下、最下）
	bool moveLeft();
	bool moveRight();
	bool moveDown();
	bool moveToLowestPosition();

	// 旋转方块
	void rotate();

	// 检查目标位置是否有碰撞
	bool checkCollision(int targetRow, int targetColumn);


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

	//下落速度
	int SPEED;

	//时间
	int time;



private:
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

	//释放方块组合的内存
	void delete_block_group();
};
