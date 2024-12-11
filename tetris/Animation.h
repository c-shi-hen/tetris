#pragma once
#include<vector>
#include<easyx.h>

class Animation
{
public:
	IMAGE back_ground;
	std::vector<IMAGE*> block_png;
	std::vector<IMAGE*> block_group_png;

public:
	/*
	* @biref 初始化所有的图片，仅初始化一次
	*/
	Animation();

	~Animation();
	/*
	* @brief 加载方块图片
	*/
	void load_block_png();

	/*
	* @brief 加载方块组合图片
	*/
	void load_block_group_png();
};

