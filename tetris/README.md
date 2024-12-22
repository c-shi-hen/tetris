# 俄罗斯方块 

## 实现思路 

使用`easyx`标准库，基于面向对象思想分别实现游戏主菜单、游戏界面、资源加载、文件配置等功能。  
列表如下：
```
Begin_frame: 游戏主菜单，实现了新建和加载配置文件、新建和加载残局、开始游戏、退出游戏
Frame: 游戏界面，实现了随时暂停、残局生成、暂停后退出
Block: 游戏方块，实现了坐标控制、颜色显示
Animation: 加载游戏所需要的图片资源
EndGame: 专门处理新建残局和加载残局以及残局生成
```

### `Block` 类

成员列表
```  
//方块颜色，使用图片替换
Block.color
//方块大小
const static int block_width = 50;
const static int block_height = 50;
//方块速度
Block.speed
//方块位置
Block.row
Block.column
//是否存在方块
Block.is_block
//ect ???
```
方法列表  
```  
//构造函数
Block();
//析构函数
~Block();
//绘制方块
void show();
//加载方块图片
void load_image();_
//ect ???
```

### `Frame`类 
**未注明均为public成员和方法**  
成员列表
```  
//窗口大小
Frame.size{
	//貌似有专门的结构体,暂时未用
	int width;
	int height;
}

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
void check_line_();
//事件响应
如何实现，easyx使用
//游戏开始
void game_begin();
//判断游戏结束
void game_over();
//ect ???
```

