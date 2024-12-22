#pragma once
#include <string>
#include <vector>
#include "Block.h"
#include "Animation.h"

class EndGame {

public:
    /*
    * @brief 游戏中生成残局
    */
    EndGame(int map_height, int map_width, int level, std::vector<std::vector<bool>> map, std::vector<std::vector<int>> blockColors);

    /*
    * @brief 手动创建残局
    */
    EndGame(Animation* animation);

    ~EndGame();

public:

    // 地图宽度
    int mapWidth;
    // 地图高度
    int mapHeight;
    // 初始关卡
    int initialLevel;

    // 地图状态
    std::vector<std::vector<bool>> map;     
    // 方块颜色
    std::vector<std::vector<int>> blockColors;    

    // 动画资源
    Animation* animation; 

public:

    /*
    * @brief 验证残局是否合法
    */
    bool isValid() const;

    /*
    * @brief 创建残局
    */
    bool createEndGame(std::string& endGameName);

    /*
    * @brief 保存残局到文件
    */
    bool saveToFile(const std::string& filename) const;

    /*
    * @brief 从文件加载残局
    */
    bool loadFromFile(const std::string& filename);

    /*
    * @brief 可视化残局地图
    */
    void visualizeEndGame();

};
