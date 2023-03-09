//扫雷

#include <stdio.h>
#include <string.h>	//字符串类头文件
#include <stdlib.h>
#include <time.h>
#include "easyx.h"
#include <graphics.h>//图形库

//坐标结构体
struct Position
{
	int x;
	int y;
};

int length = 640;	//窗口大小
const int N = 10;			//每行每列方块的数量
int size;			//方块的大小
const int MAX_MINE = 10;		//雷的数量

IMAGE image[13];	//存储图片的结构体数组

int map[N][N];		//未翻开区域的数组
int valueMap[N][N];	//已翻开区域的数组

Position mines[MAX_MINE];	//雷的坐标数组

//图片素材枚举类型
enum PNG
{
	flag = 9, mine, block,question,open
};

//坐标的8个方向数组
int dir[8][2] = {
	{ 0, 1 }, { 0, -1 }, { 1, 1 }, { 1, -1 },
	{ 1, 0 }, { -1, 0 }, { -1, 1 }, {-1,-1}
};

bool isGameOver;	//是否游戏结束
bool isWin;			//是否胜利
bool isFrist;			//如果是第一次

//每个雷周围加上数字
void addNum(int x,int y)
{
	for (int i = 0; i < 8; i++)
	{
		int x1 = dir[i][1] + x;
		int y1 = dir[i][0] + y;
		if (x1<0 || x1 >= N || y1 <0 || y1>= N || mine == valueMap[y1][x1])
		{
			continue;
		}
		valueMap[y1][x1]++;	//
	}
}

//生成地雷
void random_mine()
{
	//雷的初始化：洗牌算法
	for (int i = 0; i < MAX_MINE; i++)
	{
		valueMap[i / N][i % N] = mine;	//雷的顺序生成
	}
	//通过交换，打乱雷的顺序
	for (int i = 0; i < MAX_MINE; i++)
	{
		int x = rand() % N;
		int y = rand() % N;
		//交换雷的位置
		int t = valueMap[i / N][i % N];
		valueMap[i / N][i % N] = valueMap[y][x];
		valueMap[y][x] = t;
	}

	//循环找到已经交换好的雷的位置
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			if (mine == valueMap[i][j])
			{
				addNum(j, i);
			}
		}
	}

	//for (int i = 0; i < MAX_MINE; i++)
	//{
	//	int x = rand() % N;
	//	int y = rand() % N;
	//	for (int j = i; j>=0; j--)
	//	{
	//		if (x == mines[j].x && y == mines[j].y)	//如果位置冲突就重新随机位置
	//		{
	//			x = rand() % N;	//随着雷数量的增加，其位置冲突的概率会越来越大
	//			y = rand() % N; //导致生成地雷的速度越来越慢，甚至一直都在生成雷
	//		}
	//	}
	//	mines[i].x = x;
	//	mines[i].y = y;
	//}

}

//绘制地图
void draw()
{
	BeginBatchDraw();	//开始批量绘制
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			switch (map[i][j])
			{
			case block:	//没有打开的图像
				putimage(j*size, i*size, &image[block]);
				break;
			case flag:	//旗子
				putimage(j*size, i*size, &image[flag]);
				break;
			case question:	//问号
				putimage(j*size, i*size, &image[question]);
				break;
			case open:	//打开
				switch (valueMap[i][j])
				{
				case 0:
					putimage(j*size, i*size, &image[0]);
					break;
				case 1:
					putimage(j*size, i*size, &image[1]);
					break;
				case 2:
					putimage(j*size, i*size, &image[2]);
					break;
				case 3:
					putimage(j*size, i*size, &image[3]);
					break;
				case 4:
					putimage(j*size, i*size, &image[4]);
					break;
				case 5:
					putimage(j*size, i*size, &image[5]);
					break;
				case 6:
					putimage(j*size, i*size, &image[6]);
					break;
				case 7:
					putimage(j*size, i*size, &image[7]);
					break;
				case 8:
					putimage(j*size, i*size, &image[8]);
					break;
				case mine:
					putimage(j*size, i*size, &image[mine]);
					break;
				}
			}
		}
	}
	EndBatchDraw();	//结束批量绘制
}

//初始化地图
void init_map()
{
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			map[i][j] = block;
			valueMap[i][j] = 0;
		}
	}
	random_mine();	//初始化雷地图
	isGameOver = false;	//游戏结束条件初始化为false
	isWin = false;	//游戏胜利条件初始化为false
	isFrist = true;	//如果是第一次
}

//初始化图形
void init_image()
{
	initgraph(length, length);	//打开图形库窗口
	size = length / N;			//计算图片大小
	//导入图片
	loadimage(&image[0], _T("res/0.png"), size, size);
	loadimage(&image[1], _T("res/1.png"), size, size);
	loadimage(&image[2], _T("res/2.png"), size, size);
	loadimage(&image[3], _T("res/3.png"), size, size);
	loadimage(&image[4], _T("res/4.png"), size, size);
	loadimage(&image[5], _T("res/5.png"), size, size);
	loadimage(&image[6], _T("res/6.png"), size, size);
	loadimage(&image[7], _T("res/7.png"), size, size);
	loadimage(&image[8], _T("res/8.png"), size, size);

	loadimage(&image[9], _T("res/flag.png"), size, size);
	loadimage(&image[10], _T("res/mine.png"), size, size);
	loadimage(&image[11], _T("res/block.png"), size, size);
	loadimage(&image[12], _T("res/question.png"), size, size);

	srand(unsigned(time(NULL)));	//生成随机种子
}

//初始化
void init()
{
	init_image();
	init_map();
}

//判断是否胜利
void win()
{
	int n = 0;	//剩下未打卡方块的数量
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			if (block == map[i][j] || flag == map[i][j] || question == map[i][j])
			{
				n++;
			}
		}
	}
	if (MAX_MINE == n)
	{
		isWin = true;
	}
}

//自动填充
void floodFill(int x, int y)
{
	//遍历8个方向
	for (int i = 0; i < 8; i++)
	{
		if (valueMap[y][x] == 0)	//递归的条件是附近没有雷
		{
			int x1 = dir[i][1] + x;
			int y1 = dir[i][0] + y;
			if (x1<0 || x1 >= N || y1 <0 || y1 >= N)	//越界就跳过
			{
				continue;
			}
			if (block == map[y1][x1] || question == map[y1][x1])
			{
				map[y1][x1] = open;
				floodFill(x1, y1);	//递归填充空地，打开附近不是雷的方块
			}
		}
	}
}

//玩家交互函数
void play()
{
	MOUSEMSG mouse = GetMouseMsg();//获取鼠标消息
	int x = mouse.x / size;	//获取鼠标x坐标轴方块的位置
	int y = mouse.y / size;	//获取鼠标y坐标轴方块的位置
	if (WM_LBUTTONDOWN == mouse.uMsg)	//鼠标左键按下的消息
	{
		//判断左键按下的是否是方块或者问号
		if (block == map[y][x] || question == map[y][x])
		{
			if (mine == valueMap[y][x])
			{
				if (isFrist)
				{
					init_map();
				}
				isGameOver = true;
				isFrist = false;
			}
		}		
		map[y][x] = open;
		floodFill(x, y);
	}
	if (WM_RBUTTONDOWN == mouse.uMsg)	//鼠标右键按下的消息
	{
		if (block == map[y][x])	//如果是方块，就变成旗子
		{
			map[y][x] = flag;
		}
		else if (flag == map[y][x])	//如果是旗子，就变成问号
		{
			map[y][x] = question;
		}
		else if (question == map[y][x]) //如果是问号,就变成方块
		{
			map[y][x] = block;
		}
	}
	win();
}

//开始游戏
void start()
{
	init();
	draw();
	while (true)
	{
		play();
		draw();
		if (isGameOver)	//游戏失败
		{
			//失败了所有雷的显示

			int a = MessageBox(GetForegroundWindow(), L"是否继续游戏", L"游戏结束", MB_YESNO);
			if (6 == a)	//6表示按下了按钮：是
			{
				init_map();
			}
			else if (7 == a) //7表示按下了按钮：否
			{
				break;
				//exit(0);
			}
		}
		if (isWin)
		{
			int a = MessageBox(GetForegroundWindow(), L"是否继续游戏", L"游戏胜利", MB_YESNO);
			if (6 == a)	//6表示按下了按钮：是
			{
				init_map();
			}
			else if (7 == a) //7表示按下了按钮：否
			{
				break;
				//exit(0);
			}
		}
	}
}

int main()
{
	start();
	//system("pause");
	return 0;
}