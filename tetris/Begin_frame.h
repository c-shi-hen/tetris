#pragma once
#include<easyx.h>
struct map_size
{
	int map_width;
	int map_height;
};
class Begin_frame
{
public:

	Begin_frame();
	~Begin_frame();
	void initial();

public:
	//默认窗口宽度
	const int begin_frame_width = 800;
	//默认窗口高度
	const int begin_frame_height = 800;
	//默认地图大小
	const map_size default_map_size = { 10, 20 };
private:
	IMAGE background;
	void inline draw_backgroud();
};

//实现开始界面
//开始游戏
//残局挑战
//残局生成
//退出游戏
//