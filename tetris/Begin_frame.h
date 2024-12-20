#pragma once
#include<easyx.h>
#include"Animation.h"

class Begin_frame
{
public:

	Begin_frame(Animation* animation);
	~Begin_frame();
	void initial();
private:
	int gameSpeed;
	int randomSeed;
	int initialLevel;

public:
	//默认窗口宽度
	const int begin_frame_width = 800;
	//默认窗口高度
	const int begin_frame_height = 800;
	//默认地图大小
	int map_width;
	int map_height;
private:
	IMAGE* background;
	void inline draw_backgroud();

public:
	struct MainMenuMessage {
		bool startGame = false;
		bool quitGame = false;
		bool createConfig = false;
		bool loadConfig = false;
	};

	bool getMainMenuMessage(MainMenuMessage& msg);

	void drawMainMenu() ;
};

