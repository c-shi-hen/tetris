#pragma once
#include<easyx.h>
class Block
{
public:
	Block(int row, int column);
	~Block();

public:
	const static int block_width = 50;
	const static int block_height = 50;
	int row;
	int column;
	bool is_block = false;
private:
	IMAGE block_png[6];
public:
	// 加载方块图片
	void load_iamge();
};