//#include "EndGame.h"
//#include <fstream>
//#include <iostream>
//#include <regex>
//#include <filesystem>
//#include <cstdlib>
//
//namespace fs = std::filesystem;
//
//// 构造函数，初始化默认值
//EndGame::EndGame()
//    : mapWidth(10), mapHeight(20), initialLevel(1),
//    map(20, std::vector<bool>(10, false)),
//    blockColors(20, std::vector<int>(10, -1)) {}
//
//// 验证残局的合法性
//bool EndGame::isValid() const {
//    return (mapWidth >= 8 && mapWidth <= 20) &&
//        (mapHeight >= 8 && mapHeight <= 20) &&
//        (initialLevel >= 1) &&
//        (map.size() == static_cast<size_t>(mapHeight)) &&
//        (blockColors.size() == static_cast<size_t>(mapHeight)) &&
//        (mapWidth == blockColors[0].size());
//}
//
//// 保存残局到文件
//bool EndGame::saveToFile(const std::string& filename) const {
//    std::ofstream ofs(filename, std::ios::out);
//    if (!ofs.is_open()) {
//        return false;
//    }
//
//    // 写入地图大小和初始关卡
//    ofs << mapWidth << " " << mapHeight << "\n";
//    ofs << initialLevel << "\n";
//
//    // 写入地图和方块颜色
//    for (int y = 0; y < mapHeight; ++y) {
//        for (int x = 0; x < mapWidth; ++x) {
//            if (map[y][x]) {
//                ofs << "P " << x + 1 << " " << y + 1 << " " << blockColors[y][x] << "\n";
//            }
//        }
//    }
//
//    ofs << "f\n"; // 结束标志
//    ofs.close();
//    return true;
//}
//
//// 从文件加载残局
//bool EndGame::loadFromFile(const std::string& filename) {
//    std::ifstream ifs(filename, std::ios::in);
//    if (!ifs.is_open()) {
//        return false;
//    }
//
//    // 读取地图大小
//    ifs >> mapWidth >> mapHeight;
//    if (ifs.fail() || mapWidth < 8 || mapWidth > 20 || mapHeight < 8 || mapHeight > 20) {
//        ifs.close();
//        return false;
//    }
//
//    // 读取初始关卡
//    ifs >> initialLevel;
//    if (ifs.fail() || initialLevel < 1) {
//        ifs.close();
//        return false;
//    }
//
//    // 初始化地图和方块颜色二维数组
//    map.assign(mapHeight, std::vector<bool>(mapWidth, false));
//    blockColors.assign(mapHeight, std::vector<int>(mapWidth, -1));
//
//    // 读取方块信息
//    std::string command;
//    int x, y, color;
//    while (ifs >> command) {
//        if (command == "f") {
//            break;
//        }
//        else if (command == "P") {
//            ifs >> x >> y >> color;
//            if (ifs.fail() || x < 1 || x > mapWidth || y < 1 || y > mapHeight || color < 0) {
//                ifs.close();
//                return false;
//            }
//            map[y - 1][x - 1] = true;
//            blockColors[y - 1][x - 1] = color;
//        }
//        else {
//            // 未知命令
//            ifs.close();
//            return false;
//        }
//    }
//
//    ifs.close();
//    return isValid();
//}
//
//// 显示当前地图状态
//void EndGame::displayMap(const Frame& frame) const {
//    frame.displayMap();
//}
//
//// 获取方块颜色
//int EndGame::getBlockColor() const {
//    // 简单随机颜色选择，假设颜色索引从0开始
//    return rand() % 7; // 假设有7种颜色
//}
//
//// 创建新的残局（用户交互）
//bool EndGame::createEndGame(Frame& frame) {
//    std::string endGameName;
//    std::cout << "请输入残局文件名称（仅限英文字母、数字和下划线，输入 'q' 取消）：";
//    std::cin >> endGameName;
//
//    if (endGameName == "q") {
//        std::cout << "取消创建残局。" << std::endl;
//        return false;
//    }
//
//    // 验证文件名
//    std::regex validNameRegex("^[A-Za-z0-9_]+$");
//    if (!std::regex_match(endGameName, validNameRegex)) {
//        std::cout << "残局文件名称无效。只能包含英文字母、数字和下划线。" << std::endl;
//        return false;
//    }
//
//    // 输入地图大小
//    while (true) {
//        std::cout << "请输入地图大小（横向格子数 8-20，纵向格子数 8-20）：";
//        std::cin >> mapWidth >> mapHeight;
//        if (std::cin.fail() ||
//            mapWidth < 8 || mapWidth > 20 ||
//            mapHeight < 8 || mapHeight > 20) {
//            std::cin.clear(); // 清除错误标志
//            std::cin.ignore(10000, '\n'); // 忽略错误输入
//            std::cout << "输入无效，请输入两个8到20的正整数。" << std::endl;
//        }
//        else {
//            break;
//        }
//    }
//
//    // 输入初始关卡
//    while (true) {
//        std::cout << "请输入初始关卡数（正整数）：";
//        std::cin >> initialLevel;
//        if (std::cin.fail() || initialLevel < 1) {
//            std::cin.clear();
//            std::cin.ignore(10000, '\n');
//            std::cout << "输入无效，请输入一个正整数。" << std::endl;
//        }
//        else {
//            break;
//        }
//    }
//
//    // 清屏并绘制空白地图
//    system("cls");
//    std::cout << "当前地图大小：" << mapWidth << "x" << mapHeight << "\n";
//    std::cout << "当前初始关卡：" << initialLevel << "\n";
//    std::cout << "使用以下指令进行方块堆叠：" << std::endl;
//    std::cout << "• P X Y ：在位置 (X,Y) 处放置一个方块单元。" << std::endl;
//    std::cout << "• D X Y ：删除位置 (X,Y) 处的方块单元。" << std::endl;
//    std::cout << "• f ：结束残局创建，并保存残局文件。" << std::endl;
//    std::cout << "• q ：取消残局创建，返回主界面。" << std::endl;
//
//    // 清除 Frame 的地图
//    frame.clearMap(mapHeight, mapWidth);
//    map.assign(mapHeight, std::vector<bool>(mapWidth, false));
//    blockColors.assign(mapHeight, std::vector<int>(mapWidth, -1));
//
//    // 显示初始地图状态
//    displayMap(frame);
//
//    // 处理用户指令
//    while (true) {
//        std::cout << "请输入指令：";
//        std::string cmd;
//        std::cin >> cmd;
//
//        if (cmd == "P") {
//            int x, y;
//            std::cin >> x >> y;
//            if (std::cin.fail() ||
//                x < 1 || x > mapWidth ||
//                y < 1 || y > mapHeight) {
//                std::cin.clear();
//                std::cin.ignore(10000, '\n');
//                std::cout << "无效位置，请输入合法的 X 和 Y 值。" << std::endl;
//                continue;
//            }
//            if (map[y - 1][x - 1]) {
//                std::cout << "该位置已有方块，无法重复放置。" << std::endl;
//                continue;
//            }
//            // 设置方块
//            map[y - 1][x - 1] = true;
//            blockColors[y - 1][x - 1] = getBlockColor();
//            // 更新 Frame 的地图
//            frame.setBlock(x, y, true);
//            frame.setBlockColor(x, y, blockColors[y - 1][x - 1]);
//            // 显示地图
//            displayMap(frame);
//        }
//        else if (cmd == "D") {
//            int x, y;
//            std::cin >> x >> y;
//            if (std::cin.fail() ||
//                x < 1 || x > mapWidth ||
//                y < 1 || y > mapHeight) {
//                std::cin.clear();
//                std::cin.ignore(10000, '\n');
//                std::cout << "无效位置，请输入合法的 X 和 Y 值。" << std::endl;
//                continue;
//            }
//            if (!map[y - 1][x - 1]) {
//                std::cout << "该位置没有方块，无法删除。" << std::endl;
//                continue;
//            }
//            // 删除方块
//            map[y - 1][x - 1] = false;
//            blockColors[y - 1][x - 1] = -1;
//            // 更新 Frame 的地图
//            frame.setBlock(x, y, false);
//            frame.setBlockColor(x, y, -1);
//            // 显示地图
//            displayMap(frame);
//        }
//        else if (cmd == "f") {
//            // 保存残局文件
//            std::string endGameFilePath = "endgames/" + endGameName + ".end";
//            // 确保 endgames 目录存在
//            if (!fs::exists("endgames")) {
//                if (!fs::create_directory("endgames")) {
//                    std::cout << "无法创建 'endgames' 目录。" << std::endl;
//                    return false;
//                }
//            }
//            if (!saveToFile(endGameFilePath)) {
//                std::cout << "保存残局文件失败。" << std::endl;
//                return false;
//            }
//            std::cout << "残局文件 '" << endGameName << ".end' 创建成功并保存。" << std::endl;
//            return true;
//        }
//        else if (cmd == "q") {
//            std::cout << "取消创建残局，返回主界面。" << std::endl;
//            return false;
//        }
//        else {
//            std::cout << "未知指令，请输入 'P', 'D', 'f' 或 'q'。" << std::endl;
//        }
//    }
//}
//
//// 应用残局到 Frame
//void EndGame::applyToFrame(Frame& frame) const {
//    if (!isValid()) {
//        std::cerr << "加载的残局无效！" << std::endl;
//        return;
//    }
//
//    // 设置地图大小和初始关卡
//    frame.clearMap(mapHeight, mapWidth);
//    frame.initialLevel = initialLevel;
//    frame.gameSpeed = initialLevel; // 假设关卡数决定游戏速度，可以根据实际逻辑调整
//
//    // 设置方块位置和颜色
//    for (int y = 0; y < mapHeight; ++y) {
//        for (int x = 0; x < mapWidth; ++x) {
//            if (map[y][x]) {
//                frame.setBlock(x + 1, y + 1, true); // 转换为1-based索引
//                frame.setBlockColor(x + 1, y + 1, blockColors[y][x]);
//            }
//        }
//    }
//
//    // 显示应用后的地图
//    frame.displayMap();
//}
