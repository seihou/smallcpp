#include <Windows.h>
#include <tchar.h>
int map[10][10] = {
1,1,1,1,1,1,1,1,1,1,
1,0,0,0,0,0,0,0,0,1,
1,0,0,0,0,0,5,0,0,1,
1,0,0,0,0,0,0,0,0,1,
1,0,0,0,3,0,0,0,0,1,
1,0,0,0,0,0,0,0,0,1,
1,0,0,0,0,0,0,0,0,1,
1,0,0,0,0,0,0,0,0,1,
1,0,2,0,0,0,0,0,0,1,
1,1,1,1,1,1,1,1,1,1,
};

HBITMAP g_bImages[5];
HDC g_mdc[5],g_hdc;
VOID initMap(HWND hwnd);
VOID drawMap(HWND hwnd);

LRESULT CALLBACK WindProcFunc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);		// ���ڹ��̺���

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPreInstance, PSTR lpszCmdLine, int iCmdShow)
{
	// һ�����崰����
	TCHAR tcClassName[] = TEXT("myWindowsPro");		// ��������

	// ������ṹ WNDCLASS
	WNDCLASS windClass;			// ���������������ṹ������
	windClass.lpszClassName = tcClassName;			// ��������
	windClass.lpszMenuName = NULL;					// ������˵���Դ����
	windClass.hInstance = hInstance;				// ��ǰ���̶�����������WinMain����
	windClass.lpfnWndProc = WindProcFunc;			// ���ڹ��̺���
	windClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);		// ���ڱ�����ˢ����
	windClass.hIcon = NULL; // ���ڱ���ͼ�� ��ʽico
	windClass.hCursor = LoadCursor(NULL, IDC_ARROW);		// ���ڹ��
	windClass.cbClsExtra = 0;		// ͬ�ര�ڶ��󹫹���������С
	windClass.cbWndExtra = 0;		// ��ǰ���ڶ���˽����������С
	windClass.style = CS_HREDRAW | CS_VREDRAW;	// ���ڷ��

	// ����ע�ᴰ���� ����Ϊָ����WNDCLASS�ṹ��ָ��
	if (!RegisterClass(&windClass))
	{
		MessageBox(NULL, TEXT("����ע��ʧ��."), TEXT("��ʾ"), MB_OK | MB_ICONERROR);
		return 0;
	}

	// ������������
	TCHAR tcWindowsCaptionName[] = TEXT("Windows������Ƶڶ���������ģ�����.");
	CREATESTRUCT cs;		// ���ڱ�׼����
	cs.lpszName = tcWindowsCaptionName;		// ��������
	cs.lpszClass = tcClassName;				// ��������
	cs.x = 400;				// ���ڶ�������Ļ�ϵ�����x
	cs.y = 200;				// ���ڶ�������Ļ�ϵ�����y
	cs.cx = 500;			// ���ڿ��
	cs.cy = 550;			// ���ڸ߶�
	cs.hwndParent = NULL;	// ���ڶ���ĸ����ھ��
	cs.hMenu = NULL;		// ���ڶ���˵���� ���Ӵ��ڱ��
	cs.hInstance = hInstance;		// ��ǰ���� ʵ�����WinMain����
	cs.lpCreateParams = NULL;		// ��������ָ�� ���Է����Ժ���Ҫ���ó��������
	cs.style = WS_OVERLAPPEDWINDOW;  // ���ڶ��� ���

	//��������
	HWND hwnd = CreateWindow(cs.lpszClass, cs.lpszName, cs.style, cs.x, cs.y, cs.cx, cs.cy, cs.hwndParent, cs.hMenu, cs.hInstance, cs.lpCreateParams);
	if (hwnd == NULL)
	{
		MessageBox(NULL, TEXT("��������ʧ��."), TEXT("��ʾ"), MB_OK | MB_ICONERROR);
		return 0;
	}

	// �ġ���ʾ ����
	ShowWindow(hwnd, iCmdShow);
	UpdateWindow(hwnd);

	initMap(hwnd);


	// �塢��Ϣѭ������
	MSG msg = { 0 };			// ���岢��ʼ��msg
	while (msg.message != WM_QUIT)		// ʹ��whileѭ���������Ϣ����WM_QUIT��Ϣ����ֱ�Ӽ���ѭ��
	{
		if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))  // �鿴Ӧ�ó�����Ϣ���У�����Ϣʱ����������Ϣ�ɷ���ȥ
		{
			TranslateMessage(&msg);		// ���������Ϣת�����ַ���Ϣ
			DispatchMessage(&msg);		// �ַ�һ����Ϣ�����ڳ���
		}
		drawMap(hwnd);
		
	}

	return msg.wParam;
}

LRESULT CALLBACK WindProcFunc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)		// ���ڹ��̺���
{
	int x, y;
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			if (map[i][j] == 2||map[i][j]==7)
			{
				x = i;
				y = j;
			}
		}
	}
	switch (message)
	{
		// ����������Ϣ
	case WM_DESTROY://����esc
	{
		// ����WM_QUIT��Ϣ��֪ͨ�߳���Ϣ����ѭ����������������򼴿��˳�
		for (int i = 0; i < 5; i++)
			DeleteObject(g_bImages);
		for (int i = 0; i < 5; i++)
			DeleteDC(g_mdc[i]);
		ReleaseDC(hwnd, g_hdc);
		PostQuitMessage(0);
		
		return 0;

	}
	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_ESCAPE:
			DestroyWindow(hwnd);
			PostQuitMessage(0);
			break;
		case VK_RIGHT://����
			if (map[x][y + 1] == 0 || map[x][y + 1] == 5)
			{
				map[x][y] -= 2;
				map[x][y + 1] += 2;
			}
			else if (map[x][y + 1] == 3 || map[x][y + 1] == 8)
			{
				if (map[x][y + 2] == 0 || map[x][y + 2] == 5)
				{
					map[x][y] -= 2;
					map[x][y + 1] -= 1;
					map[x][y + 2] += 3;
				}
			}
			break;
		case VK_LEFT://����
			if (map[x][y - 1] == 0 || map[x][y - 1] == 5)
			{
				map[x][y] -= 2;
				map[x][y - 1] += 2;
			}
			else if (map[x][y - 1] == 3 || map[x][y - 1] == 8)
			{
				if (map[x][y - 2] == 0 || map[x][y - 2] == 5)
				{
					map[x][y] -= 2;
					map[x][y - 1] -= 1;
					map[x][y - 2] += 3;
				}
			}
			break;
		case VK_UP:
			if (map[x - 1][y] == 0 || map[x - 1][y] == 5)
			{
				map[x][y] -= 2;
				map[x - 1][y] += 2;
			}
			else if (map[x - 1][y] == 3 || map[x - 1][y] == 8)
			{
				if (map[x - 2][y] == 0 || map[x - 2][y] == 5)
				{
					map[x][y] -= 2;
					map[x - 1][y] -= 1;
					map[x - 2][y] += 3;
				}
			}
			break;
		case VK_DOWN:
			if (map[x + 1][y] == 0 || map[x + 1][y] == 5)
			{
				map[x][y] -= 2;
				map[x + 1][y] += 2;
			}
			else if (map[x + 1][y] == 3 || map[x + 1][y] == 8)
			{
				if (map[x + 2][y] == 0 || map[x + 2][y] == 5)
				{
					map[x][y] -= 2;
					map[x + 1][y] -= 1;
					map[x + 2][y] += 3;
				}
			}
			break;

		}
		InvalidateRect(hwnd, NULL, true);
		break;
	}

	return DefWindowProc(hwnd, message, wParam, lParam);
}


VOID initMap(HWND hwnd)
{
	g_hdc = GetDC(hwnd);
	CCHAR str[10] = { 0 };
	for (int i = 1; i <= 5; i++)
	{
		wsprintf(str, "%d.bmp", i);
		g_bImages[i-1] = (HBITMAP)LoadImage(NULL, str, IMAGE_BITMAP, 50, 50, LR_LOADFROMFILE);
	}
	for (int i = 0; i < 5; i++)
	{
		g_mdc[i] = CreateCompatibleDC(g_hdc);
		SelectObject(g_mdc[i], g_bImages[i]);
	}
	drawMap(hwnd);
}
VOID drawMap(HWND hwnd)
{
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			switch (map[i][j])
			{
			case 1://Χǽ
				BitBlt(g_hdc, j * 50, i * 50, 50, 50, g_mdc[0], 0, 0, SRCCOPY);
				break;
			case 2://��
				BitBlt(g_hdc, j * 50, i * 50, 50, 50, g_mdc[1], 0, 0, SRCCOPY);
				break;
			case 3://����
				BitBlt(g_hdc, j * 50, i * 50, 50, 50, g_mdc[3], 0, 0, SRCCOPY);
				break;
			case 8://������Ŀ�ĵ���
				BitBlt(g_hdc, j * 50, i * 50, 50, 50, g_mdc[2], 0, 0, SRCCOPY);
				break;
			case 5://Ŀ�ĵ�
				BitBlt(g_hdc, j * 50, i * 50, 50, 50,g_mdc[4] , 0, 0, SRCCOPY);
				break;
			case 7:
				BitBlt(g_hdc, j * 50, i * 50, 50, 50, g_mdc[1], 0, 0, SRCCOPY);
				break;
			}
		}
	}
}