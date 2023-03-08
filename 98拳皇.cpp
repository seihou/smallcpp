

#include <graphics.h>
#include <stdio.h>
#include <conio.h>
#include <mmsystem.h>
#pragma comment(lib,"winmm.lib")
IMAGE img[23], img_y[23], background;
int frameMoveNum = 0;
int x = 0, y = 200;
//加载图片
void InitImg(){
	char buff[128], buff_y[128];
	for (int i = 1; i < 24; i++){
		sprintf(buff, "images\\%d.bmp", i);
		sprintf(buff_y, "images\\%dy.bmp", i);
		loadimage(&img[i - 1], buff);
		loadimage(&img_y[i - 1], buff_y);
	}
	loadimage(&background, "images\\background.jpg", 640, 480);

}
//画角色
void drawRole()
{

	putimage(x, y, &img_y[frameMoveNum], SRCAND);
	putimage(x, y, &img[frameMoveNum], SRCPAINT);
	//改变贴图的帧数
	frameMoveNum++;
	Sleep(50);
	//防止动作过度
	if (frameMoveNum == 6)
		frameMoveNum = 0;
}

//释放技能
void keyPlay(IMAGE background)
{
	frameMoveNum = 6;		//从第六张图片开始 ，是放技能
	while (frameMoveNum < 24)
	{
		BeginBatchDraw();
		putimage(0, 0, &background);
		drawRole();
		frameMoveNum++;
		Sleep(5);
		EndBatchDraw();
	}
	frameMoveNum = 1;  //技能放完帧数还原
}

int main(){

	initgraph(640, 480); //创建窗口

	mciSendString("play x.mp3 repeat", 0, 0, 0);

	InitImg();//加载图片  

	while (1){
		BeginBatchDraw();
		putimage(0, 0, &background);//显示背景图
		drawRole();//显示人物图

		if (kbhit())
		{
			fflush(stdin);
			switch (getch()){
			case 'W':
			case 'w':
			case 72:
				y -= 5;
				break;
			case 's':
			case 'S':
			case 80:
				y += 15;
				break;
			case 'a':
			case 'A':
			case 75:
				x -= 15;
				break;
			case 'd':
			case 'D':
			case 77:
				x += 15;
				break;
			case 'k':
				keyPlay(background);
				break;

			}

		}

		EndBatchDraw();
	}

	return 0;
}

