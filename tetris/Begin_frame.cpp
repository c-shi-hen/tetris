#include"Begin_frame.h"


#define VK_G 0x47
#define VK_Q 0x51
#define VK_I 0x49
#define VK_U 0x55

Begin_frame::Begin_frame(Animation* animation) {
	//默认地图宽度和高度
	this->map_height = 15;
	this->map_width = 10;
	this->background = &animation->back_ground;
}


Begin_frame::~Begin_frame()
{
}

/*
* @brief 获取初始化游戏界面的必要信息
*/
void Begin_frame::initial() {
	//初始界面背景
	draw_backgroud();

}

/*
* @brief 绘制地图背景
*/
void inline Begin_frame::draw_backgroud() {
	putimage(0, 0, background);
}


// 绘制主菜单界面
void Begin_frame::drawMainMenu() {
    cleardevice();
    settextstyle(48, 0, _T("Arial"));
    settextcolor(YELLOW);

    TCHAR title[] = _T("欢迎来到俄罗斯方块");
    TCHAR prompt1[] = _T("按 'G' 开始游戏");
    TCHAR prompt2[] = _T("按 'Q' 退出游戏");
    TCHAR prompt3[] = _T("按 'I' 新建配置");
    TCHAR prompt4[] = _T("按 'U' 加载配置");

    int titleWidth = textwidth(title);
    int prompt1Width = textwidth(prompt1);
    int prompt2Width = textwidth(prompt2);
    int prompt3Width = textwidth(prompt3);
    int prompt4Width = textwidth(prompt4);

    outtextxy((getwidth() - titleWidth) / 2, getheight() / 2 - 120, title);
    settextstyle(24, 0, _T("Arial"));
    outtextxy((getwidth() - prompt1Width) / 2, getheight() / 2 - 20, prompt1);
    outtextxy((getwidth() - prompt2Width) / 2, getheight() / 2 + 20, prompt2);
    outtextxy((getwidth() - prompt3Width) / 2, getheight() / 2 + 60, prompt3);
    outtextxy((getwidth() - prompt4Width) / 2, getheight() / 2 + 100, prompt4);

    FlushBatchDraw();
}



// 获取主菜单消息
bool Begin_frame::getMainMenuMessage(MainMenuMessage& msg) {
    ExMessage message;
    if (peekmessage(&message)) {
        switch (message.vkcode) {
        case VK_G:
            msg.startGame = true;
            return true;
        case VK_Q:
            msg.quitGame = true;
            return true;
        case VK_I:
            msg.createConfig = true;
            return true;
        case VK_U:
            msg.loadConfig = true;
            return true;
        default:
            break;
        }
    }
    return false;
}