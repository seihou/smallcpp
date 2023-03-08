
#include "graphics.h"
#include "conio.h"
#include "time.h"
#include "mmsystem.h"//多媒体音频接口
#pragma comment(lib,"winmm.lib")
IMAGE img;

void Welcome(){
	//贴背景图
	//加载图片
	loadimage(&img, "bk.jpg", 800, 800);
	//图片在窗口显示的位置
	putimage(0, 0, &img);
	
	//open x.mp3
	//mciSendString("open x.mp3 alias BGM",0,0,0);
	//play x.mp3 
	//mciSendString("play BGM repeat", 0, 0, 0);

	//设置背景
	setbkmode(0);

	//输出文本坐标 x,y表示文字在窗口显示的位置 c
	outtextxy(300, 100, "欢迎来到六星C/C++学院");

	settextcolor(YELLOW);
	outtextxy(200, 300, "作者:教主");
	settextcolor(RED);
	settextstyle(30, 0, "微软雅黑");
	outtextxy(250, 400, "只要努力一定会有结果!!!");
	//迷茫的 内心  
	while (!kbhit()){
		settextcolor(RGB(rand() % 256, rand() % 256, rand() % 256));
		outtextxy(500, 650, "按任意键继续...");
		Sleep(1000);
	}
}

void PlayGame(){
	HWND hwnd = GetHWnd();
	mciSendString("close BGM", 0, 0, 0);
	//清屏
	cleardevice();
	int flag = 0;
	while (1){
		char Obj;//目标文字 随机参数的字符
		char Key;//按键输入的 
		int Objx, Objy;
		//获取一个大写的字母
		Obj = rand() % 26 + 65;//0-25 大写字母
		//随机参数坐标
		Objx = rand() % 700 + 50;//随机产生x坐标
		for (Objy = 0; Objy < 800; Objy++){
			cleardevice();
			//y 0-799
			outtextxy(Objx, Objy, Obj);
			Sleep(10);
			if (kbhit()){
				Key = getch();//获取字符
				if (Key == Obj){
					settextcolor(RGB(0, 0, 0));
					outtextxy(Objx, Objy, Obj);
					flag = 1;
					break;
				}
			}
		}
		if (flag == 0){
			int x=MessageBox(hwnd, "GameOver!!!", "温馨提示", MB_YESNO);
			exit(0);
		}
	}
}

int main(){

	//创建窗口 单位:px 像素
	initgraph(800, 800);
	//通过时间做随机数的种子
	srand((unsigned)time(NULL));
	

	Welcome();
	PlayGame();
	
	

	system("pause");


	return 0;
}


