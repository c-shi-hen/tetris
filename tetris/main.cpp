#include<easyx.h>
#include"Frame.h"
#include"Begin_frame.h"
#include"Animation.h"
#include "EndGame.h"
#include <iostream>
#include <windows.h> 
#include <tchar.h>   
#include <filesystem> 

namespace fs = std::filesystem;

// 显示控制台
void showConsole() {
    AllocConsole();  // 分配控制台窗口

    FILE* pFile;
    freopen_s(&pFile, "CONOUT$", "w", stdout); // 重定向标准输出到控制台

    // 获取控制台窗口句柄
    HWND consoleWnd = GetConsoleWindow();
    if (consoleWnd == nullptr) {
        return; // 如果控制台窗口句柄为空，则返回
    }

    // 显示控制台窗口
    ShowWindow(consoleWnd, SW_SHOWNORMAL);

    // 获取屏幕分辨率
    RECT desktopRect;
    GetWindowRect(GetDesktopWindow(), &desktopRect);
    int screenWidth = desktopRect.right;
    int screenHeight = desktopRect.bottom;

    // 设置控制台窗口的位置和大小
    int consoleWidth = screenWidth / 3;  // 设置控制台宽度
    int consoleHeight = screenHeight / 2; // 设置控制台高度为屏幕高度的一半
    int consoleX = screenWidth - consoleWidth - 10; // 控制台位于屏幕右侧，距离右边框50像素
    int consoleY = (screenHeight - consoleHeight) / 2; // 控制台垂直居中

    // 调整控制台窗口的位置和大小
    SetWindowPos(consoleWnd, HWND_TOP, consoleX, consoleY, consoleWidth, consoleHeight, SWP_NOZORDER);

    // 将控制台窗口置于最前端
    SetForegroundWindow(consoleWnd);
}

// 隐藏控制台
void hideConsole() {

    // 隐藏控制台
    ShowWindow(GetConsoleWindow(), SW_HIDE);
}

// 运行游戏
void runGame(Begin_frame* begin_frame) {

    Frame* myFrame = new Frame(begin_frame->animation, begin_frame);

    HWND hwnd = initgraph(myFrame->frame_width, myFrame->frame_height);
    SetWindowText(hwnd, L"俄罗斯方块");

    RECT desktopRect;
    GetWindowRect(GetDesktopWindow(), &desktopRect);
    int screenWidth = desktopRect.right;
    int screenHeight = desktopRect.bottom;
    int windowX = (screenWidth - myFrame->frame_width) / 2;
    int windowY = (screenHeight - myFrame->frame_height) / 2;
    SetWindowPos(hwnd, HWND_TOP, windowX, windowY, 0, 0, SWP_NOSIZE | SWP_NOZORDER);

    BeginBatchDraw();
    myFrame->game_begin();
    EndBatchDraw();
    closegraph();

    delete(myFrame);
}

int main() {
    // 确保 config 和 endgames 目录存在
    const std::string configDir = "config";
    const std::string endgameDir = "endgames";
    if (!fs::exists(configDir) && !fs::create_directories(configDir)) {
        std::cout << "无法创建 'config' 目录。" << std::endl;
        return 1;
    }
    if (!fs::exists(endgameDir) && !fs::create_directories(endgameDir)) {
        std::cout << "无法创建 'endgames' 目录。" << std::endl;
        return 1;
    }

    //初始化资源类
    Animation* animation = new Animation();

    Begin_frame* begin_frame = new Begin_frame(animation);

    // 初始化主菜单界面
    begin_frame->initial();


    //开始读取消息
    while (true) {

        // 获取用户输入
        begin_frame->getMainMenuMessage(begin_frame->menuMsg);

        // 开始游戏
        if (begin_frame->menuMsg.startGame) {
            EndBatchDraw();
            closegraph();

            // 启动游戏
            runGame(begin_frame);

            // 初始化主菜单
            begin_frame->initial();
            begin_frame->menuMsg.startGame = false;
            continue;
        }

        //退出游戏
        if (begin_frame->menuMsg.quitGame) {
            EndBatchDraw();
            closegraph();
            std::cout << "退出游戏。" << std::endl;
            begin_frame->menuMsg.quitGame = false;
            break;
        }

        // 新建配置文件
        if (begin_frame->menuMsg.createConfig) {
            showConsole();
            EndBatchDraw();
            closegraph();

            std::string filename;
            std::cout << "请输入新配置文件名称（仅限字母、数字和下划线，输入 'q' 退出）：";
            while (std::cin >> filename) {
                if (filename == "q") {
                    std::cout << "取消新建配置。\n";
                    break;
                }
                else {
                    if (begin_frame->createConfig(filename)) {
                        std::cout << "新配置创建成功。" << std::endl;
                    }
                    else {
                        std::cout << "新配置创建失败，请再试一次。" << std::endl;
                    }
                }
                std::cout << "请输入新配置文件名称（仅限字母、数字和下划线，输入 'q' 退出）：";
            }

            // 返回主菜单界面
            hideConsole();
            begin_frame->menuMsg.createConfig = false;
            begin_frame->initial();
            continue;
        }

        // 加载配置文件
        if (begin_frame->menuMsg.loadConfig) {
            showConsole();
            EndBatchDraw();
            closegraph();

            std::string filename;
            std::cout << "请输入要加载的配置文件名（不包括路径,后缀，直接输入文件名，输入 'q' 退出）：";
            bool is_load = false;
            while (std::cin >> filename) {
                if (filename == "q") {
                    std::cout << "取消加载配置。" << std::endl;
                    break;
                }
                else {
                    std::string filepath = "config/" + filename + ".config";
                    if (begin_frame->loadConfig(filepath)) {
                        std::cout << "配置文件加载成功：" << filepath << std::endl;
                        is_load = true;

                        // 保存当前配置到 last.config
                        if (begin_frame->saveLastConfig()) {
                            std::cout << "当前配置已同时复制到到 last.config。" << std::endl;
                        }
                        else {
                            std::cout << "复制到 last.config 失败！" << std::endl;
                        }
                        break;
                    }
                    else {
                        std::cout << "配置文件加载失败。" << std::endl;
                    }
                }
                std::cout << "请输入要加载的配置文件名（不包括路径,后缀，直接输入文件名，输入 'q' 退出）：";
            }

            // 如果加载成功，启动游戏
            hideConsole();
            if (is_load) runGame(begin_frame);

            // 返回主菜单界面
            begin_frame->menuMsg.loadConfig = false;
            begin_frame->initial();
            continue;
        }

        // 创建残局
        if (begin_frame->menuMsg.createEndGame) {
            showConsole();
            EndBatchDraw();
            closegraph();
            
            std::string filename;
            std::cout << "请输入残局文件名称（仅限英文字母、数字和下划线，输入 'q' 取消）：";
            while (std::cin >> filename) {
                if (filename == "q") {
                    std::cout << "取消创建残局。" << std::endl;
                    break;
                }
                else {
                    EndGame endGame(animation); // 传递 Animation 对象
                    if (endGame.createEndGame(filename)) {
                        std::cout << "残局创建完成。" << std::endl;
                    }
                    else {
                        std::cout << "残局创建失败，请再试一次。" << std::endl;
                    }
                }
                std::cout << "请输入要加载的配置文件名（不包括路径,后缀，直接输入文件名，输入 'q' 退出）：";
            }
            

            // 返回主菜单界面
            hideConsole();
            begin_frame->menuMsg.createEndGame = false;
            begin_frame->initial();
            continue;
        }

        // 加载残局并挑战
        if (begin_frame->menuMsg.challengeEndGame) {
            showConsole();
            EndBatchDraw();
            closegraph();

            std::string endGameFile;
            std::cout << "请输入要加载的残局文件名（不包括路径,后缀，直接输入文件名，输入 'q' 退出）：";
            bool is_load = false;
            while (std::cin >> endGameFile) {
                if (endGameFile == "q") {
                    std::cout << "取消加载残局。" << std::endl;
                    break;
                }

                std::string filepath = endgameDir + "/" + endGameFile + ".end";
                EndGame endGame(animation);
                if (endGame.loadFromFile(filepath)) {
                    std::cout << "残局加载成功：" << filepath << std::endl;
                    is_load = true;
                    //将相关参数传递给主菜单
                    begin_frame->map = endGame.map;
                    begin_frame->blockColors = endGame.blockColors;
                    begin_frame->map_height = endGame.mapHeight;
                    begin_frame->map_width = endGame.mapWidth;
                    begin_frame->initialLevel = endGame.initialLevel;

                    break; // 退出主菜单循环
                }
                else {
                    std::cout << "残局加载失败，文件可能不存在或格式错误。" << std::endl;
                }
                std::cout << "请输入要加载的残局文件名（不包括路径,后缀，直接输入文件名，输入 'q' 退出）：";
            }
            //加载成功，启动游戏
            hideConsole();
            if (is_load) runGame(begin_frame);
            begin_frame->menuMsg.challengeEndGame = false;
            begin_frame->initial();

            continue;
        }
        FlushBatchDraw();

        Sleep(20);
    }

    delete begin_frame;
    delete animation;
    return 0;
}
