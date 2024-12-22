#pragma once
#include<easyx.h>
#include<vector>
#include"Begin_frame.h"

#define BLOCK_BLUE 0
#define BLOCK_GREEN 1
#define BLOCK_LIGHT_BLUE 2
#define BLOCK_ORANGE 3
#define BLOCK_PURPLE 4
#define BLOCK_YELLOW 5

class Block
{
public:

	/*
	* @param row : 该方块的行序号， column : 该方块的列数序号；均以0开始
	* @brief 生成方块对象
	*/
	Block(int row, int column, std::vector<IMAGE*>* block_png);

	~Block();

public:
	//方块宽度，由方块的图片决定
	const static int block_width = 30;

	//方块高度，由方块的图片决定
	const static int block_height = 30;

	//方块所在排数
	int row;

	//方块所在列数
	int column;

	//该位置是否存在方块
	bool is_block = false;

	//方块颜色
	int color;

	//存储方块图片
	std::vector<IMAGE*>* block_png;

public:

	/*
	* @brief 在界面上绘制方块
	*/
	void show();

};
