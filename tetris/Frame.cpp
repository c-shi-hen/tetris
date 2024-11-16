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
	//加载图片
	load_image();
	//初始化消息
	button_down = NON_BUTTON;
}

Frame::~Frame() {

}

void Frame::game_begin() {
	draw_backgroud();
}

void Frame::get_next_block_group() {
	// 创建随机数生成引擎
	std::random_device rd;  // 用于获取随机数种子
	std::mt19937 gen(rd()); // Mersenne Twister 19937 演算法生成器
	// 设置随机数分布范围
	int start = 0;
	int end = 6;
	std::uniform_int_distribution<> dis(start, end); // 均匀分布
	// 生成随机数
	int block_group_shape = dis(gen);
	switch (block_group_shape){
	case S: break;
	case Z: break; 
	case L: break;
	case J: break; 
	case I: break; 
	case O: break;
	case T: break;
	default:break;
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

void Frame::check_crash() {
	bool flag = true;
	for (int i = 0; i < block_group.size(); i++) {
		//下方为地图边界特殊处理
		if (block_group[i]->row == map_height - 1) {
			flag = false;
			break;
		}
		else {
			int row_next = block_group[i]->row + 1;
			int column_next = block_group[i]->column;
			if (block[row_next][column_next]->is_block = true) {
				flag = false;
				break;
			}
		}
	}
	//检查到碰撞，下落停止
	if (flag == false) {
		//检查是否可以消除
		check_line();
	}
}

void Frame::check_line() {
	for (int i = 0; i < map_height; i++) {
		bool flag = true;
		for (int j = 0; j < map_width; j++) {
			if (block[i][j]->is_block = false) {
				flag = false;
				break;
			}
		}
		if (flag) {
			erase_line(i);
			break;
		}
	}
}

void Frame::erase_line(int row) {
	//第一行特殊处理
	if (row == 0) {
		for (int i = 0; i < map_width; i++) {
			block[row][i]->is_block = false;
		}
	}
	else {
		//上一行下落，传递必要参数
		for (int i = 0; i < map_width; i++) {
			block[row][i]->is_block = block[row - 1][i]->is_block;
			block[row][i]->color = block[row - 1][i]->color;
		}
	}
	
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


void Frame::load_image()
{
	//加载背景图片
	loadimage(&background, _T("../res/background.png"));
	//加载方块组合照片,顺序和方块组合的顺序一致
	loadimage(&block_group_png[0], _T("../res/S.png"));
	loadimage(&block_group_png[1], _T("../res/Z.png"));
	loadimage(&block_group_png[2], _T("../res/L.png"));
	loadimage(&block_group_png[3], _T("../res/J.png"));
	loadimage(&block_group_png[4], _T("../res/I.png"));
	loadimage(&block_group_png[5], _T("../res/O.png"));
	loadimage(&block_group_png[6], _T("../res/T.png"));
}
