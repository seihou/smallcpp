
#include "graphics.h"
#include "conio.h"
#include "time.h"
#include "mmsystem.h"//��ý����Ƶ�ӿ�
#pragma comment(lib,"winmm.lib")
IMAGE img;

void Welcome() {
	//������ͼ
	//����ͼƬ
	loadimage(&img, L"bk.jpg", 800, 800);
	//ͼƬ�ڴ�����ʾ��λ��
	putimage(0, 0, &img);

	//open x.mp3
	//mciSendString("open x.mp3 alias BGM",0,0,0);
	//play x.mp3 
	//mciSendString("play BGM repeat", 0, 0, 0);

	//���ñ���
	setbkmode(0);

	//����ı����� x,y��ʾ�����ڴ�����ʾ��λ�� c
	outtextxy(300, 100, L"��ӭ");

	settextcolor(YELLOW);
	outtextxy(200, 300, L"����");
	settextcolor(RED);
	settextstyle(30, 0, L"΢���ź�");
	outtextxy(250, 400, L"ֻҪŬ��һ�����н��!!!");
	//��ã�� ����  
	while (!_kbhit()) {
		settextcolor(RGB(rand() % 256, rand() % 256, rand() % 256));
		outtextxy(500, 650, L"�����������...");
		Sleep(100);
	}
}

void PlayGame() {
	HWND hwnd = GetHWnd();
	mciSendString(L"close BGM", 0, 0, 0);
	//����
	cleardevice();
	while (1) {
	A:
		char Obj;//Ŀ������ ����������ַ�
		char Key;//��������� 
		int Objx, Objy;
		int flag = 0;
		//��ȡһ����д����ĸ
		Obj = rand() % 26 + 65 + 32;//0-25 ��д��ĸ
		//�����������
		Objx = rand() % 700 + 50;//�������x����   50-749
		for (Objy = 0; Objy < 800; Objy += 5) {
			cleardevice();
			//y 0-799
			settextcolor(RGB(0, 255, 0));
			outtextxy(Objx, Objy, Obj);
			Sleep(20);
			if (_kbhit()) {
				Key = _getch();//��ȡ�ַ�
				if (Key == Obj) {
					settextcolor(RGB(0, 0, 0));
					outtextxy(Objx, Objy, Obj);
					flag = 1;
					break;
				}
			}
		}
		if (flag == 0) {
			int x = MessageBox(hwnd, L"GameOver!!!", L"��ܰ��ʾ", MB_YESNO);
			exit(0);
		}
	}
}

int main() {
	//�������� ��λ:px ����
	initgraph(800, 800);
	//ͨ��ʱ���������������
	srand((unsigned)time(NULL));
	Welcome();
	PlayGame();
	system("pause");
	return 0;
}


