#include<easyx.h>
#include"Frame.h"
#include"Begin_frame.h"
#include"Animation.h"

int main()
{
	Begin_frame* my_begin_frame = new Begin_frame();
	SetWindowText(initgraph( my_begin_frame->begin_frame_width, my_begin_frame->begin_frame_height), L"俄罗斯方块");
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

	return 0;
}
