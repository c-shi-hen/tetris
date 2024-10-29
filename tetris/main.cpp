#include<easyx.h>
#include"Frame.h"
#include"Begin_frame.h"
int main()
{
	Begin_frame* my_begin_frame = new Begin_frame();
	SetWindowText(initgraph( my_begin_frame->begin_frame_width, my_begin_frame->begin_frame_height), L"俄罗斯方块");
	my_begin_frame->initial();
	closegraph();

	Frame* myFrame = new Frame(my_begin_frame->default_map_size.map_width, my_begin_frame->default_map_size.map_height);
	SetWindowText(initgraph(myFrame->frame_width, myFrame->frame_height), L"俄罗斯方块");
	BeginBatchDraw();
	myFrame->begin();
	while (true){

		FlushBatchDraw();
		Sleep(1000 / 60);
	}
	EndBatchDraw();
	closegraph();
	delete(myFrame);
	delete(my_begin_frame);

	return 0;
}
