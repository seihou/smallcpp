
#include "graphics.h"
#include "conio.h"
#include "time.h"
#include "mmsystem.h"//��ý����Ƶ�ӿ�
#pragma comment(lib,"winmm.lib")
IMAGE img;

void Welcome(){
	//������ͼ
	//����ͼƬ
	loadimage(&img, "bk.jpg", 800, 800);
	//ͼƬ�ڴ�����ʾ��λ��
	putimage(0, 0, &img);
	
	//open x.mp3
	//mciSendString("open x.mp3 alias BGM",0,0,0);
	//play x.mp3 
	//mciSendString("play BGM repeat", 0, 0, 0);

	//���ñ���
	setbkmode(0);

	//����ı����� x,y��ʾ�����ڴ�����ʾ��λ�� c
	outtextxy(300, 100, "��ӭ��������C/C++ѧԺ");

	settextcolor(YELLOW);
	outtextxy(200, 300, "����:����");
	settextcolor(RED);
	settextstyle(30, 0, "΢���ź�");
	outtextxy(250, 400, "ֻҪŬ��һ�����н��!!!");
	//��ã�� ����  
	while (!kbhit()){
		settextcolor(RGB(rand() % 256, rand() % 256, rand() % 256));
		outtextxy(500, 650, "�����������...");
		Sleep(1000);
	}
}

void PlayGame(){
	HWND hwnd = GetHWnd();
	mciSendString("close BGM", 0, 0, 0);
	//����
	cleardevice();
	int flag = 0;
	while (1){
		char Obj;//Ŀ������ ����������ַ�
		char Key;//��������� 
		int Objx, Objy;
		//��ȡһ����д����ĸ
		Obj = rand() % 26 + 65;//0-25 ��д��ĸ
		//�����������
		Objx = rand() % 700 + 50;//�������x����
		for (Objy = 0; Objy < 800; Objy++){
			cleardevice();
			//y 0-799
			outtextxy(Objx, Objy, Obj);
			Sleep(10);
			if (kbhit()){
				Key = getch();//��ȡ�ַ�
				if (Key == Obj){
					settextcolor(RGB(0, 0, 0));
					outtextxy(Objx, Objy, Obj);
					flag = 1;
					break;
				}
			}
		}
		if (flag == 0){
			int x=MessageBox(hwnd, "GameOver!!!", "��ܰ��ʾ", MB_YESNO);
			exit(0);
		}
	}
}

int main(){

	//�������� ��λ:px ����
	initgraph(800, 800);
	//ͨ��ʱ���������������
	srand((unsigned)time(NULL));
	

	Welcome();
	PlayGame();
	
	

	system("pause");


	return 0;
}


