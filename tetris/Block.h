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



class Block
{
public:
	Block(int row, int column);
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

private:
	//存储方块图片
	IMAGE block_png[6];


public:
	// 加载方块图片
	void load_image();

	/*
	* @brief 在界面上绘制方块
	*/
	void show();

};
