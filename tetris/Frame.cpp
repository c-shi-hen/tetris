#include"Frame.h"
#include"Block.h"
/*
* @brief 游戏初始化时构造，主函数中调用一次
* @param map_width: 横向可容纳方块的数量，map_height:纵向可容纳方块的数量
*/
Frame::Frame(int map_width, int map_height) {
	menu_width = map_width * Block::block_width / 3;
	menu_height = map_height * Block::block_height / 3;
	frame_width = map_width * Block::block_width + menu_width;
	frame_height = map_height * Block::block_height + menu_height;
}

/*
* @brief 游戏结束后调用，主函数中析构
*/
Frame::~Frame() {

}

/*
* @brief 开始游戏
*/
void Frame::begin() {

}
/*
* @brief 生成方块组合，S,Z,L,J,I,O,T
*/
void Frame::generate_block() {

}
/*
* @brief 获得玩家操作信息
* @param message 用于存储信息的结构体
*/
void Frame::get_message(ExMessage& message) {
	while (true) {
		getmessage(&message , -1);

	}
}
/*
* @brief 检查是否可以消除
*/
void Frame::check_line() {

}