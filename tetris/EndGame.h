#pragma once
#include <string>
#include <vector>
#include "Block.h"
#include "Animation.h"

class EndGame {
public:
    int mapWidth;        // 地图宽度
    int mapHeight;       // 地图高度
    int initialLevel;    // 初始关卡
    std::vector<std::vector<bool>> map;           // 地图状态
    std::vector<std::vector<int>> blockColors;    // 方块颜色

    Animation* animation; // 动画资源

    // 验证残局是否合法
    bool isValid() const;

public:
    EndGame(Animation* animation);

    // 创建残局
    bool createEndGame();

    // 保存残局到文件
    bool saveToFile(const std::string& filename) const;

    // 从文件加载残局
    bool loadFromFile(const std::string& filename);

    // 可视化残局地图
    void visualizeEndGame();

    // 将残局数据应用到方块网格
    void applyToBlocks(std::vector<std::vector<Block*>>& blocks, int& level, int& speed);
};
