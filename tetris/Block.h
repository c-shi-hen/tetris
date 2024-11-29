#pragma once
#include<easyx.h>
#include<vector>
#include"Begin_frame.h"

#define BLOCK_BLUE 1
#define BLOCK_GREEN 2
#define BLOCK_LIGHT_BLUE 3
#define BLOCK_ORANGE 4
#define BLOCK_PURPLE 5
#define BLOCK_YELLOW 6


// 枚举所有的方块类型
enum BlockType {
	S, Z, L, J, I, O, T
};



class Block
{
public:
	Block(int row, int column, BlockType type, map_size map);
	~Block();

public:
	//方块宽度
	const static int block_width = 50;
	//方块高度
	const static int block_height = 50;
	//方块所在排数
	int row;
	//方块所在列数
	int column;
	//该位置是否存在方块
	bool is_block = false;
	//方块颜色
	int color;

	// 方块类型
	BlockType type;

	// 地图的宽度和高度
	//表示当前游戏地图的大小,动态地控制方块的移动范围。
	map_size game_map;

private:
	//存储方块图片
	IMAGE block_png[6];

	// 方块形状（可以根据类型来更新形状）
	int shape[4][4];


public:
	// 加载方块图片
	void load_image();

	/*
	* @brief 在界面上绘制方块
	*/
	void show();


	// 控制方块移动（左、右、下）
	void moveLeft();
	void moveRight();
	void moveDown();

	// 设置方块是否存在
	void setActive(bool active);

	// 旋转方块
	void rotate();

	// 检查目标位置是否有碰撞
	bool checkCollision(int targetRow, int targetColumn);

	// 初始化方块形状
	void loadShape();
};
