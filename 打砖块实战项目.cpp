#include <graphics.h>
#include <conio.h>
#include <time.h>
#define ROW 5//����ש��Ϊ5�� 10��
#define COL 10

int zhuan[5][10] = { 0 };
int ballx;
int bally;
int boardx;
int boardy;

//С���ٶ�һ��,������ȵĸı�
int addx = 1;
int addy = -1;

bool starting = false;

void drawzhuan()
{
	//����ש��
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

	//����ש��
	drawzhuan();

	//����С��
	setfillcolor(LIGHTRED);
	solidcircle(ballx, bally, 10);

	//����ľ��
	setfillcolor(YELLOW);
	solidrectangle(boardx, boardy, boardx + 60, boardy + 10);
}

void ballMove()
{
	//�ú�ɫС���������ı�֮ǰ��С��
	setfillcolor(BLACK);
	solidcircle(ballx, bally, 10);
	BeginBatchDraw();
	if (ballx >= 390 || ballx <= 10)
		addx = -1 * addx;
	if (bally <= 10)
		addy = -1 * addy;
	int flag = 0;//�����û�д�С��
	//С���ש��
	//�����ж�С���ש�������
	for (int i = 0; i < ROW; i++)
	{
		for (int j = 0; j < COL; j++)
		{
			//Сש��ĺ�������
			int x = j * 40;//�����±�ת��Ϊ����
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

	//ľ��ӵ�С��,�ж�ľ���С�������
	if (starting && boardx - ballx <= 10 && ballx - boardx <= 70 && boardy - bally <= 10)
	{
		addy = -1 * addy;

	}

	starting = true;

	//С���ƶ�,����ı�
	ballx += addx;
	bally += addy;

	//�ƶ�����λ���Ժ����»�������ı��Ժ��С��
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
	MessageBox(NULL, L"��Ϸ����", L"��ש��", MB_OK);
	return 0;
}

/*
C++��չ����: ��������������ʦ���˹����ܡ��Ƽ��㹤��ʦ����Ϣ��ȫ���ڿͷ��ڿͣ���
������ ������ƽ̨��Ƕ��ʽ����ʦ����ý������������ݿؽ⡢ͼ����
��Ƶ��Ƶ��������ʦ����Ϸ���������ֲ�ʽϵͳ����Ϸ������
*/