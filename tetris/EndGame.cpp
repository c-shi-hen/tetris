#include "EndGame.h"
#include <iostream>
#include <fstream>
#include <regex>

EndGame::EndGame()
    : mapWidth(10), mapHeight(20), initialLevel(1), initialSpeed(5),
    map(20, std::vector<bool>(10, false)),
    blockColors(20, std::vector<int>(10, -1)) {}

bool EndGame::isValid() const {
    return (mapWidth >= 8 && mapWidth <= 20) &&
        (mapHeight >= 8 && mapHeight <= 20) &&
        (initialLevel >= 1) &&
        (map.size() == static_cast<size_t>(mapHeight)) &&
        (blockColors.size() == static_cast<size_t>(mapHeight)) &&
        (mapWidth == blockColors[0].size());
}

void EndGame::updateFrame(int x, int y, bool placed, char type) {
    std::cout << "更新地图：";
    if (placed) {
        std::cout << "放置方块 (" << x << ", " << y << ", 类型: " << type << ")\n";
    }
    else {
        std::cout << "移除方块 (" << x << ", " << y << ")\n";
    }

    // 打印当前地图
    for (int i = 0; i < mapHeight; ++i) {
        for (int j = 0; j < mapWidth; ++j) {
            if (map[i][j]) {
                std::cout << 0 << " ";
            }
            else {
                std::cout << ". ";
            }
        }
        std::cout << "\n";
    }
}

bool EndGame::createEndGame() {
    std::string endGameName;
    std::cout << "请输入残局文件名称（仅限英文字母、数字和下划线，输入 'q' 取消）：";
    std::cin >> endGameName;

    if (endGameName == "q") {
        std::cout << "取消创建残局。" << std::endl;
        return false;
    }

    std::regex validNameRegex("^[A-Za-z0-9_]+$");
    if (!std::regex_match(endGameName, validNameRegex)) {
        std::cout << "残局文件名称无效。" << std::endl;
        return false;
    }

    // 输入地图大小
    while (true) {
        std::cout << "请输入地图大小（横向格子数 8-20，纵向格子数 8-20）：";
        std::cin >> mapWidth >> mapHeight;
        if (std::cin.fail() || mapWidth < 8 || mapWidth > 20 || mapHeight < 8 || mapHeight > 20) {
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            std::cout << "输入无效，请重新输入。" << std::endl;
        }
        else {
            break;
        }
    }

    // 输入初始关卡
    while (true) {
        std::cout << "请输入初始关卡数（正整数）：";
        std::cin >> initialLevel;
        if (std::cin.fail() || initialLevel < 1) {
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            std::cout << "输入无效，请重新输入。" << std::endl;
        }
        else {
            break;
        }
    }

    // 初始化地图
    map.assign(mapHeight, std::vector<bool>(mapWidth, false));
    blockColors.assign(mapHeight, std::vector<int>(mapWidth, -1));

    // 用户交互式编辑地图
    while (true) {
        std::cout << "请输入指令（P X Y Type 放置方块，D X Y 删除方块，f 保存并退出，q 取消）：";
        std::string cmd;
        std::cin >> cmd;

        if (cmd == "P") {
            int x, y;
            char type;
            std::cin >> x >> y >> type;
            if (x >= 1 && x <= mapWidth && y >= 1 && y <= mapHeight) {
                map[y - 1][x - 1] = true;
                blockColors[y - 1][x - 1] = type;

                // 调用更新方法
                updateFrame(x, y, true, type);
            }
            else {
                std::cout << "位置超出范围！" << std::endl;
            }
        }
        else if (cmd == "D") {
            int x, y;
            std::cin >> x >> y;
            if (x >= 1 && x <= mapWidth && y >= 1 && y <= mapHeight) {
                map[y - 1][x - 1] = false;
                blockColors[y - 1][x - 1] = -1;

                // 调用更新方法
                updateFrame(x, y, false, -1);
            }
            else {
                std::cout << "位置超出范围！" << std::endl;
            }
        }
        else if (cmd == "f") {
            std::string filePath = "endgames/" + endGameName + ".end";
            if (saveToFile(filePath)) {
                std::cout << "残局保存成功: " << filePath << std::endl;
                return true;
            }
            else {
                std::cout << "保存失败！" << std::endl;
                return false;
            }
        }
        else if (cmd == "q") {
            std::cout << "取消创建残局。" << std::endl;
            return false;
        }
        else {
            std::cout << "无效的指令！" << std::endl;
        }
    }
}

bool EndGame::saveToFile(const std::string& filename) const {
    std::ofstream ofs(filename);
    if (!ofs.is_open()) {
        return false;
    }

    ofs << mapWidth << " " << mapHeight << "\n";
    ofs << initialLevel << "\n";
    ofs << initialSpeed << "\n";

    for (int y = 0; y < mapHeight; ++y) {
        for (int x = 0; x < mapWidth; ++x) {
            if (map[y][x]) {
                ofs << "P " << x + 1 << " " << y + 1 << " " << blockColors[y][x] << "\n";
            }
        }
    }

    ofs << "f\n";
    return true;
}

bool EndGame::loadFromFile(const std::string& filename) {
    std::ifstream ifs(filename);
    if (!ifs.is_open()) {
        return false;
    }

    ifs >> mapWidth >> mapHeight >> initialLevel >> initialSpeed;
    if (ifs.fail() || mapWidth < 8 || mapWidth > 20 || mapHeight < 8 || mapHeight > 20 || initialLevel < 1 || initialSpeed < 1) {
        return false;
    }

    map.assign(mapHeight, std::vector<bool>(mapWidth, false));
    blockColors.assign(mapHeight, std::vector<int>(mapWidth, -1));

    std::string command;
    while (ifs >> command) {
        if (command == "f") {
            break;
        }
        else if (command == "P") {
            int x, y;
            char type;
            ifs >> x >> y >> type;
            if (x >= 1 && x <= mapWidth && y >= 1 && y <= mapHeight) {
                map[y - 1][x - 1] = true;
                blockColors[y - 1][x - 1] = type;
            }
        }
    }

    return true;
}
