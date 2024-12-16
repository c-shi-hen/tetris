#include<easyx.h>
#include"Frame.h"
#include"Begin_frame.h"
#include"Animation.h"

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
