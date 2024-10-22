#include"Frame.h"
#include"Block.h"
/*
* @brief 游戏初始化时构造，主函数中调用一次
* @param map_width: 横向可容纳方块的数量，map_height:纵向可容纳方块的数量
*/
Frame::Frame(int map_width, int map_height) {
	//获得地图参数
	this->map_height = map_height;
	this->map_width = map_width;
	menu_width = map_width * Block::block_width / 4;
	menu_height = map_height * Block::block_height;
	frame_width = map_width * Block::block_width + menu_width;
	frame_height = map_height * Block::block_height;
	//默认其他参数
	message = {};
	//生成方块
	initial_block();
	//加载背景图片
	loadimage(&background, _T("background.png"));
	//初始化消息
	button_down = NON_BUTTON;
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
	draw_backgroud();
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
		if (message.message == WM_KEYDOWN) {
			//确保按下第二个键时第一个键已经松开
			if (!button_down) {
				switch (message.vkcode){
				case VK_UP: button_down = UP; break;
				case VK_DOWN: button_down = DOWN; break;
				case VK_LEFT: button_down = LEFT; break;
				case VK_RIGHT: button_down = RIGHT; break;
				default:
					break;
				}
			}
		}
		else if (message.message == WM_KEYUP) {
			button_down = NON_BUTTON;
		}
		else if (message.message == WM_LBUTTONDOWN) {

		}
		else if (message.message == WM_NCLBUTTONUP) {

		}
		Sleep(1000 / 60);
	}
}
/*
* @brief 检查是否可以消除
*/
void Frame::check_line() {

}

/*
* @brief 绘制地图背景
*/
void inline Frame::draw_backgroud() {
	putimage(0, 0, &background);
	//const int line_size = 4;
	//setlinestyle(PS_SOLID, line_size);
	//setlinecolor(WHITE);
	//for (int i = 0; i < map_height; i++) {
	//	line(0, Block::block_height * i + line_size / 2, Block::block_width * map_width, Block::block_height * i + line_size / 2);
	//}
	//for (int i = 0; i <= map_width; i++) {
	//	line(Block::block_width * i + line_size / 2, 0, Block::block_width * i + line_size / 2, Block::block_height * map_width);
	//}
}

/*
* @brief 初始化方块，即生成方块对象
*/
void inline Frame::initial_block(){
	for (int i = 0; i < map_width; i++) {
		std::vector<Block*> block_line;
		for (int j = 0; j < map_height; j++) {
			block_line.push_back(new Block(i ,j));
		}
		block.push_back(block_line);
	}
}
