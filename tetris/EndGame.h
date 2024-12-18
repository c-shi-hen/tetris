#pragma once

#include <vector>
#include <string>
#include "Frame.h" 
class EndGame {
public:
    // 构造函数
    EndGame();

    // 验证残局的合法性
    bool isValid() const;

    // 保存残局到文件
    bool saveToFile(const std::string& filename) const;

    // 从文件加载残局
    bool loadFromFile(const std::string& filename);

    // 创建新的残局（用户交互）
    bool createEndGame(Frame& frame);

    // 应用残局到 Frame
    void applyToFrame(Frame& frame) const;

private:
    int mapWidth; // 横向格子数（8-20）
    int mapHeight; // 纵向格子数（8-20）
    int initialLevel; // 初始关卡（正整数）
    std::vector<std::vector<bool>> map; // 地图二维数组
    std::vector<std::vector<int>> blockColors; // 方块颜色二维数组

    // 显示当前地图状态
    void displayMap(const Frame& frame) const;

    // 获取方块颜色
    int getBlockColor() const;
};
