#include"Frame.h"
#include"Block.h"
#include<random>


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

Frame::~Frame() {

}

void Frame::begin() {
	draw_backgroud();
}

void Frame::generate_block_group() {
	enum blcok_group
	{
		S,Z,L,J,I,O,T
	};
	// 创建随机数生成引擎
	std::random_device rd;  // 用于获取随机数种子
	std::mt19937 gen(rd()); // Mersenne Twister 19937 演算法生成器
	// 设置随机数分布范围
	int start = 1;
	int end = 7;
	std::uniform_int_distribution<> dis(start, end); // 均匀分布
	// 生成随机数
	int randomInteger = dis(gen);
	switch (randomInteger - 1){
	case S: 
	default:
		break;
	}
}

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
		Sleep(1000 / 100);
	}
}

void Frame::check_line() {

}

void inline Frame::draw_backgroud() {
	putimage(0, 0, &background);
}

void inline Frame::initial_block(){
	for (int i = 0; i < map_width; i++) {
		std::vector<Block*> block_line;
		for (int j = 0; j < map_height; j++) {
			block_line.push_back(new Block(i ,j));
		}
		block.push_back(block_line);
	}
}
