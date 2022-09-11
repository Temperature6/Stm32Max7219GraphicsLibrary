Stm32 MAX7219 点阵屏图形库

### 介绍

基于HAL库的Stm32 MAX7219 点阵屏图形库

![](.\pic\cover.jpg)

### 使用

#### void Max7219_Init(void);

初始化点阵屏

！！必须在GPIO初始化完成之后调用

#### void Max7219_Clear(void);

清空屏幕

#### void Max7219_SetDot(uint8_t x, uint8_t y, uint8_t state);

单独控制一个LED

x：横坐标

y：纵坐标

state：状态，ON（开）或 OFF（关）

#### void Max7219_SetBrightness(uint8_t brightness);

设置亮度

brightness：亮度，可选的值为L0 - L15，或0 - 15

#### void Max7219_Fill(void);

填充整个屏幕

#### void Max7219_DrawBitMap(uint8_t map[], uint8_t length, uint8_t height, int start_X, int start_Y);

绘图

map[]：位图数组，可由字模提取软件生成

length：位图的长（像素）

height：位图的宽（像素）

start_X：开始绘图的起始横坐标

start_Y：开始绘图的起始纵坐标

特性：绘图程序只绘制位图数组中有点亮的部分，未点亮的部分显示原来的状态

#### void Max7219_InvertScreen();

反转屏幕（反显）

#### void Max7219_Power(uint8_t shutdown);

开启或关闭屏幕

shutdown：开启或关闭，可选的值为ON或OFF
