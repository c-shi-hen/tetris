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

// 运行游戏
void runGame(Begin_frame* begin_frame) {

    Frame* myFrame = new Frame(begin_frame->animation, begin_frame);
    SetWindowText(initgraph(myFrame->frame_width, myFrame->frame_height), L"俄罗斯方块");
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
            runGame(begin_frame);
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
            EndBatchDraw();
            
            closegraph();
            if (begin_frame->createConfig()) {
                std::cout << "新配置创建成功。" << std::endl;
            }
            else {
                std::cout << "新配置创建失败或取消。" << std::endl;
                
            }
            // 返回主菜单界面
            begin_frame->menuMsg.createConfig = false;
            begin_frame->initial();
            continue;
        }

        // 加载配置文件
        if (begin_frame->menuMsg.loadConfig) {
            EndBatchDraw();
            closegraph();
            
            std::string filename;
            std::cout << "请输入要加载的配置文件名（不包括路径,后缀，直接输入文件名，输入 'q' 退出）：";
            bool is_load = false;
            while (std::cin >> filename) {
                if (filename == "q") {
                    std::cout << "取消加载配置。" << std::endl;
                    break;
                }else {
                    std::string filepath = configDir + "/" + filename + ".config";
                    if (begin_frame->loadConfig(filepath)) {
                        std::cout << "配置文件加载成功：" << filepath << std::endl;
                        std::cout << "启动游戏" << filepath << std::endl;
                        is_load = true;
                        break;
                    }else {
                        std::cout << "配置文件加载失败。" << std::endl;
                    }
                }
                std::cout << "请输入要加载的配置文件名（不包括路径,后缀，直接输入文件名，输入 'q' 退出）：";
            }
            //加载成功，开始游戏
            if (is_load) runGame(begin_frame);
            // 返回主菜单界面
            begin_frame->menuMsg.loadConfig = false;
            begin_frame->initial();
            continue;
        }

        // 创建残局
        if (begin_frame->menuMsg.createEndGame) {
            EndBatchDraw();
            closegraph();
            
            EndGame endGame(animation); // 传递 Animation 对象
            if (endGame.createEndGame()) {
                std::cout << "残局创建完成。" << std::endl;
            }
            else {
                std::cout << "残局创建失败或取消。" << std::endl;
            }

            // 返回主菜单界面
            begin_frame->menuMsg.createEndGame = false;
            begin_frame->initial();
            continue;
        }

        // 加载残局并挑战
        if (begin_frame->menuMsg.challengeEndGame) {
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