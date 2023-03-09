//ɨ��

#include <stdio.h>
#include <string.h>	//�ַ�����ͷ�ļ�
#include <stdlib.h>
#include <time.h>
#include "easyx.h"
#include <graphics.h>//ͼ�ο�

//����ṹ��
struct Position
{
	int x;
	int y;
};

int length = 640;	//���ڴ�С
const int N = 10;			//ÿ��ÿ�з��������
int size;			//����Ĵ�С
const int MAX_MINE = 10;		//�׵�����

IMAGE image[13];	//�洢ͼƬ�Ľṹ������

int map[N][N];		//δ�������������
int valueMap[N][N];	//�ѷ������������

Position mines[MAX_MINE];	//�׵���������

//ͼƬ�ز�ö������
enum PNG
{
	flag = 9, mine, block,question,open
};

//�����8����������
int dir[8][2] = {
	{ 0, 1 }, { 0, -1 }, { 1, 1 }, { 1, -1 },
	{ 1, 0 }, { -1, 0 }, { -1, 1 }, {-1,-1}
};

bool isGameOver;	//�Ƿ���Ϸ����
bool isWin;			//�Ƿ�ʤ��
bool isFrist;			//����ǵ�һ��

//ÿ������Χ��������
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

//���ɵ���
void random_mine()
{
	//�׵ĳ�ʼ����ϴ���㷨
	for (int i = 0; i < MAX_MINE; i++)
	{
		valueMap[i / N][i % N] = mine;	//�׵�˳������
	}
	//ͨ�������������׵�˳��
	for (int i = 0; i < MAX_MINE; i++)
	{
		int x = rand() % N;
		int y = rand() % N;
		//�����׵�λ��
		int t = valueMap[i / N][i % N];
		valueMap[i / N][i % N] = valueMap[y][x];
		valueMap[y][x] = t;
	}

	//ѭ���ҵ��Ѿ������õ��׵�λ��
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
	//		if (x == mines[j].x && y == mines[j].y)	//���λ�ó�ͻ���������λ��
	//		{
	//			x = rand() % N;	//���������������ӣ���λ�ó�ͻ�ĸ��ʻ�Խ��Խ��
	//			y = rand() % N; //�������ɵ��׵��ٶ�Խ��Խ��������һֱ����������
	//		}
	//	}
	//	mines[i].x = x;
	//	mines[i].y = y;
	//}

}

//���Ƶ�ͼ
void draw()
{
	BeginBatchDraw();	//��ʼ��������
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			switch (map[i][j])
			{
			case block:	//û�д򿪵�ͼ��
				putimage(j*size, i*size, &image[block]);
				break;
			case flag:	//����
				putimage(j*size, i*size, &image[flag]);
				break;
			case question:	//�ʺ�
				putimage(j*size, i*size, &image[question]);
				break;
			case open:	//��
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
	EndBatchDraw();	//������������
}

//��ʼ����ͼ
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
	random_mine();	//��ʼ���׵�ͼ
	isGameOver = false;	//��Ϸ����������ʼ��Ϊfalse
	isWin = false;	//��Ϸʤ��������ʼ��Ϊfalse
	isFrist = true;	//����ǵ�һ��
}

//��ʼ��ͼ��
void init_image()
{
	initgraph(length, length);	//��ͼ�οⴰ��
	size = length / N;			//����ͼƬ��С
	//����ͼƬ
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

	srand(unsigned(time(NULL)));	//�����������
}

//��ʼ��
void init()
{
	init_image();
	init_map();
}

//�ж��Ƿ�ʤ��
void win()
{
	int n = 0;	//ʣ��δ�򿨷��������
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

//�Զ����
void floodFill(int x, int y)
{
	//����8������
	for (int i = 0; i < 8; i++)
	{
		if (valueMap[y][x] == 0)	//�ݹ�������Ǹ���û����
		{
			int x1 = dir[i][1] + x;
			int y1 = dir[i][0] + y;
			if (x1<0 || x1 >= N || y1 <0 || y1 >= N)	//Խ�������
			{
				continue;
			}
			if (block == map[y1][x1] || question == map[y1][x1])
			{
				map[y1][x1] = open;
				floodFill(x1, y1);	//�ݹ����յأ��򿪸��������׵ķ���
			}
		}
	}
}

//��ҽ�������
void play()
{
	MOUSEMSG mouse = GetMouseMsg();//��ȡ�����Ϣ
	int x = mouse.x / size;	//��ȡ���x�����᷽���λ��
	int y = mouse.y / size;	//��ȡ���y�����᷽���λ��
	if (WM_LBUTTONDOWN == mouse.uMsg)	//���������µ���Ϣ
	{
		//�ж�������µ��Ƿ��Ƿ�������ʺ�
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
	if (WM_RBUTTONDOWN == mouse.uMsg)	//����Ҽ����µ���Ϣ
	{
		if (block == map[y][x])	//����Ƿ��飬�ͱ������
		{
			map[y][x] = flag;
		}
		else if (flag == map[y][x])	//��������ӣ��ͱ���ʺ�
		{
			map[y][x] = question;
		}
		else if (question == map[y][x]) //������ʺ�,�ͱ�ɷ���
		{
			map[y][x] = block;
		}
	}
	win();
}

//��ʼ��Ϸ
void start()
{
	init();
	draw();
	while (true)
	{
		play();
		draw();
		if (isGameOver)	//��Ϸʧ��
		{
			//ʧ���������׵���ʾ

			int a = MessageBox(GetForegroundWindow(), L"�Ƿ������Ϸ", L"��Ϸ����", MB_YESNO);
			if (6 == a)	//6��ʾ�����˰�ť����
			{
				init_map();
			}
			else if (7 == a) //7��ʾ�����˰�ť����
			{
				break;
				//exit(0);
			}
		}
		if (isWin)
		{
			int a = MessageBox(GetForegroundWindow(), L"�Ƿ������Ϸ", L"��Ϸʤ��", MB_YESNO);
			if (6 == a)	//6��ʾ�����˰�ť����
			{
				init_map();
			}
			else if (7 == a) //7��ʾ�����˰�ť����
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