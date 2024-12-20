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
void runGame() {
    Animation* animation = new Animation();
    
    Begin_frame* my_begin_frame = new Begin_frame(animation);
    SetWindowText(initgraph(my_begin_frame->begin_frame_width, my_begin_frame->begin_frame_height), L"俄罗斯方块");
    my_begin_frame->initial();
    closegraph();
    
    
    Frame* myFrame = new Frame(animation, my_begin_frame);
    SetWindowText(initgraph(myFrame->frame_width, myFrame->frame_height), L"俄罗斯方块");
    BeginBatchDraw();
    myFrame->game_begin();
    EndBatchDraw();
    closegraph();
    
    delete(myFrame);
    delete(animation);
    delete(my_begin_frame);
    
}

int main() {
    // 确保 config 目录存在
    const std::string configDir = "config";
    if (!fs::exists(configDir) && !fs::create_directories(configDir)) {
        std::cerr << "无法创建 'config' 目录。" << std::endl;
        return 1;
    }

    // 初始化主菜单界面
    int menuWidth = 600;
    int menuHeight = 400;
    initgraph(menuWidth, menuHeight);
    SetWindowText(GetHWnd(), L"俄罗斯方块 - 主菜单");

    // 主菜单消息循环
    Begin_frame::MainMenuMessage menuMsg;
    Animation* animation0 = new Animation();
    Begin_frame* my_begin_frame0 = new Begin_frame(animation0);

    while (true) {
        my_begin_frame0->drawMainMenu();

        // 等待用户输入
        while (!my_begin_frame0->getMainMenuMessage(menuMsg)) {
            Sleep(10);
        }

        // 根据用户选择处理操作
        if (menuMsg.startGame) {
            closegraph();
            runGame();
            break;
        }

        if (menuMsg.quitGame) {
            closegraph();
            std::cout << "退出游戏。" << std::endl;
            break;
        }

        if (menuMsg.createConfig) {
            // 新建配置文件
            if (my_begin_frame0->createConfig()) {
                std::cout << "新配置创建成功。" << std::endl;
            }
            else {
                std::cout << "新配置创建失败或取消。" << std::endl;
            }

            // 返回主菜单界面
            break;
        }

        if (menuMsg.loadConfig) {
            // 加载配置文件
            std::string filename;
            std::cout << "请输入要加载的配置文件名（不包括路径,后缀，直接输入文件名，输入 'q' 退出）：";
            std::cin >> filename;

            if (filename == "q") {
                std::cout << "取消加载配置。" << std::endl;
                break;
            }
            else {
                std::string filepath = configDir + "/" + filename + ".config";
                if (my_begin_frame0->loadConfig(filepath)) {
                    std::cout << "配置文件加载成功：" << filepath << std::endl;

                    

                    // 启动游戏
                    Sleep(100);
                    closegraph(); // 关闭主菜单窗口
                    runGame();
                    break; // 退出主菜单循环
                }
                else {
                    std::cout << "配置文件加载失败。" << std::endl;
                }
            }

            // 返回主菜单界面
            continue;
        }

        // 重置消息状态
        menuMsg = {};
    }

    delete my_begin_frame0;
    delete animation0;
    return 0;
}