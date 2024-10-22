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