#include"Block.h"
/*
* @param row : 该方块的行序号， column : 该方块的列数序号；均以0开始
*/
Block::Block(int row, int column)
{
	this->row = row;
	this->column = column;
}

Block::~Block()
{
}

// 加载方块图片
void Block::load_iamge(){
	loadimage(&block_png[0], _T("../res/blue.png"));
	loadimage(&block_png[1], _T("../res/green.png"));
	loadimage(&block_png[2], _T("../res/light_blue.png"));
	loadimage(&block_png[3], _T("../res/orange.png"));
	loadimage(&block_png[4], _T("../res/purple.png"));
	loadimage(&block_png[5], _T("../res/yellow.png"));
}
