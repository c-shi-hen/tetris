#pragma once
#include <wtypes.h>
#include"Block.h"
#include <vector>
#include<easyx.h>

//定义按下的方向键
#define NON_BUTTON 0
#define LEFT 1
#define RIGHT 2
#define UP 3
#define DOWN 4

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
	int map_width;
	int map_height;
	ExMessage message;
	std::vector<std::vector<Block*>> block;

private:
	IMAGE background;
	int button_down;
private:
	void draw_backgroud();
	void initial_block();
};
