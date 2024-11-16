# 俄罗斯方块 

## 实现思路 

基于面向对象实现，实现方块类 `Block`和框架类`Frame`

**未更新，可直接看源文件**

### `Block` 类
**未注明均为public成员和方法，方法参数未定**  
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

