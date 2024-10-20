#pragma once
struct map_size
{
	int map_width;
	int map_height;
};
class Begin_frame
{
public:
	Begin_frame();
	~Begin_frame();
	void initial();

public:
	const int begin_frame_width = 800;
	const int begin_frame_height = 640;
	const map_size default_map_size = { 20, 10 };
private:
	
};