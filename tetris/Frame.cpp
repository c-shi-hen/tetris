#include"Frame.h"
#include"Block.h"
#include<random>
#include<iostream>
#include"EndGame.h"


Frame::Frame(Animation* animation, Begin_frame* begin_frame) {

	//获得主菜单指针
	this->begin_frame = begin_frame;

	//获得地图参数
	this->map_height = begin_frame->map_height + 4;//前四行留给生成方块使用
	this->map_width = begin_frame->map_width;
	this->menu_width = begin_frame->map_width * Block::block_width / 4 + 200;
	this->menu_height = begin_frame->map_height * Block::block_height;
	this->frame_width = this->map_width * Block::block_width + menu_width;
	this->frame_height = this->map_height * Block::block_height;

	//获取图片资源
	this->animation = animation;
	this->background = &animation->back_ground;
	this->block_group_png = &animation->block_group_png;

	//初始化消息
	this->message = {};
	this->is_up = false;
	this->is_down = false;
	this->is_left = false;
	this->is_right = false;
	this->is_space = false;
	this->is_pause = false;
	this->is_generate_end_game = false;
	this->is_over = false;

	//初始化得分
	this->score = 0;

	//初始化得分坐标
	this->score_x_axis = this->map_width * Block::block_width + menu_width / 5;
	this->score_y_axis = 20;

	//初始化速度坐标
	this->speed_x_axis = this->map_width * Block::block_width + menu_width / 5;
	this->speed_y_aixs = 60;
	
	//初始化关卡坐标
	this->level_x_axis = this->map_width * Block::block_width + menu_width / 5;
	this->level_y_axis = 100;

	//初始化暂停坐标
	this->pause_x_axis = this->frame_width / 2 - 200;
	this->pause_y_axis = this->frame_height / 2 - 100;

	//初始化速度
	this->SPEED = begin_frame->gameSpeed;

	//初始化种子
	this->seed = begin_frame->randomSeed;

	//初始化关卡
	this->level = begin_frame->initialLevel;

	//初始化方块组合图片的坐标
	this->next_group_block_x_axis = this->map_width * Block::block_width + menu_width / 6;
	this->next_group_block_y_axis = 200;

	//初始化进行
	this->running = false;

	//获取残局信息
	this->map = begin_frame->map;
	this->blockColors = begin_frame->blockColors;

	//生成方块
	initial_block();
}

Frame::~Frame() {
	//释放方块对象
	for (int i = 0; i < map_height; i++) {
		for (int j = 0; j < map_width; j++) {
			delete block[i][j];
		}
	}
	//释放当前正在下落的方块
	delete_block_group();

	//释放下一个方块组合
	for(int i = 0; i < next_block_group.size(); i++){
		for (int j = 0; j < next_block_group[i].size(); j++) {
			delete next_block_group[i][j];
		}
	}

}

//初始化部分
void Frame::initial_block() {

	for (int i = 0; i < 4; i++) {
		std::vector<Block*> block_line;
		for (int j = 0; j < map_width; j++) {
			Block* temp = new Block(i, j, &this->animation->block_png);
			block_line.push_back(temp);
		}
		block.push_back(block_line);
	}

	for (int i = 4; i < map_height; i++) {
		std::vector<Block*> block_line;
		for (int j = 0; j < map_width; j++) {
			Block* temp = new Block(i, j, &this->animation->block_png);
			temp->is_block = this->map[i - 4][j];
			temp->color = this->blockColors[i - 4][j];
			block_line.push_back(temp);
		}
		block.push_back(block_line);
	}
}


//游戏开始与结束
void Frame::game_begin() {

	//初始化种子
	//创建随机数生成引擎
	if (seed != -1){
		std::srand(this->seed);
	}
	
	//生成第一个方块组合
	generate_block_group();

	//由于当前不存在方块组合，因此立即传递一个
	trans_block_group();

	//绘制背景
	draw_backgroud();

	//绘制方块
	draw_block();

	//绘制得分
	draw_score();

	//绘制速度
	draw_speed();

	//绘制关卡
	draw_level();

	//生成第二个方块组合
	generate_block_group();

	//绘制下一个方块组合的图片
	draw_block_group_png();

	//绘制一条分界线
	setlinecolor(RED);
	line(map_width * Block::block_width, 0, map_width, map_height * Block::block_height);

	//显示
	FlushBatchDraw();

	//开始运行
	this->running = true;

	//开始get消息
	get_message(message);
}

void Frame::game_over() {
	running = false;
	renew_frame();
}

//获取消息部分
void Frame::get_message(ExMessage& message) {

	int timer = 0;
	int temp_speed = SPEED + level;
	while (running) {
		timer++;
		//动态延时优化性能，保证每次循环执行的时间高于帧率
		//开始时间
		ULONGLONG begin_time = GetTickCount64();
		
		while (peekmessage(&message)) {
			
			if (message.message == WM_KEYDOWN) {
				//每个按键单独处理
				switch (message.vkcode) {
				case VK_W: {
					is_up = true;
					break;
				}
				case VK_S: {
					is_down = true;
					break;
				}
				case VK_A: {
					if (!is_right) {
						is_left = true;
					}
					break;
				}
				case VK_D: {
					if (!is_left) {
						is_right = true;
					}
					break;
				}
				case VK_SPACE: {
					is_space = true;
					break;
				}
				case VK_ESCAPE: {
					if (is_pause) {
						is_pause = false;
					}
					else {
						is_pause = true;
					}
					break;
				}
				case VK_G: {
					is_generate_end_game = true;
					break;
				}
				case VK_P: {
					if (is_pause) {
						is_over = true;
					}
					break;
				}
				default:
					break;
				}
			}
			else if (message.message == WM_KEYUP) {
				switch (message.vkcode) {
				case VK_W: {
					is_up = false;
					break;
				}
				case VK_S: {
					is_down = false;
					//松下按键后刷新速度
					temp_speed = SPEED + level;
					break;
				}
				case VK_A: {
					is_left = false;
					break;
				}
				case VK_D: {
					is_right = false;
					break;
				}
				case VK_SPACE: {
					is_space = false;
					break;
				}
				case VK_G: {
					is_generate_end_game = false;
					break;
				}
				default:
					break;
				}
			}
		}

		if (!is_pause) {
			if (is_left) {
				moveLeft();
				is_left = false;
				renew_frame();
			}
			if (is_right) {
				moveRight();
				is_right = false;
				renew_frame();
			}
			if (is_up) {
				rotate();
				is_up = false;
				renew_frame();
			}
			if (is_down && temp_speed <= 50) temp_speed++;
			if (is_space) {
				moveToLowestPosition();
				is_space = false;
				renew_frame();
			}

			//每隔 1000/speed ms下落一行
			int timer_gap = (int)1000.0 / temp_speed / 16.7;
			if (timer % timer_gap == 0) {
				moveDown();
				renew_frame();
				timer %= timer_gap;
			}
		}
		else {
			//在暂停的情况下，生成残局
			if (is_generate_end_game) {
				generate_end_game();
			}
			renew_frame();

			if (is_over) {
				game_over();
			}
		}

		//结束时间
		ULONGLONG end_time = GetTickCount64();
		//如果执行时间低于帧间隔，阻塞所缺时间，帧率设置为60
		int run_time = end_time - begin_time;
		if (run_time < 1000 / 60) {
			Sleep(1000 / 60 - run_time);
		}
	}

}


//方块组合生成、下落、检查消除、检查结束
void Frame::generate_block_group() {

	//刷新block_group
	rewnew_block_group();

	// 生成随机数
	int block_group_shape;
	if (seed != -1) {
		block_group_shape = (int)((double)std::rand() / RAND_MAX * 7);
	}
	else {
		std::random_device rd;  // 用于获取随机数种子
		std::mt19937 gen(rd()); // Mersenne Twister 19937 演算法生成器
		// 设置随机数分布范围
		int start = 0;
		int end = 6;
		std::uniform_int_distribution<> dis(start, end); // 均匀分布
		block_group_shape = dis(gen);
	}

	//测试用
	//int block_group_shape = 4;

	//存储下生成的随机数对应的方块组合图片
	block_group_png_index = block_group_shape;

	//根据随机数生成方块组合
	switch (block_group_shape) {
	case S: {
		int color = BLOCK_GREEN;
		next_block_group[0][1]->is_block = true;
		next_block_group[0][1]->color = color;
		next_block_group[0][2]->is_block = true;
		next_block_group[0][2]->color = color;
		next_block_group[1][0]->is_block = true;
		next_block_group[1][0]->color = color;
		next_block_group[1][1]->is_block = true;
		next_block_group[1][1]->color = color;
		break;
	}
	case Z: {
		int color = BLOCK_BLUE;
		next_block_group[0][0]->is_block = true;
		next_block_group[0][0]->color = color;
		next_block_group[0][1]->is_block = true;
		next_block_group[0][1]->color = color;
		next_block_group[1][1]->is_block = true;
		next_block_group[1][1]->color = color;
		next_block_group[1][2]->is_block = true;
		next_block_group[1][2]->color = color;
		break;
	}
	case L: {
		int color = BLOCK_LIGHT_BLUE;
		next_block_group[0][0]->is_block = true;
		next_block_group[0][0]->color = color;
		next_block_group[1][0]->is_block = true;
		next_block_group[1][0]->color = color;
		next_block_group[1][1]->is_block = true;
		next_block_group[1][1]->color = color;
		next_block_group[1][2]->is_block = true;
		next_block_group[1][2]->color = color;
		break;
	}
	case J: {
		int color = BLOCK_ORANGE;
		next_block_group[0][2]->is_block = true;
		next_block_group[0][2]->color = color;
		next_block_group[1][0]->is_block = true;
		next_block_group[1][0]->color = color;
		next_block_group[1][1]->is_block = true;
		next_block_group[1][1]->color = color;
		next_block_group[1][2]->is_block = true;
		next_block_group[1][2]->color = color;
		break;
	}

	case I: {
		int color = BLOCK_PURPLE;
		next_block_group[0][1]->is_block = true;
		next_block_group[0][1]->color = color;
		next_block_group[1][1]->is_block = true;
		next_block_group[1][1]->color = color;
		next_block_group[2][1]->is_block = true;
		next_block_group[2][1]->color = color;
		next_block_group[3][1]->is_block = true;
		next_block_group[3][1]->color = color;
		break;
	}
	case O: {
		int color = BLOCK_YELLOW;
		next_block_group[0][1]->is_block = true;
		next_block_group[0][1]->color = color;
		next_block_group[0][2]->is_block = true;
		next_block_group[0][2]->color = color;
		next_block_group[1][1]->is_block = true;
		next_block_group[1][1]->color = color;
		next_block_group[1][2]->is_block = true;
		next_block_group[1][2]->color = color;
		break;
	}
	case T: {
		int color = BLOCK_GREEN;
		next_block_group[0][0]->is_block = true;
		next_block_group[0][0]->color = color;
		next_block_group[0][1]->is_block = true;
		next_block_group[0][1]->color = color;
		next_block_group[0][2]->is_block = true;
		next_block_group[0][2]->color = color;
		next_block_group[1][1]->is_block = true;
		next_block_group[1][1]->color = color;
		break;
	}
	default:
		//程序出错，直接退出
		std::cout << "未能生成新方块，随机数种子出错" << std::endl;
		exit(0);
		break;
	}
}

void Frame::check_line() {
	//检测是否可以消除
	bool is_erase = true;

	//连续消除得分倍数翻倍
	int base = 1;

	//第一次默认可以消除，直到出现不能消除的情况再结束
	while (is_erase) {
		for (int i = 0; i < map_height; i++) {
			is_erase = false;
			bool flag = true;
			for (int j = 0; j < map_width; j++) {
				if (block[i][j]->is_block == false) {
					flag = false;
					break;
				}
			}
			if (flag) {
				erase_line(i);
				this->score += base;
				base *= 2;
				is_erase = true;
				break;
			}
		}
	}

	//判断当前得分，提升关卡难度。每次获得十分，就增加一次关卡难度
	if (score > (10 * level)) {
		level++;
	}
}

void Frame::erase_line(int row) {

	//直接覆盖改行，之后整体下移一行
	for (int i = row; i > 0; i--) {
		for (int j = 0; j < map_width; j++) {
			block[i][j]->is_block = block[i - 1][j]->is_block;
			block[i][j]->color = block[i - 1][j]->color;
		}
	}

	//第一行清除为空
	for (int i = 0; i < map_width; i++) {
		block[0][i]->is_block = false;
	}
}

void Frame::rewnew_block_group() {
	for (int i = 0; i < 4; i++) {
		std::vector<Block*> temp_line;
		for (int j = map_width / 2 - 1; j < map_width / 2 + 3; j++) {
			Block* temp = new Block(i, j, &this->animation->block_png);
			temp->is_block = false;
			temp_line.push_back(temp);
		}
		next_block_group.push_back(temp_line);
	}
}

void Frame::delete_block_group() {
	for (int i = 0; i < block_group.size(); i++) {
		for (int j = 0; j < block_group[i].size(); j++) {
			delete block_group[i][j];
		}
		block_group[i].clear();
	}
	block_group.clear();
}

void Frame::trans_block_group() {
	for (int i = 0; i < next_block_group.size(); i++) {
		std::vector<Block*> temp_line;
		for (int j = 0; j < next_block_group[i].size(); j++) {
			temp_line.push_back(next_block_group[i][j]);
		}
		block_group.push_back(temp_line);
	}
	//传递之后自身被清空
	next_block_group.clear();
}

void Frame::check_over_map() {
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < map_width; j++) {
			//查找出现溢出
			if (block[i][j]->is_block == true) {
				game_over();
			}
		}
	}
}


//显示部分
void Frame::renew_frame() {
	//清除界面
	cleardevice();

	//绘制背景
	draw_backgroud();

	//绘制方块
	draw_block();

	//绘制得分
	draw_score();

	//绘制速度
	draw_speed();

	//绘制关卡
	draw_level();

	//绘制下一个方块组合的图片
	draw_block_group_png();

	//绘制一条分界线
	setlinecolor(RED);
	line(map_width * Block::block_width, 0, map_width * Block::block_width, map_height * Block::block_height);

	//绘制截止线
	line(0, 4 * Block::block_height, map_width * Block::block_width, 4 * Block::block_height);
	setlinecolor(BLACK);

	//游戏是否结束
	if (!running) {
		draw_game_over();
	}

	//游戏是否暂停
	if (is_pause) {
		draw_pause();
	}

	//显示
	FlushBatchDraw();
}

void Frame::draw_block() {

	//绘制棋盘本身
	for (int i = 0; i < map_height; i++) {
		for (int j = 0; j < map_width; j++) {
			block[i][j]->show();
		}
	}

	//绘制当前下落组合
	for (auto& x : block_group) {
		for (auto& y : x) {
			y->show();
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
	font_style.lfHeight = 25;
	font_style.lfWeight = 25;
	//设置背景透明
	setbkmode(TRANSPARENT);
	//设置字体样式
	settextstyle(&font_style);
	//设置颜色
	settextcolor(RED);
	//指定坐标显示
	outtextxy(score_x_axis, score_y_axis, score_str);
}

void Frame::draw_block_group_png() {
	putimage(next_group_block_x_axis, next_group_block_y_axis, block_group_png->at(block_group_png_index));
}

void Frame::draw_speed() {
	//存储要显示的字符串
	static TCHAR speed_str[64];
	//格式化字符串
	_stprintf_s(speed_str, _T("游戏基础速度：%d"), SPEED);
	//获取当前字体样式
	LOGFONT font_style;
	gettextstyle(&font_style);
	//更改字体样式
	font_style.lfHeight = 25;
	font_style.lfWeight = 25;
	//设置背景透明
	setbkmode(TRANSPARENT);
	//设置字体样式
	settextstyle(&font_style);
	//设置颜色
	settextcolor(RED);
	//指定坐标显示
	outtextxy(speed_x_axis, speed_y_aixs, speed_str);
}

void Frame::draw_level() {
	//存储要显示的字符串
	static TCHAR level_str[64];
	//格式化字符串
	_stprintf_s(level_str, _T("当前关卡：%d"), level);
	//获取当前字体样式
	LOGFONT font_style;
	gettextstyle(&font_style);
	//更改字体样式
	font_style.lfHeight = 25;
	font_style.lfWeight = 25;
	//设置背景透明
	setbkmode(TRANSPARENT);
	//设置字体样式
	settextstyle(&font_style);
	//设置颜色
	settextcolor(RED);
	//指定坐标显示
	outtextxy(level_x_axis, level_y_axis, level_str);
}

void Frame::draw_pause() {
	//存储要显示的字符串
	static TCHAR pause_str[64];
	//格式化字符串
	_stprintf_s(pause_str, _T("游戏暂停"));
	//获取当前字体样式
	LOGFONT font_style;
	gettextstyle(&font_style);
	//更改字体样式
	font_style.lfHeight = 100;
	font_style.lfWeight = 100;
	//设置背景透明
	setbkmode(TRANSPARENT);
	//设置字体样式
	settextstyle(&font_style);
	//设置颜色
	settextcolor(RED);
	//指定坐标显示
	outtextxy(pause_x_axis, pause_y_axis, pause_str);
}

void Frame::draw_backgroud() {
	putimage(0, 0, this->background);
}

void Frame::draw_game_over() {
	//存储要显示的字符串
	static TCHAR pause_str[64];
	//格式化字符串
	_stprintf_s(pause_str, _T("游戏结束"));
	//获取当前字体样式
	LOGFONT font_style;
	gettextstyle(&font_style);
	//更改字体样式
	font_style.lfHeight = 100;
	font_style.lfWeight = 100;
	//设置背景透明
	setbkmode(TRANSPARENT);
	//设置字体样式
	settextstyle(&font_style);
	//设置颜色
	settextcolor(RED);
	//指定坐标显示
	outtextxy(pause_x_axis, pause_y_axis, pause_str);
}


//方块组合移动和下落部分
void Frame::block_group_ground() {

	//检查游戏结束
	check_over_map();

	//检查是否可以消除并消除
	check_line();

	//释放block_group
	delete_block_group();

	//立刻传递新的组合
	trans_block_group();

	//生成下一个组合
	generate_block_group();
}

bool Frame::checkCollision(int deltaRow, int deltaColumn) {
	// 遍历当前下落方块组合中的所有块
	for (auto& row_vec : block_group) {
		for (auto& b : row_vec) {
			if (b->is_block) {
				int targetRow = b->row + deltaRow;
				int targetColumn = b->column + deltaColumn;

				// 检查是否越界
				if (targetRow < 0 || targetRow >= map_height || targetColumn < 0 || targetColumn >= map_width) {
					return true; // 越界表示碰撞
				}

				// 检查该位置是否已被固定方块占据
				if (block[targetRow][targetColumn]->is_block) {
					return true; // 已有方块占据，碰撞
				}
			}
		}
	}

	// 如果所有激活方块检测后均无问题，则表示无碰撞
	return false;
}

bool Frame::moveLeft() {
	// 检查向左移动是否有碰撞
	// deltaRow = 0, deltaColumn = -1 表示尝试向左一格的位置
	if (checkCollision(0, -1)) {
		// 有碰撞则直接返回，不移动
		return false;
	}

	// 无碰撞，可以左移
	for (auto& row_vec : block_group) {
		for (auto& b : row_vec) {
			if (b->is_block) {
				b->column -= 1; // 左移一格
			}
		}
	}
	return true;
}

bool Frame::moveRight() {
	// 检查向右移动是否有碰撞
	// deltaRow = 0, deltaColumn = 1 表示尝试向右一格的位置
	if (checkCollision(0, 1)) {
		// 有碰撞则直接返回，不移动
		return false;
	}

	// 无碰撞，可以右移
	for (auto& row_vec : block_group) {
		for (auto& b : row_vec) {
			if (b->is_block) {
				b->column += 1; // 右移一格
			}
		}
	}
	return true;
}

bool Frame::moveDown() {
	// 检查向下移动是否有碰撞
	// deltaRow = 1, deltaColumn = 0 表示尝试向下移动一格的位置
	if (checkCollision(1, 0)) {
		// 检查到碰撞停止，立即将block_group的数据传送到block
		for (auto& x : block_group) {
			for (auto& y : x) {
				if (y->is_block) {
					block[y->row][y->column]->is_block = true;
					block[y->row][y->column]->color = y->color;
				}
			}
		}
		//调用触底函数，并进行下一个方块组合的xialuo
		block_group_ground();

		return false;
	}

	// 无碰撞，可以下移
	for (auto& row_vec : block_group) {
		for (auto& b : row_vec) {
			if (b->is_block) {
				b->row += 1; // 下移1格
			}
		}
	}
	return true;
}

void Frame::rotate()
{
	// 以 block_group[1][1] 为旋转中心点
	int centerRow = block_group[1][1]->row;
	int centerCol = block_group[1][1]->column;

	// 收集当前下落方块组合中所有激活的方块
	std::vector<Block*> activeBlocks;
	for (auto& row_vec : block_group)
	{
		for (auto& b : row_vec)
		{
			if (b->is_block)
			{
				activeBlocks.push_back(b);
			}
		}
	}

	// 计算旋转后的位置
	std::vector<std::pair<int, int>> rotatedPositions;
	rotatedPositions.reserve(activeBlocks.size());
	for (auto b : activeBlocks)
	{
		int relR = b->row - centerRow;
		int relC = b->column - centerCol;

		// 顺时针90度旋转公式：
		// (relR, relC) -> (-relC, relR)
		int newR = centerRow - relC;
		int newC = centerCol + relR;

		// 越界检测
		if (newR < 0 || newR >= map_height || newC < 0 || newC >= map_width)
		{
			// 如果越界则不旋转，直接返回
			return;
		}

		// 检测是否与已存在的固定方块重叠
		if (block[newR][newC]->is_block)
		{
			// 已被占用，不旋转
			return;
		}

		rotatedPositions.push_back(std::make_pair(newR, newC));
	}

	// 如果能执行到这里，说明旋转后的所有位置都有效
	// 清除当前 block_group 中所有方块的 is_block 标记
	for (auto& row_vec : block_group)
	{
		for (auto& b : row_vec)
		{
			b->is_block = false;
		}
	}

	// 更新方块到旋转后的位置
	for (size_t i = 0; i < activeBlocks.size(); i++)
	{
		Block* b = activeBlocks[i];
		b->row = rotatedPositions[i].first;
		b->column = rotatedPositions[i].second;
		b->is_block = true;
	}
}

bool Frame::moveToLowestPosition()
{
	// 不断检测方块是否可以继续向下移动一格
	while (!checkCollision(1, 0))
	{
		// 如果无碰撞，则将所有处于激活状态的方块向下移动一格
		for (auto& row_vec : block_group)
		{
			for (auto& b : row_vec)
			{
				if (b->is_block)
				{
					b->row += 1; // 向下移动一格
				}
			}
		}
	}
	return true;
}


//生成残局部分
void Frame::generate_end_game() {
	//更新残局所需要的参数
	for (int i = 4; i < map_height; i++) {
		for (int j = 0; j < map_width; j++) {
			this->map[i - 4][j] = block[i][j]->is_block;
			this->blockColors[i - 4][j] = block[i][j]->color;
		}
	}

	//创建一个end_game对象
	EndGame end_game(this->map_height - 4, this->map_width, this->level, this->map, this->blockColors);
	std::string filename;
	std::cout << "请输入残局文件名: ";
	while (std::cin >> filename) {
		if (end_game.saveToFile(filename)) {
			std::cout << "创建成功" << std::endl;
			std::cout << "请继续游戏" << std::endl;
			break;
		}
		else {
			std::cout << "创建失败，请再试一次" << std::endl;
			std::cout << "请输入残局文件名: ";
		}
	}
}