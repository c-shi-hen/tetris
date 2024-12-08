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
	//get_next_block_group();
	//绘制下一个方块组合的图片
	//draw_block_group_png();
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
		block_group[0][0]->is_block = true;
		block_group[0][0]->color = color;
		block_group[0][1]->is_block = true;
		block_group[0][1]->color = color;
		block_group[1][1]->is_block = true;
		block_group[1][1]->color = color;
		block_group[1][2]->is_block = true;
		block_group[1][2]->color = color;
		break;
	}
	case L: {
		int color = BLOCK_GREEN;
		block_group[0][0]->is_block = true;
		block_group[0][0]->color = color;
		block_group[1][0]->is_block = true;
		block_group[1][0]->color = color;
		block_group[1][1]->is_block = true;
		block_group[1][1]->color = color;
		block_group[1][2]->is_block = true;
		block_group[1][2]->color = color;
		break;
	}
	case J: {
		int color = BLOCK_GREEN;
		block_group[0][2]->is_block = true;
		block_group[0][2]->color = color;
		block_group[1][0]->is_block = true;
		block_group[1][0]->color = color;
		block_group[1][1]->is_block = true;
		block_group[1][1]->color = color;
		block_group[1][2]->is_block = true;
		block_group[1][2]->color = color;
		break;
	}

	case I: {
		int color = BLOCK_GREEN;
		block_group[0][1]->is_block = true;
		block_group[0][1]->color = color;
		block_group[1][1]->is_block = true;
		block_group[1][1]->color = color;
		block_group[2][1]->is_block = true;
		block_group[2][1]->color = color;
		block_group[3][1]->is_block = true;
		block_group[3][1]->color = color;
		break;
	}
	case O: {
		int color = BLOCK_GREEN;
		block_group[0][1]->is_block = true;
		block_group[0][1]->color = color;
		block_group[0][2]->is_block = true;
		block_group[0][2]->color = color;
		block_group[1][1]->is_block = true;
		block_group[1][1]->color = color;
		block_group[1][2]->is_block = true;
		block_group[1][2]->color = color;
		break;
	}
	case T: {
		int color = BLOCK_GREEN;
		block_group[0][0]->is_block = true;
		block_group[0][0]->color = color;
		block_group[0][1]->is_block = true;
		block_group[0][1]->color = color;
		block_group[0][2]->is_block = true;
		block_group[0][2]->color = color;
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

		if (button_down == UP) {
			rotate();
		}

		if (button_down == DOWN) {
			moveDown();
		}

		if (button_down == LEFT) {
			moveLeft();
		}

		if (button_down == RIGHT) {
			moveRight();
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

// 以行列偏移量（deltaRow, deltaColumn）为参数，用于在移动或旋转方块之前进行检测。
// 当准备向某个方向（左、右、下）移动或在旋转后变换坐标时，
// 只需根据新坐标计算出相对于当前坐标的偏移（或新位置），然后调用该函数检查是否有碰撞。
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



void Frame::moveLeft() {
	// 检查向左移动是否有碰撞
	// deltaRow = 0, deltaColumn = -1 表示尝试向左一格的位置
	if (checkCollision(0, -1)) {
		// 有碰撞则直接返回，不移动
		return;
	}

	// 无碰撞，可以左移
	for (auto& row_vec : block_group) {
		for (auto& b : row_vec) {
			if (b->is_block) {
				b->column -= 1; // 左移一格
			}
		}
	}
}

void Frame::moveRight() {
	// 检查向右移动是否有碰撞
	// deltaRow = 0, deltaColumn = 1 表示尝试向右一格的位置
	if (checkCollision(0, 1)) {
		// 有碰撞则直接返回，不移动
		return;
	}

	// 无碰撞，可以右移
	for (auto& row_vec : block_group) {
		for (auto& b : row_vec) {
			if (b->is_block) {
				b->column += 1; // 右移一格
			}
		}
	}
}



void Frame::moveDown() {
	// 检查向下移动是否有碰撞
	// deltaRow = 1, deltaColumn = 0 表示尝试向下移动一格的位置
	if (checkCollision(1, 0)) {
		// 有碰撞则直接返回，不移动
		return;
	}

	// 无碰撞，可以下移
	for (auto& row_vec : block_group) {
		for (auto& b : row_vec) {
			if (b->is_block) {
				b->row += 1; // 下移一格
			}
		}
	}
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


void Frame::moveToLowestPosition()
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
}

