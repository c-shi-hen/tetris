# 俄罗斯方块 

## 实现思路 

基于面向对象实现，实现方块类 `Block`和框架类`Frame`

### `Block` 类
**未注明均为public成员和方法，方法参数未定**  
成员列表
```  
//方块颜色
Block.color
//方块大小
Block.length
//方块速度
Block.speed
//方块坐标
Block.x_axis
Block.y_axis
//方块状态，是否正在下落
Block.is_fall
//ect ???
```
方法列表  
```  
//构造函数
Block();
//析构函数
~Block();
//根据键盘下和当前速度改变y_axis位置
void set_y_axis();
//根据键盘左右改变x_axis位置
void set_x_axis(Message button_down);
//ect ???
```

### `Frame`类 
**未注明均为public成员和方法**  
成员列表
```  
//窗口实例
Frame.main
//窗口大小
Frame.size{
	//貌似有专门的结构体
	int width;
	int height;
}
//格子大小,考虑方块的大小
Frame.grid_size
//格子数目，row，column
Frame.row
Frame.column
//格子矩阵，储存方块
Frame.matrix
//储存当前下落格子，使用vector?
Frame.falling_block
//ect ???
```
方法列表  
```  
//构造函数
Frame();
//析构函数
~Frame();
//生成初始界面
void init_frame();
//检测是否出现整行
void is_full_row();
//事件响应
如何实现，easyx使用
//游戏开始
void game_begin();
//判断游戏结束
void game_over();
//ect ???
```

