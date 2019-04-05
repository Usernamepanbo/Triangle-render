// Win32Project2.cpp : ����Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "stdlib.h"
#include "Win32Project2.h"

#define MAX_LOADSTRING 100

// ȫ�ֱ���: 
HWND	  hwnd;									// ��ǰ����
HINSTANCE hInst;                                // ��ǰʵ��
WCHAR szTitle[MAX_LOADSTRING];                  // �������ı�
WCHAR szWindowClass[MAX_LOADSTRING];            // ����������

// �˴���ģ���а����ĺ�����ǰ������: 
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);
VOID				RefreshTriangle();
void				ClearWindowColor();
ImVec2 vertexMax, vertexMin, vertexMid;
ImVec2 vertex1, vertex2, vertex3;

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: �ڴ˷��ô��롣

    // ��ʼ��ȫ���ַ���
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_WIN32PROJECT2, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // ִ��Ӧ�ó����ʼ��: 
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_WIN32PROJECT2));

    MSG msg;

    // ����Ϣѭ��: 
    while (GetMessage(&msg, nullptr, 0, 0) && msg.message != WM_QUIT)
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}

//
//  ����: MyRegisterClass()
//
//  Ŀ��: ע�ᴰ���ࡣ
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_WIN32PROJECT2));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_WIN32PROJECT2);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//   ����: InitInstance(HINSTANCE, int)
//
//   Ŀ��: ����ʵ�����������������
//
//   ע��: 
//
//        �ڴ˺����У�������ȫ�ֱ����б���ʵ�������
//        ��������ʾ�����򴰿ڡ�
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // ��ʵ������洢��ȫ�ֱ�����

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   hwnd = hWnd;

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   vertex1.x = 100;
   vertex1.y = 100;
   vertex2.x = 100;
   vertex2.y = 200;
   vertex3.x = 200;
   vertex3.y = 200;
   ClearWindowColor();

   return TRUE;
}

//  ����: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  Ŀ��:    ���������ڵ���Ϣ��
//
//  WM_COMMAND  - ����Ӧ�ó���˵�
//  WM_PAINT    - ����������
//  WM_DESTROY  - �����˳���Ϣ������
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // �����˵�ѡ��: 
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            // TODO: �ڴ˴����ʹ�� hdc ���κλ�ͼ����...
            EndPaint(hWnd, &ps);
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
	case WM_LBUTTONDOWN:
		RefreshTriangle();
		break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// �����ڡ������Ϣ�������
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}

void GetSortVecY(ImVec2 vertex1, ImVec2 vertex2, ImVec2 vertex3, ImVec2& vertexMax, ImVec2& vertexMid, ImVec2& vertexMin)
{
	if (vertex1.y >= vertex2.y)
	{
		if (vertex2.y >= vertex3.y)
		{
			vertexMax = vertex1;
			vertexMid = vertex2;
			vertexMin = vertex3;
		}
		else if (vertex3.y >= vertex1.y)
		{
			vertexMax = vertex3;
			vertexMid = vertex1;
			vertexMin = vertex2;
		}
		else
		{
			vertexMax = vertex1;
			vertexMid = vertex3;
			vertexMin = vertex2;
		}
	}
	else
	{
		if (vertex3.y >= vertex2.y)
		{
			vertexMax = vertex3;
			vertexMid = vertex2;
			vertexMin = vertex1;
		}
		else if (vertex1.y >= vertex3.y)
		{
			vertexMax = vertex2;
			vertexMid = vertex1;
			vertexMin = vertex3;
		}
		else
		{
			vertexMax = vertex2;
			vertexMid = vertex3;
			vertexMin = vertex1;
		}
	}
}

float GetPointX(ImVec2 begin, ImVec2 end, float posY)
{
	ImVec2 posP;
	if (begin.x == end.x)
	{
		return end.x;
	}
	else
	{
		float k = (begin.y - end.y) / (begin.x - end.x);
		float b = begin.y - k * begin.x;
		return (posY - b) / k;
	}
}

void RedrawTriangle(ImVec2 vertexa, ImVec2 vertexb, ImVec2 vertexc, COLORREF color)
{
	// A:vertexMax B:vertexMid C:vertexMin
	GetSortVecY(vertexa, vertexb, vertexc, vertexMax, vertexMid, vertexMin);
	ImVec2 &A = vertexMax;
	ImVec2 &B = vertexMid;
	ImVec2 &C = vertexMin;

	HDC dc = GetWindowDC(hwnd);
	float point1 = 0.0f, point2 = 0.0f, temp = 0.0f;
	for (int i = (int)C.y; i < (int)B.y; ++i)
	{
		point1 = GetPointX(A, C, (float)i);
		point2 = GetPointX(B, C, (float)i);
		temp = point1;
		if (point1 > point2)
		{
			temp = point1;
			point1 = point2;
			point2 = temp;
		}
		for (int j = (int)point1; j < (int)point2; ++j)
		{
			SetPixel(dc, i, j, color);
		}
	}
	for (int i = (int)B.y; i < (int)A.y; ++i)
	{
		point1 = GetPointX(A, C, (float)i);
		point2 = GetPointX(A, B, (float)i);
		temp = point1;
		if (point1 > point2)
		{
			temp = point1;
			point1 = point2;
			point2 = temp;
		}
		for (int j = (int)point1; j < (int)point2; ++j)
		{
			SetPixel(dc, i, j, color);
		}
	}
}

VOID RefreshTriangle()
{
	COLORREF color = RGB(255, 255, 255);
	RedrawTriangle(vertex1, vertex2, vertex3, color);

	RECT rect;
	GetWindowRect(hwnd, &rect);
	ImVec2 display = ImVec2((float)(rect.left), (float)(rect.top));
	int rangeX = rect.right - rect.left;
	int rangeY = rect.bottom - rect.top;
	if (rangeX == 0 || rangeY == 0)
	{
		return;
	}
	vertex1 = ImVec2((float)(rand() % rangeX), (float)(rand() % rangeY));
	vertex2 = ImVec2((float)(rand() % rangeX), (float)(rand() % rangeY));
	vertex3 = ImVec2((float)(rand() % rangeX), (float)(rand() % rangeY));

	//Sleep(5000);
	color = RGB(255, 0, 0);
	RedrawTriangle(vertex1, vertex2, vertex3, color);
}

void ClearWindowColor()
{
	RECT rect;
	GetWindowRect(hwnd, &rect);
	HDC dc = GetWindowDC(hwnd);

	COLORREF color = RGB(255, 255, 255);
	for (int i = rect.left; i <= rect.right; ++i)
	{
		for (int j = rect.top; j < rect.bottom; ++j)
		{
			SetPixel(dc, i, j, color);
		}
	}
}
