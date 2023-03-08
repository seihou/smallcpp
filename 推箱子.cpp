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

LRESULT CALLBACK WindProcFunc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);		// 窗口过程函数

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPreInstance, PSTR lpszCmdLine, int iCmdShow)
{
	// 一、定义窗口类
	TCHAR tcClassName[] = TEXT("myWindowsPro");		// 窗口类名

	// 窗口类结构 WNDCLASS
	WNDCLASS windClass;			// 窗口类属性描述结构体类型
	windClass.lpszClassName = tcClassName;			// 窗口类名
	windClass.lpszMenuName = NULL;					// 窗口类菜单资源名称
	windClass.hInstance = hInstance;				// 当前进程对象句柄，接收WinMain参数
	windClass.lpfnWndProc = WindProcFunc;			// 窗口过程函数
	windClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);		// 窗口背景画刷对象
	windClass.hIcon = NULL; // 窗口标题图标 格式ico
	windClass.hCursor = LoadCursor(NULL, IDC_ARROW);		// 窗口光标
	windClass.cbClsExtra = 0;		// 同类窗口对象公共数据区大小
	windClass.cbWndExtra = 0;		// 当前窗口对象私有数据区大小
	windClass.style = CS_HREDRAW | CS_VREDRAW;	// 窗口风格

	// 二、注册窗口类 参数为指针向WNDCLASS结构的指针
	if (!RegisterClass(&windClass))
	{
		MessageBox(NULL, TEXT("窗口注册失败."), TEXT("提示"), MB_OK | MB_ICONERROR);
		return 0;
	}

	// 三、创建窗口
	TCHAR tcWindowsCaptionName[] = TEXT("Windows程序设计第二讲：程序模块分析.");
	CREATESTRUCT cs;		// 窗口标准名称
	cs.lpszName = tcWindowsCaptionName;		// 窗口名称
	cs.lpszClass = tcClassName;				// 窗口类名
	cs.x = 400;				// 窗口对象在屏幕上的坐标x
	cs.y = 200;				// 窗口对象在屏幕上的坐标y
	cs.cx = 500;			// 窗口宽度
	cs.cy = 550;			// 窗口高度
	cs.hwndParent = NULL;	// 窗口对象的父窗口句柄
	cs.hMenu = NULL;		// 窗口对象菜单句柄 或子窗口编号
	cs.hInstance = hInstance;		// 当前进程 实例句柄WinMain参数
	cs.lpCreateParams = NULL;		// 创建参数指针 可以访问以后想要引用程序的数据
	cs.style = WS_OVERLAPPEDWINDOW;  // 窗口对象 风格

	//创建窗口
	HWND hwnd = CreateWindow(cs.lpszClass, cs.lpszName, cs.style, cs.x, cs.y, cs.cx, cs.cy, cs.hwndParent, cs.hMenu, cs.hInstance, cs.lpCreateParams);
	if (hwnd == NULL)
	{
		MessageBox(NULL, TEXT("创建窗口失败."), TEXT("提示"), MB_OK | MB_ICONERROR);
		return 0;
	}

	// 四、显示 更新
	ShowWindow(hwnd, iCmdShow);
	UpdateWindow(hwnd);

	initMap(hwnd);


	// 五、消息循环过程
	MSG msg = { 0 };			// 定义并初始化msg
	while (msg.message != WM_QUIT)		// 使用while循环，如果消息不是WM_QUIT消息，就直接继续循环
	{
		if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))  // 查看应用程序消息队列，有消息时将队列中消息派发出去
		{
			TranslateMessage(&msg);		// 将虚拟键消息转换成字符消息
			DispatchMessage(&msg);		// 分发一个消息给窗口程序
		}
		drawMap(hwnd);
		
	}

	return msg.wParam;
}

LRESULT CALLBACK WindProcFunc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)		// 窗口过程函数
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
		// 窗口消毁消息
	case WM_DESTROY://按下esc
	{
		// 发送WM_QUIT消息，通知线程消息检索循环，清除窗口主程序即可退出
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
		case VK_RIGHT://向右
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
		case VK_LEFT://向左
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
			case 1://围墙
				BitBlt(g_hdc, j * 50, i * 50, 50, 50, g_mdc[0], 0, 0, SRCCOPY);
				break;
			case 2://人
				BitBlt(g_hdc, j * 50, i * 50, 50, 50, g_mdc[1], 0, 0, SRCCOPY);
				break;
			case 3://箱子
				BitBlt(g_hdc, j * 50, i * 50, 50, 50, g_mdc[3], 0, 0, SRCCOPY);
				break;
			case 8://箱子在目的地上
				BitBlt(g_hdc, j * 50, i * 50, 50, 50, g_mdc[2], 0, 0, SRCCOPY);
				break;
			case 5://目的地
				BitBlt(g_hdc, j * 50, i * 50, 50, 50,g_mdc[4] , 0, 0, SRCCOPY);
				break;
			case 7:
				BitBlt(g_hdc, j * 50, i * 50, 50, 50, g_mdc[1], 0, 0, SRCCOPY);
				break;
			}
		}
	}
}