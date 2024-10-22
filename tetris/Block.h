#pragma once
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
private:

};