#include"Begin_frame.h"


Begin_frame::Begin_frame()
{

	
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
	loadimage(&background, _T("../res/background.png"));
	putimage(0, 0, &background);
}