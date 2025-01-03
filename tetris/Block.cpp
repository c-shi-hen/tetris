#include"Block.h"
#include"Begin_frame.h"
#include<iostream>


Block::Block(int row, int column, std::vector<IMAGE*>* block_png) {
	//存储初始化时行和列
	this->row = row;
	this->column = column;
	//初始化color
	this->color = -1;
	//获取图片指针
	this->block_png = block_png;
}

Block::~Block(){

}

void Block::show() {
	//确保存在方块
	if (is_block && color != -1) {
		int x_axis = block_width * column;
		int y_axis = block_height * row;
		putimage(x_axis, y_axis, block_png->at(color));
	}
}

