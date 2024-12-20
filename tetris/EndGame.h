#pragma once
#include <string>
#include <vector>
#include "Frame.h" 
#include "Block.h"


#include <string>
#include <vector>

class EndGame {
private:
    int mapWidth;        // 地图宽度
    int mapHeight;       // 地图高度
    int initialLevel;    // 初始关卡
    int initialSpeed;    // 初始速度

    std::vector<std::vector<bool>> map;           // 地图状态
    std::vector<std::vector<int>> blockColors;   // 方块颜色

    // 验证残局是否合法
    bool isValid() const;

    // 更新地图的状态，输出到控制台
    void updateFrame(int x, int y, bool placed, char type);

public:
    EndGame();

    // 创建残局
    bool createEndGame();

    // 保存残局到文件
    bool saveToFile(const std::string& filename) const;

    // 从文件加载残局
    bool loadFromFile(const std::string& filename);
};