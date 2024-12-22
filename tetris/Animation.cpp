#include "Animation.h"

Animation::Animation() {
	load_block_group_png();
	load_block_png();
}

Animation::~Animation(){

}

void Animation::load_block_png() {
	IMAGE* temp = new IMAGE();
	loadimage(temp, _T("./res/blue.png"));
	block_png.push_back(temp);

	temp = new IMAGE();
	loadimage(temp, _T("./res/green.png"));
	block_png.push_back(temp);

	temp = new IMAGE();
	loadimage(temp,  _T("./res/light_blue.png"));
	block_png.push_back(temp);

	temp = new IMAGE();
	loadimage(temp, _T("./res/orange.png"));
	block_png.push_back(temp);

	temp = new IMAGE();
	loadimage(temp, _T("./res/purple.png"));
	block_png.push_back(temp);

	temp = new IMAGE();
	loadimage(temp, _T("./res/yellow.png"));
	block_png.push_back(temp);
}

void Animation::load_block_group_png() {
	//加载背景图片
	loadimage(&back_ground, _T("./res/background.png"));

	//加载方块组合照片,顺序和方块组合的顺序一致
	IMAGE* temp = new IMAGE();
	loadimage(temp, _T("./res/S.png"));
	block_group_png.push_back(temp);

	temp = new IMAGE();
	loadimage(temp, _T("./res/Z.png"));
	block_group_png.push_back(temp);

	temp = new IMAGE();
	loadimage(temp, _T("./res/L.png"));
	block_group_png.push_back(temp);

	temp = new IMAGE();
	loadimage(temp, _T("./res/J.png"));
	block_group_png.push_back(temp);

	temp = new IMAGE();
	loadimage(temp, _T("./res/I.png"));
	block_group_png.push_back(temp);

	temp = new IMAGE();
	loadimage(temp, _T("./res/O.png"));
	block_group_png.push_back(temp);

	temp = new IMAGE();
	loadimage(temp, _T("./res/T.png"));
	block_group_png.push_back(temp);
}