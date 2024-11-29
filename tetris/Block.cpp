#include"Block.h"
#include"Begin_frame.h"
/*
* @param row : 该方块的行序号， column : 该方块的列数序号；均以0开始
*/
Block::Block(int row, int column, BlockType type, map_size map){
	//存储初始化时行和列
	this->row = row;
	this->column = column;


    this->type = type;
    this->game_map = map;  // 设置游戏地图的大小
	this->is_block = true;  // 设置方块存在
	this->color = BLOCK_BLUE;  // 默认颜色为蓝色
	load_image();  // 加载方块的图片
	loadShape();   // 加载方块的形状
}

Block::~Block(){

}

/*
void Block::show() {
	//确保存在方块
	if (is_block) {
		int x_axis = block_width * column;
		int y_axis = block_height * row;
		putimage(x_axis, y_axis, &block_png[color]);
	}

}
*/


// 绘制方块
//重新更新了下实现方法
void Block::show() {
    //确保存在方块
    if (is_block) {
        for (int i = 0; i < 4; ++i) {
            for (int j = 0; j < 4; ++j) {
                if (shape[i][j] == 1) {  // 只有形状中存在的位置才绘制
                    int x = column * block_width + j * block_width;
                    int y = row * block_height + i * block_height;
                    putimage(x, y, &block_png[color]);  // 使用 color 作为索引，不知道会不会有问题
                }
            }
        }
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



// 根据方块类型加载形状（默认是 I 方块）
void Block::loadShape() {
    // 清空方块形状数组
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            shape[i][j] = 0;
        }
    }

    // 根据方块类型初始化形状
    //先随便设了一下颜色，目前颜色的数量不够
    //感觉必须要用4x4的矩阵设置占位
    switch (type) {
    case S:
        color = BLOCK_GREEN;
        shape[0][1] = shape[0][2] = 1;
        shape[1][0] = shape[1][1] = 1;
        break;
    case Z:
        color = BLOCK_GREEN;
        shape[0][0] = shape[0][1] = 1;
        shape[1][1] = shape[1][2] = 1;
        break;
    case L:
        color = BLOCK_ORANGE;
        shape[0][0] = shape[1][0] = shape[2][0] = 1;
        shape[2][1] = 1;
        break;
    case J:
        color = BLOCK_BLUE;
        shape[0][1] = shape[1][1] = shape[2][1] = 1;
        shape[2][0] = 1;
        break;
    case I:
        color = BLOCK_LIGHT_BLUE;
        shape[0][0] = shape[0][1] = shape[0][2] = shape[0][3] = 1;
        break;
    case O:
        color = BLOCK_YELLOW;
        shape[0][0] = shape[0][1] = shape[1][0] = shape[1][1] = 1;
        break;
    case T:
        color = BLOCK_PURPLE;
        shape[0][0] = shape[0][1] = shape[0][2] = 1;
        shape[1][1] = 1;
        break;
    default:
        break;
    }
}



// 向左移动方块
void Block::moveLeft() {
    if (column > 0 && !checkCollision(row, column - 1)) {
        --column;  // 向左移动
    }
}

// 向右移动方块
void Block::moveRight() {
    if (column < game_map.map_width - 1 && !checkCollision(row, column + 1)) {
        ++column;  // 向右移动
    }
}

// 向下移动方块
void Block::moveDown() {
    if (row < game_map.map_height - 1 && !checkCollision(row + 1, column)) {
        ++row;  // 向下移动
    }
}

// 设置方块是否存在
void Block::setActive(bool active) {
    is_block = active;
}

// 检查是否与其他方块发生碰撞
//暂时只实现了是否会超出地图边界的检测
//之后可能需要定义一个二维数组，其中每个元素表示一个位置。如果某个位置有方块，它会指向一个方块对象。如果没有方块，则为 nullptr
bool Block::checkCollision(int targetRow, int targetColumn) {
    // 检查目标位置是否超出边界
    if (targetRow < 0 || targetRow >= game_map.map_height || targetColumn < 0 || targetColumn >= game_map.map_width) {
        return true;  // 超出边界，发生碰撞
    }

    return false;
}

// 旋转方块（顺时针90度）
void Block::rotate() {
    int temp[4][4];

    // 将当前的形状复制到临时数组
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            temp[i][j] = shape[i][j];
        }
    }

    // 顺时针旋转90度
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            shape[i][j] = temp[3 - j][i];
        }
    }

    // 检查旋转后的方块是否与其他方块发生碰撞
    if (checkCollision(row, column)) {
        // 如果发生碰撞，恢复到原始状态
        for (int i = 0; i < 4; ++i) {
            for (int j = 0; j < 4; ++j) {
                shape[i][j] = temp[i][j];
            }
        }
    }
}
