#include<easyx.h>
#include"Frame.h"
#include"Begin_frame.h"
#include"Animation.h"
#include "ConfigManager.h"
#include <iostream>
#include <windows.h> 
#include <tchar.h>   
#include <filesystem> 

namespace fs = std::filesystem;





int main()
{
	Animation* animation = new Animation();

	Begin_frame* my_begin_frame = new Begin_frame(animation);
	SetWindowText(initgraph( my_begin_frame->begin_frame_width, my_begin_frame->begin_frame_height), L"俄罗斯方块");
	my_begin_frame->initial();
	closegraph();
	
	
	Frame* myFrame = new Frame(my_begin_frame->map_width, my_begin_frame->map_height, animation);
	SetWindowText(initgraph(myFrame->frame_width, myFrame->frame_height), L"俄罗斯方块");
	BeginBatchDraw();
	myFrame->game_begin();
	EndBatchDraw();
	closegraph();

	delete(myFrame);
	delete(animation);
	delete(my_begin_frame);

	return 0;
}

/*
#define VK_G 0x47
#define VK_Q 0x51


// 定义 MainExMessage 结构体（用于主菜单消息处理）
struct MainExMessage {
    int message;
    int vkcode;
};

// 获取主菜单消息的函数
bool getMainMenuMessage(MainExMessage& msg) {
    MSG winMsg;
    if (PeekMessage(&winMsg, NULL, 0, 0, PM_REMOVE)) {
        msg.message = winMsg.message;
        msg.vkcode = winMsg.wParam;
        TranslateMessage(&winMsg);
        DispatchMessage(&winMsg);
        return true;
    }
    return false;
}


// 封装原有游戏代码到 runGame() 函数
void runGame()
{
    Begin_frame* my_begin_frame = new Begin_frame();
    SetWindowText(initgraph(my_begin_frame->begin_frame_width, my_begin_frame->begin_frame_height), L"俄罗斯方块");
    my_begin_frame->initial();
    closegraph();

    Animation* animation = new Animation();
    Frame* myFrame = new Frame(my_begin_frame->default_map_size.map_height, my_begin_frame->default_map_size.map_width, animation);
    SetWindowText(initgraph(myFrame->frame_width, myFrame->frame_height), L"俄罗斯方块");
    BeginBatchDraw();
    myFrame->game_begin();
    EndBatchDraw();
    closegraph();

    delete(myFrame);
    delete(animation);
    delete(my_begin_frame);

    
}


int main()
{
    // 确保 config 目录存在
    if (!createDirectoryIfNotExists("config")) {
        std::cerr << "无法创建 'config' 目录。" << std::endl;
        return 1;
    }

    // 加载最后使用的配置
    Config currentConfig;
    loadLastConfig(currentConfig);

    // 显示主菜单并获取玩家选择
    while (true) {
        // 初始化主界面窗口
        int menuWidth = 600;  // 根据需要调整
        int menuHeight = 400; // 根据需要调整
        HWND menuHwnd = initgraph(menuWidth, menuHeight, 1); // 使用 1 代替 SHOWCONSOLE
        if (menuHwnd == INVALID_HANDLE_VALUE) {
            std::cerr << "主界面窗口初始化失败！" << std::endl;
            return 1;
        }

        // 设置窗口标题
        SetWindowText(menuHwnd, L"俄罗斯方块 - 主菜单");

        // 清除屏幕并绘制主界面内容
        cleardevice();
        settextstyle(48, 0, _T("Arial"));
        settextcolor(YELLOW);

        TCHAR title[] = _T("欢迎来到俄罗斯方块");
        TCHAR prompt1[] = _T("按 'G' 开始游戏");
        TCHAR prompt2[] = _T("按 'Q' 退出游戏");
        TCHAR prompt3[] = _T("按 'I' 新建配置");
        TCHAR prompt4[] = _T("按 'U' 加载配置");

        // 计算文本位置以居中显示
        int titleWidth = textwidth(title);
        int prompt1Width = textwidth(prompt1);
        int prompt2Width = textwidth(prompt2);
        int prompt3Width = textwidth(prompt3);
        int prompt4Width = textwidth(prompt4);

        outtextxy((getwidth() - titleWidth) / 2, getheight() / 2 - 120, title);
        settextstyle(24, 0, _T("Arial")); // 设置较小字体
        settextcolor(YELLOW);
        outtextxy((getwidth() - prompt1Width) / 2, getheight() / 2 - 20, prompt1);
        outtextxy((getwidth() - prompt2Width) / 2, getheight() / 2 + 20, prompt2);
        outtextxy((getwidth() - prompt3Width) / 2, getheight() / 2 + 60, prompt3);
        outtextxy((getwidth() - prompt4Width) / 2, getheight() / 2 + 100, prompt4);

        FlushBatchDraw(); // 显示绘制内容

        // 进入消息循环，等待用户输入
        MainExMessage msg;
        bool invalidInput = false;

        while (true) {
            // 获取消息
            if (getMainMenuMessage(msg)) {
                if (msg.message == WM_KEYDOWN) {
                    switch (msg.vkcode) {
                    case 'G':
                    case 'g':
                        closegraph(); // 关闭主菜单窗口
                        runGame();     // 运行游戏
                        return 0;      // 游戏结束后退出程序
                    case 'Q':
                    case 'q':
                        closegraph(); // 关闭主菜单窗口
                        std::cout << "退出游戏。" << std::endl;
                        return 0;      // 退出程序
                    case 'I':
                    case 'i':
                        closegraph(); // 关闭主菜单窗口
                        createConfig(); // 新建配置
                        // 重新绘制主菜单后继续循环
                        break;
                    case 'U':
                    case 'u':
                        closegraph(); // 关闭主菜单窗口
                        loadConfig(currentConfig); // 加载配置
                        // 重新绘制主菜单后继续循环
                        break;
                    default:
                        invalidInput = true;
                        break;
                    }
                    // 重新初始化主菜单窗口
                    menuHwnd = initgraph(menuWidth, menuHeight, 1);
                    if (menuHwnd == INVALID_HANDLE_VALUE) {
                        std::cerr << "主界面窗口初始化失败！" << std::endl;
                        return 1;
                    }
                    SetWindowText(menuHwnd, L"俄罗斯方块 - 主菜单");
                    cleardevice();
                    settextstyle(48, 0, _T("Arial"));
                    settextcolor(YELLOW);
                    outtextxy((getwidth() - titleWidth) / 2, getheight() / 2 - 120, title);
                    settextstyle(24, 0, _T("Arial"));
                    settextcolor(YELLOW);
                    outtextxy((getwidth() - prompt1Width) / 2, getheight() / 2 - 20, prompt1);
                    outtextxy((getwidth() - prompt2Width) / 2, getheight() / 2 + 20, prompt2);
                    outtextxy((getwidth() - prompt3Width) / 2, getheight() / 2 + 60, prompt3);
                    outtextxy((getwidth() - prompt4Width) / 2, getheight() / 2 + 100, prompt4);
                    FlushBatchDraw();
                }
            }

            if (invalidInput) {
                // 显示非法输入提示
                cleardevice();
                settextstyle(24, 0, _T("Arial"));
                settextcolor(RED);
                TCHAR invalidMsg[] = _T("无效输入，请按 'G' 开始、'I' 新建、'U' 加载配置或 'Q' 退出");
                int invalidWidth = textwidth(invalidMsg);
                outtextxy((getwidth() - invalidWidth) / 2, getheight() / 2 - 20, invalidMsg);
                FlushBatchDraw();
                Sleep(2000); // 显示2秒提示

                // 重新绘制主菜单
                cleardevice();
                settextstyle(48, 0, _T("Arial"));
                settextcolor(YELLOW);
                outtextxy((getwidth() - titleWidth) / 2, getheight() / 2 - 120, title);
                settextstyle(24, 0, _T("Arial"));
                settextcolor(YELLOW);
                outtextxy((getwidth() - prompt1Width) / 2, getheight() / 2 - 20, prompt1);
                outtextxy((getwidth() - prompt2Width) / 2, getheight() / 2 + 20, prompt2);
                outtextxy((getwidth() - prompt3Width) / 2, getheight() / 2 + 60, prompt3);
                outtextxy((getwidth() - prompt4Width) / 2, getheight() / 2 + 100, prompt4);
                FlushBatchDraw();

                invalidInput = false;
            }

            Sleep(10); // 减少CPU占用
        }
    }
}

*/