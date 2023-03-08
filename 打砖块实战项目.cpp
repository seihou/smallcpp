#include <graphics.h>
#include <conio.h>
#include <time.h>
#define ROW 5//定义砖块为5行 10列
#define COL 10

int zhuan[5][10] = { 0 };
int ballx;
int bally;
int boardx;
int boardy;

//小球速度一定,坐标均匀的改变
int addx = 1;
int addy = -1;

bool starting = false;

void drawzhuan()
{
	//绘制砖块
	for (int i = 0; i < ROW; i++)
	{
		for (int j = 0; j < COL; j++)
		{
			if (zhuan[i][j] == 0)
			{
				setfillcolor(RGB(rand() % 256, rand() % 256, rand() % 256));
				solidrectangle(j * 40, i * 20, j * 40 + 40, i * 20 + 20);
			}

		}
	}

}

void initGame()
{
	ballx = 200;
	bally = 580;
	boardx = 170;
	boardy = 590;

	//绘制砖块
	drawzhuan();

	//绘制小球
	setfillcolor(LIGHTRED);
	solidcircle(ballx, bally, 10);

	//绘制木板
	setfillcolor(YELLOW);
	solidrectangle(boardx, boardy, boardx + 60, boardy + 10);
}

void ballMove()
{
	//用黑色小球擦除坐标改变之前的小球
	setfillcolor(BLACK);
	solidcircle(ballx, bally, 10);
	BeginBatchDraw();
	if (ballx >= 390 || ballx <= 10)
		addx = -1 * addx;
	if (bally <= 10)
		addy = -1 * addy;
	int flag = 0;//标记有没有打到小球
	//小球打砖块
	//首先判断小球和砖块的坐标
	for (int i = 0; i < ROW; i++)
	{
		for (int j = 0; j < COL; j++)
		{
			//小砖块的横纵坐标
			int x = j * 40;//数组下标转换为坐标
			int y = i * 20;

			if (zhuan[i][j] == 0 && x - ballx <= 10 && ballx - x <= 50 && bally - y >= 10 && bally - y <= 30)
			{
				addy = -1 * addy;
				zhuan[i][j] = 1;
				flag = 1;
				setfillcolor(BLACK);
				solidrectangle(x, y, x + 40, y + 20);
				break;
			}
		}
		if (flag)
			break;
	}

	//木板接到小球,判断木板和小球的坐标
	if (starting && boardx - ballx <= 10 && ballx - boardx <= 70 && boardy - bally <= 10)
	{
		addy = -1 * addy;

	}

	starting = true;

	//小球移动,坐标改变
	ballx += addx;
	bally += addy;

	//移动到新位置以后重新绘制坐标改变以后的小球
	setfillcolor(LIGHTRED);
	solidcircle(ballx, bally, 10);
	FlushBatchDraw();
	Sleep(5);
}

void muban()
{
	setfillcolor(BLACK);
	solidrectangle(boardx, boardy, boardx + 60, boardy + 10);
	switch (getch())
	{
	case 75:
		boardx -= 15;
		break;
	case 77:
		boardx += 15;
		break;
	case 72:
		boardy -= 10;
		break;
	case 80:
		boardy += 10;
		break;
	default:
		break;
	}
	if (boardx <= 0)
		boardx = 0;
	if (boardx >= 340)
		boardx = 340;

	setfillcolor(YELLOW);
	solidrectangle(boardx, boardy, boardx + 60, boardy + 10);
}

int main()
{
	initgraph(400, 600);
	srand((unsigned)time(NULL));
	initGame();

	while (1)
	{
		if (kbhit())
		{
			muban();
		}
		if (bally > boardy)
			break;
		ballMove();

	}
	MessageBox(NULL, L"游戏结束", L"打砖块", MB_OK);
	return 0;
}

/*
C++发展方向: 服务器开发工程师、人工智能、云计算工程师、信息安全（黑客反黑客）、
大数据 、数据平台、嵌入式工程师、流媒体服务器、数据控解、图像处理、
音频视频开发工程师、游戏服务器、分布式系统、游戏辅助等
*/