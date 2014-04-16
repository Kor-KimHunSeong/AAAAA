#include <windows.h>
#include <vector>
#include "resource.h"
#include <math.h>

using namespace std;

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
HINSTANCE g_hInst;
LPCTSTR lpszClass = TEXT("¿¬½À");

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdParam, int nCmdShow)
{
	HWND hWnd;
	MSG Message;
	WNDCLASS WndClass;
	g_hInst = hInstance;

	WndClass.cbClsExtra = 0;
	WndClass.cbWndExtra = 0;
	WndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	WndClass.hIcon = LoadIcon(NULL, IDI_ASTERISK);
	WndClass.hInstance = hInstance;
	WndClass.lpfnWndProc = WndProc;
	WndClass.lpszClassName = lpszClass;
	WndClass.lpszMenuName = MAKEINTRESOURCE(IDR_MENU1);
	WndClass.style = CS_HREDRAW | CS_VREDRAW;
	RegisterClass(&WndClass);

	hWnd = CreateWindow(lpszClass, lpszClass, (WS_OVERLAPPED | 
												WS_CAPTION |
												WS_SYSMENU | 
												WS_THICKFRAME | 
												WS_MINIMIZEBOX | 
												WS_MAXIMIZEBOX),
		CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
		NULL, (HMENU) NULL, hInstance, NULL);
	ShowWindow(hWnd, nCmdShow);

	SetTimer(hWnd, 11, 100, NULL);

	while(GetMessage(&Message, NULL, 0, 0))
	{
		TranslateMessage(&Message);
		DispatchMessage(&Message);
	}
	return (int)Message.wParam;
}

struct tagLine
{
	POINT Pos;
	bool Start;
};

enum SELECT_DRAW
{
	S_NONE = 0,
	S_RECT,
	S_CIRCLE,
	S_LINE,
	S_PEN
};

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;

	static bool Move = false;
	static int nSelect = 0;
	static vector<tagLine>	vLine;

	static int time = 0;
	static float angle = 0;

	switch(iMessage)
	{
	case WM_TIMER:
		{
			vLine.clear();
			time += 30;
			angle = (float)time/180 * 3.141592;
			if(angle > 3.141592 * 2.0f)
			{
				time = 0;
			}
		}
		InvalidateRect(hWnd, NULL, FALSE);
		break;

	case WM_COMMAND:
		{
			switch(LOWORD(wParam))
			{
			case ID_FILE_CREATE:
				vLine.clear();
				break;
			case ID_FILE_END:
				DestroyWindow(hWnd);
				break;

			case ID_DRAW_NONE:
				nSelect=S_NONE;
				break;
			case ID_DRAW_RECT:
				nSelect=S_RECT;
				break;
			case ID_DRAW_CIRCLE:
				nSelect=S_CIRCLE;
				break;
			case ID_DRAW_LINE:
				nSelect=S_LINE;
				break;
			case ID_DRAW_PEN:
				nSelect=S_PEN;
				break;

			case ID_COLOR_SELECT:
				break;
			}
		}
		break;

	case WM_MOUSEMOVE:
		{
			if(Move)
			{
				tagLine Temp;
				Temp.Pos.x = LOWORD(lParam);
				Temp.Pos.y = HIWORD(lParam);
				Temp.Start = false;
				vLine.push_back(Temp);
			}
			InvalidateRect(hWnd, NULL, FALSE);
		}
		break;

	case WM_LBUTTONDOWN:
		{
			Move = true;
			tagLine Temp;
			Temp.Pos.x = LOWORD(lParam);
			Temp.Pos.y = HIWORD(lParam);
			Temp.Start = true;

			vLine.push_back(Temp);
		}
		break;

	case WM_LBUTTONUP:
		{
			Move = false;
		}
		break;

	case WM_PAINT:
		{
			hdc = BeginPaint(hWnd, &ps);

			RECT rc;
			GetClientRect(hWnd, &rc);

			HDC memDC = CreateCompatibleDC(hdc);
			HBITMAP membit = CreateCompatibleBitmap(hdc, rc.right, rc.bottom);
			HBITMAP oldbit = (HBITMAP) SelectObject(memDC, membit);
			FillRect(memDC, &rc, (HBRUSH)(WHITE_BRUSH));

			for(int i=0; i<vLine.size(); ++i)
			{
				if(vLine[i].Start)
				{
					MoveToEx(memDC, vLine[i].Pos.x,vLine[i].Pos.y, NULL);
				}
				else
				{
					LineTo(memDC, vLine[i].Pos.x, vLine[i].Pos.y);
				}
			}

			//fscanf_s()
			//DrawTextA(memDC, )

			MoveToEx(memDC, 400,300,NULL);

			for(float i=0; i<angle; i+=0.1f)
			{
				float x = cos(i) * 100.f;
				float y = sin(i) * 100.f;
				LineTo(memDC, x+300, -y+300);

			}

			HDC hdcbm = CreateCompatibleDC(memDC);
			HBITMAP hbmold = (HBITMAP) SelectObject(hdcbm, g_hInst);
			BitBlt(hdc, 0,0, rc.right, rc.bottom, memDC, 0,0, SRCCOPY);
			SelectObject(hdcbm, hbmold);
			DeleteObject(hdcbm);

			SelectObject(memDC, oldbit);
			DeleteObject(membit);
			DeleteDC(memDC);

			EndPaint(hWnd, &ps);
			break;
		}
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}
	return (DefWindowProc(hWnd, iMessage, wParam, lParam));
}