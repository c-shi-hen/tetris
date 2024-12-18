#include"Begin_frame.h"


Begin_frame::Begin_frame(Animation* animation) {
	//默认地图宽度和高度
	this->map_height = 20;
	this->map_width = 10;
	this->background = &animation->back_ground;
}


Begin_frame::~Begin_frame()
{
}

/*
* @brief 获取初始化游戏界面的必要信息
*/
void Begin_frame::initial() {
	//初始界面背景
	draw_backgroud();

}

/*
* @brief 绘制地图背景
*/
void inline Begin_frame::draw_backgroud() {
	putimage(0, 0, background);
}