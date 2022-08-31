#include <Windows.h>
#include <cstring>

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM IParam)
{
	switch (message)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_LBUTTONDOWN:
		MessageBox(NULL, (LPCTSTR)"YOU", (LPCTSTR)"Message", NULL);
		break;
	case WM_KEYDOWN:
		if (wParam == 0x41)
			MessageBox(NULL, (LPCTSTR)"THE", (LPCTSTR)"KEYDOWN", NULL);
		else MessageBox(NULL, (LPCTSTR)"THE", (LPCTSTR)"KEY", NULL);
		break;
	default:
		return DefWindowProc(hwnd, message, wParam, IParam);
	}
	return 0;
}
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR ipCmdLine, int nShowCmd)
{
	WNDCLASS wndclass;
	MSG msg;
	char lpszClassName[] = "窗口";
	char lpszTitle[] = "My_window";
	wndclass.style = 0;
	wndclass.lpfnWndProc = WndProc;
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	wndclass.hInstance = hInstance;
	wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndclass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wndclass.lpszMenuName = NULL;
	wndclass.lpszClassName = (LPCTSTR)lpszClassName;
	//注册窗口类
	if (!RegisterClass(&wndclass))
	{
		MessageBeep(0);
		return 0;
	}
	//创建窗口
	HWND hwndMain = CreateWindow((LPCTSTR)lpszClassName, (LPCTSTR)lpszTitle,
		WS_POPUP | WS_OVERLAPPEDWINDOW,
		0,
		0,
		500,
		500,
		NULL,
		NULL,
		hInstance,
		NULL);
	ShowWindow(hwndMain, 2);
	UpdateWindow(hwndMain);
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return true;
}