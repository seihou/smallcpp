
#include "graphics.h"
#include "conio.h"
#include "time.h"
#include "mmsystem.h"//多媒体音频接口
#pragma comment(lib,"winmm.lib")
IMAGE img;

void Welcome() {
	//贴背景图
	//加载图片
	loadimage(&img, L"bk.jpg", 800, 800);
	//图片在窗口显示的位置
	putimage(0, 0, &img);

	//open x.mp3
	//mciSendString("open x.mp3 alias BGM",0,0,0);
	//play x.mp3 
	//mciSendString("play BGM repeat", 0, 0, 0);

	//设置背景
	setbkmode(0);

	//输出文本坐标 x,y表示文字在窗口显示的位置 c
	outtextxy(300, 100, L"欢迎");

	settextcolor(YELLOW);
	outtextxy(200, 300, L"作者");
	settextcolor(RED);
	settextstyle(30, 0, L"微软雅黑");
	outtextxy(250, 400, L"只要努力一定会有结果!!!");
	//迷茫的 内心  
	while (!_kbhit()) {
		settextcolor(RGB(rand() % 256, rand() % 256, rand() % 256));
		outtextxy(500, 650, L"按任意键继续...");
		Sleep(100);
	}
}

void PlayGame() {
	HWND hwnd = GetHWnd();
	mciSendString(L"close BGM", 0, 0, 0);
	//清屏
	cleardevice();
	while (1) {
	A:
		char Obj;//目标文字 随机参数的字符
		char Key;//按键输入的 
		int Objx, Objy;
		int flag = 0;
		//获取一个大写的字母
		Obj = rand() % 26 + 65 + 32;//0-25 大写字母
		//随机参数坐标
		Objx = rand() % 700 + 50;//随机产生x坐标   50-749
		for (Objy = 0; Objy < 800; Objy += 5) {
			cleardevice();
			//y 0-799
			settextcolor(RGB(0, 255, 0));
			outtextxy(Objx, Objy, Obj);
			Sleep(20);
			if (_kbhit()) {
				Key = _getch();//获取字符
				if (Key == Obj) {
					settextcolor(RGB(0, 0, 0));
					outtextxy(Objx, Objy, Obj);
					flag = 1;
					break;
				}
			}
		}
		if (flag == 0) {
			int x = MessageBox(hwnd, L"GameOver!!!", L"温馨提示", MB_YESNO);
			exit(0);
		}
	}
}

int main() {
	//创建窗口 单位:px 像素
	initgraph(800, 800);
	//通过时间做随机数的种子
	srand((unsigned)time(NULL));
	Welcome();
	PlayGame();
	system("pause");
	return 0;
}


