#include"Block.h"
#include"Begin_frame.h"
/*
* @param row : 该方块的行序号， column : 该方块的列数序号；均以0开始
*/
Block::Block(int row, int column){
	//存储初始化时行和列
	this->row = row;
	this->column = column;
	load_image();  // 加载方块的图片
}

Block::~Block(){

}

void Block::show() {
	//确保存在方块
	if (is_block) {
		int x_axis = block_width * column;
		int y_axis = block_height * row;
		putimage(x_axis, y_axis, &block_png[color]);
	}
}

// 加载方块图片
void Block::load_image(){
	loadimage(&block_png[0], _T("../res/blue.png"));
	loadimage(&block_png[1], _T("../res/green.png"));
	loadimage(&block_png[2], _T("../res/light_blue.png"));
	loadimage(&block_png[3], _T("../res/orange.png"));
	loadimage(&block_png[4], _T("../res/purple.png"));
	loadimage(&block_png[5], _T("../res/yellow.png"));
}
