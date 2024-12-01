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
	//加载图片
	load_image();
	//初始化消息
	message = {};
	button_down = NON_BUTTON;
	//初始化得分
	score = 0;
	//初始化得分坐标
	score_x_axis = 0;
	score_y_axis = 0;
	//初始化速度
	speed = 1;
	//生成方块
	initial_block();
	//初始化方块组合图片的坐标
	next_group_block_x_axis = 10;
	next_group_block_y_axis = 10;
}

Frame::~Frame() {

}

void Frame::game_begin() {
	//生成第一个方块
	get_next_block_group();
	//绘制背景
	draw_backgroud();
	//绘制方块
	draw_block();
	//绘制得分
	draw_score();
	//生成第二个方块组合
	get_next_block_group();
	//绘制下一个方块组合的图片
	draw_block_group_png();
	//显示
	FlushBatchDraw();
	//开始get消息
	get_message(message);
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
	rewnew_block_group();
	int block_group_shape = dis(gen);
	next_block_group_png = block_group_shape;
	switch (block_group_shape) {
	case S: {
		int color = BLOCK_GREEN;
		block_group[0][1]->is_block = true;
		block_group[0][1]->color = color;
		block_group[0][2]->is_block = true;
		block_group[0][2]->color = color;
		block_group[1][0]->is_block = true;
		block_group[1][0]->color = color;
		block_group[1][1]->is_block = true;
		block_group[1][1]->color = color;
		break;
	}
	case Z: {
		int color = BLOCK_GREEN;
		block_group[0][1]->is_block = true;
		block_group[0][1]->color = color;
		block_group[0][2]->is_block = true;
		block_group[0][2]->color = color;
		block_group[1][0]->is_block = true;
		block_group[1][0]->color = color;
		block_group[1][1]->is_block = true;
		block_group[1][1]->color = color;
		break;
	}
	case L: {
		int color = BLOCK_GREEN;
		block_group[0][1]->is_block = true;
		block_group[0][1]->color = color;
		block_group[0][2]->is_block = true;
		block_group[0][2]->color = color;
		block_group[1][0]->is_block = true;
		block_group[1][0]->color = color;
		block_group[1][1]->is_block = true;
		block_group[1][1]->color = color;
		break;
	}
	case J: {
		int color = BLOCK_GREEN;
		block_group[0][1]->is_block = true;
		block_group[0][1]->color = color;
		block_group[0][2]->is_block = true;
		block_group[0][2]->color = color;
		block_group[1][0]->is_block = true;
		block_group[1][0]->color = color;
		block_group[1][1]->is_block = true;
		block_group[1][1]->color = color;
		break;
	}
	case I: {
		int color = BLOCK_GREEN;
		block_group[0][1]->is_block = true;
		block_group[0][1]->color = color;
		block_group[0][2]->is_block = true;
		block_group[0][2]->color = color;
		block_group[1][0]->is_block = true;
		block_group[1][0]->color = color;
		block_group[1][1]->is_block = true;
		block_group[1][1]->color = color;
		break;
	}
	case O: {
		int color = BLOCK_GREEN;
		block_group[0][1]->is_block = true;
		block_group[0][1]->color = color;
		block_group[0][2]->is_block = true;
		block_group[0][2]->color = color;
		block_group[1][0]->is_block = true;
		block_group[1][0]->color = color;
		block_group[1][1]->is_block = true;
		block_group[1][1]->color = color;
		break;
	}
	case T: {
		int color = BLOCK_GREEN;
		block_group[0][1]->is_block = true;
		block_group[0][1]->color = color;
		block_group[0][2]->is_block = true;
		block_group[0][2]->color = color;
		block_group[1][0]->is_block = true;
		block_group[1][0]->color = color;
		block_group[1][1]->is_block = true;
		block_group[1][1]->color = color;
		break;
	}
	default:
			//程序出错，直接退出
			exit(0);
			break;
	}
}

void Frame::get_message(ExMessage& message) {
	while (true) {
		//动态延时优化性能，保证每次循环执行的时间高于帧率
		//开始时间
		ULONGLONG begin_time = GetTickCount64();
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
		//刷新
		renew_frame();
		//结束时间
		ULONGLONG end_time = GetTickCount64();
		//如果执行时间低于帧间隔，阻塞所缺时间，帧率设置为60
		int run_time = end_time - begin_time;
		if (run_time < 1000 / 60) {
			Sleep(1000 / 60 - run_time);
		}
	}
}

void Frame::check_crash() {
	bool flag = true;
	//单独检测每一个方块会不会出现碰撞
	
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
	for (int i = 0; i < map_height; i++) {
		std::vector<Block*> block_line;
		for (int j = 0; j < map_width; j++) {
			block_line.push_back(new Block(i ,j));
		}
		block.push_back(block_line);
	}
}

void Frame::renew_frame() {
	//清除界面
	cleardevice();
	//绘制背景
	draw_backgroud();
	//绘制方块
	draw_block();
	//绘制得分
	draw_score();
	//绘制下一个方块组合的图片
	draw_block_group_png();
	//显示
	FlushBatchDraw();
}


void Frame::draw_block() {
	for (int i = 0; i < map_height; i++) {
		for (int j = 0; j < map_width; j++) {
			block[i][j]->show();
		}
	}
}

void Frame::draw_score() {
	//存储要显示的字符串
	static TCHAR score_str[64];
	//格式化字符串
	_stprintf_s(score_str, _T("当前得分为：%d"), score);
	//获取当前字体样式
	LOGFONT font_style;
	gettextstyle(&font_style);
	//更改字体样式
	font_style.lfHeight = 16;
	font_style.lfWeight = 16;
	//设置字体样式
	settextstyle(&font_style);
	//设置颜色
	settextcolor(RED);
	//指定坐标显示
	outtextxy(score_x_axis, score_y_axis, score_str);
}

void Frame::draw_block_group_png() {
	putimage(next_group_block_x_axis, next_group_block_y_axis, &block_group_png[next_block_group_png]);
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

void Frame::rewnew_block_group() {
	for (int i = 0; i < 4; i++) {
		std::vector<Block*> temp_line;
		for (int j = map_width / 2 - 1; j < map_width / 2 + 3; j++) {
			temp_line.push_back(block[i][j]);
		}
		block_group.push_back(temp_line);
	}
}

// 向左移动方块
void Frame::moveLeft() {
	
}

// 向右移动方块
void Frame::moveRight() {
	
}

// 向下移动方块
void Frame::moveDown() {
	
}


// 检查是否与其他方块发生碰撞
//暂时只实现了是否会超出地图边界的检测
//之后可能需要定义一个二维数组，其中每个元素表示一个位置。如果某个位置有方块，它会指向一个方块对象。如果没有方块，则为 nullptr
bool Frame::checkCollision(int targetRow, int targetColumn) {
	
	return false;
}

// 旋转方块（顺时针90度）
void Frame::rotate() {
	//int temp[4][4];

	//// 将当前的形状复制到临时数组
	//for (int i = 0; i < 4; ++i) {
	//	for (int j = 0; j < 4; ++j) {
	//		temp[i][j] = block_group[i][j];
	//	}
	//}

	//// 顺时针旋转90度
	//for (int i = 0; i < 4; ++i) {
	//	for (int j = 0; j < 4; ++j) {
	//		block_group[i][j] = temp[3 - j][i];
	//	}
	//}

	//// 检查旋转后的方块是否与其他方块发生碰撞
	//if (checkCollision(row, column)) {
	//	// 如果发生碰撞，恢复到原始状态
	//	for (int i = 0; i < 4; ++i) {
	//		for (int j = 0; j < 4; ++j) {
	//			block_group[i][j] = temp[i][j];
	//		}
	//	}
	//}
}