#pragma once
#include <wtypes.h>
#include"Block.h"
#include <vector>
#include<easyx.h>
class Frame
{
public:
	Frame(int map_width, int map_height);
	~Frame();
	void begin();
	void generate_block();
	void get_message(ExMessage& message);
	void check_line();
public:
	int menu_width;
	int menu_height;
	int frame_width;
	int frame_height;
	ExMessage message;
	std::vector<std::vector<Block>> block;
private:

};
