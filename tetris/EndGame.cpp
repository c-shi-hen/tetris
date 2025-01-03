#include "EndGame.h"
#include <iostream>
#include <fstream>
#include <regex>
#include <easyx.h>

EndGame::EndGame(int map_height, int map_width, int level, std::vector<std::vector<bool>> map, std::vector<std::vector<int>> blockColors) {
    this->mapHeight = map_height;
    this->mapWidth = map_width;
    this->initialLevel = level;
    this->map = map;
    this->blockColors = blockColors;
}

EndGame::EndGame(Animation* animation) {
    //获取图片资源
    this->animation = animation;
}

EndGame::~EndGame() {

}

bool EndGame::isValid() const {
    return (mapWidth >= 8 && mapWidth <= 20) &&
        (mapHeight >= 8 && mapHeight <= 20) &&
        (initialLevel >= 1) &&
        (map.size() == static_cast<size_t>(mapHeight)) &&
        (blockColors.size() == static_cast<size_t>(mapHeight)) &&
        (mapWidth == blockColors[0].size());
}

void EndGame::visualizeEndGame() {
    // 初始化图形窗口的大小
    int blockWidth = Block::block_width;
    int blockHeight = Block::block_height;
    int windowWidth = mapWidth * blockWidth;
    int windowHeight = mapHeight * blockHeight;

    // 初始化图形窗口
    HWND hwnd = initgraph(windowWidth, windowHeight);
    SetWindowText(hwnd, L"残局地图编辑器");

    // 获取屏幕的宽度和高度
    RECT desktopRect;
    GetWindowRect(GetDesktopWindow(), &desktopRect);
    int screenWidth = desktopRect.right;
    int screenHeight = desktopRect.bottom;

    // 设置图形窗口的位置，靠屏幕左边，垂直居中
    int windowX = 35;  // 距离屏幕左边 35 像素
    int windowY = (screenHeight - windowHeight) / 2; // 垂直居中

    SetWindowPos(hwnd, HWND_TOP, windowX, windowY, 0, 0, SWP_NOSIZE | SWP_NOZORDER);

    // 显示并调整控制台窗口
    HWND consoleWnd = GetConsoleWindow();
    ShowWindow(consoleWnd, SW_SHOWNORMAL); // 确保控制台窗口可见

    // 设置控制台窗口的位置和大小
    int consoleWidth = screenWidth / 3;  // 设置控制台宽度为屏幕宽度的三分之一
    int consoleHeight = screenHeight / 2; // 设置控制台高度为屏幕高度的一半
    int consoleX = screenWidth - consoleWidth - 10; // 控制台位于屏幕右侧，距离右边框10像素
    int consoleY = (screenHeight - consoleHeight) / 2; // 控制台垂直居中

    // 调整控制台窗口的位置和大小
    SetWindowPos(consoleWnd, HWND_TOP, consoleX, consoleY, consoleWidth, consoleHeight, SWP_NOZORDER);



    // 开始绘制内容
    cleardevice();

    // 绘制背景
    putimage(0, 0, &animation->back_ground);

    // 绘制每个方块
    for (int row = 0; row < mapHeight; ++row) {
        for (int col = 0; col < mapWidth; ++col) {
            if (map[row][col]) {
                Block tempBlock(row, col, &animation->block_png);
                tempBlock.is_block = true;
                tempBlock.color = blockColors[row][col];
                tempBlock.show();
            }
        }
    }

    // 绘制网格线
    setlinecolor(WHITE);
    for (int i = 0; i <= mapWidth; ++i) {
        line(i * blockWidth, 0, i * blockWidth, mapHeight * blockHeight);
    }
    for (int i = 0; i <= mapHeight; ++i) {
        line(0, i * blockHeight, mapWidth * blockWidth, i * blockHeight);
    }

    FlushBatchDraw();
}

bool EndGame::createEndGame(std::string &endGameName) {

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
        visualizeEndGame(); // 实时可视化地图

        std::cout << "请输入指令（P X Y Type 放置方块，D X Y 删除方块，f 保存并退出，q 取消）：";
        std::string cmd;
        std::cin >> cmd;

        if (cmd == "P") {
            int x, y;
            char type;
            std::cin >> x >> y >> type;
            if (x >= 1 && x <= mapWidth && y >= 1 && y <= mapHeight) {
                map[y - 1][x - 1] = true;
                blockColors[y - 1][x - 1] = type - '0';

                visualizeEndGame(); // 更新界面

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

                visualizeEndGame(); // 更新界面

            }
            else {
                std::cout << "位置超出范围！" << std::endl;
            }
        }
        else if (cmd == "f") {
            std::string filePath = endGameName;
            if (saveToFile(filePath)) {
                std::cout << "残局保存成功: " << filePath << std::endl;
                closegraph(); // 关闭图形界面
                return true;
            }
            else {
                std::cout << "保存失败！" << std::endl;
                return false;
            }
        }
        else if (cmd == "q") {
            std::cout << "取消创建残局。" << std::endl;
            closegraph(); // 关闭图形界面
            return false;
        }
        else {
            std::cout << "无效的指令！" << std::endl;
        }
    }
}

bool EndGame::saveToFile(const std::string& filename) const {

    std::ofstream ofs("endgames/" + filename + ".end");
    if (!ofs.is_open()) {
        return false;
    }

    ofs << mapWidth << " " << mapHeight << "\n";
    ofs << initialLevel << "\n";

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

    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cout << "无法打开文件：" << filename << std::endl;
        return false;
    }

    file >> mapWidth >> mapHeight >> initialLevel;

    // 初始化地图
    map.assign(mapHeight, std::vector<bool>(mapWidth, false));
    blockColors.assign(mapHeight, std::vector<int>(mapWidth, -1));

    std::string command;
    while (file >> command) {
        if (command == "P") {
            int x, y, color;
            file >> x >> y >> color;
            map[y - 1][x - 1] = true;
            blockColors[y - 1][x - 1] = color;
        }
        else if (command == "f") {
            break; // 结束指令
        }
    }

    file.close();
    return true;
}
