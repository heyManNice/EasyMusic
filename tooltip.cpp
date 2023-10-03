#include <windows.h>
#include "myhead.h"
#include <string>
#include <algorithm>
#include <cwctype>

std::wstring tooltip_str=L"初次显示的文字";

LRESULT CALLBACK tooltipProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam){
	switch(Message) {
		case WM_PAINT:
			{
				PAINTSTRUCT ps;
				HDC hdc = BeginPaint(hwnd, &ps);
				HPEN hpen = CreatePen(PS_SOLID, 1, RGB(77,62,64));
				SelectObject(hdc, (HGDIOBJ)hpen);
				Rectangle(hdc,0,0,ps.rcPaint.right,ps.rcPaint.bottom);
				
				HFONT hFont = CreateFont(DDPI(13.333333), 0, 0, 0, 400, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, TEXT("Arial"));
				HGDIOBJ hOldFont = SelectObject(hdc, hFont);
				SetTextColor(hdc, RGB(77,62,64));
				DrawTextW(hdc,tooltip_str.c_str(),-1,&ps.rcPaint,DT_CENTER|DT_VCENTER|DT_SINGLELINE);
				DeleteObject(hFont);
				DeleteObject(hpen);
				ReleaseDC(hwnd, hdc);
				EndPaint(hwnd, &ps);
			}
		default:
			return DefWindowProc(hwnd, Message, wParam, lParam);
	}
	return 0;
}


int tooltip_tooltip(HINSTANCE hInstance){
	WNDCLASSEX tooltipClass;
	memset(&tooltipClass,0,sizeof(tooltipClass));
	tooltipClass.cbSize		 = sizeof(WNDCLASSEX);
	tooltipClass.lpfnWndProc = tooltipProc;
	tooltipClass.hInstance	 = hInstance;
	tooltipClass.style		 = CS_HREDRAW | CS_VREDRAW | CS_PARENTDC;
	tooltipClass.hbrBackground = CreateSolidBrush(RGB(255,255,255));
	tooltipClass.lpszClassName = "tooltip";
	if(!RegisterClassEx(&tooltipClass)) {
		MessageBox(NULL, "窗口类注册失败!","错误!",MB_ICONEXCLAMATION|MB_OK);
		PostQuitMessage(0);
	}
	HWNDM[H_tooltip] = CreateWindowEx(WS_EX_TOPMOST|WS_EX_TOOLWINDOW,"tooltip",NULL, 
									WS_POPUP,0, 0,
									0, 0,HWNDM[H_MAIN_WIN],
									NULL, hInstance, NULL);
	//SetWindowPos(HWNDM[H_tooltip],HWND_TOP,400,400,66,26,SWP_HIDEWINDOW);
	return 0;
}
int tooltip_show(std::wstring str,int x, int y){
	int enNum = 0;
	int enSupNum=0;
	int nuNum=0;
	for(int i = 0; i < str.size(); i++){
		if(std::iswalpha(str[i])){
			enNum++;
		}
		if(std::iswupper(str[i])){
			enSupNum++;
		}
		if(std::iswdigit(str[i])){
			nuNum++;
		}
	}
	int enLowNum = enNum-enSupNum;
	int otherNum = str.size() - enLowNum;
	//printf("%d",enLowNum);
	SetWindowPos(HWNDM[H_tooltip],HWND_TOP,x+DDPI(11),y+DDPI(16.666666),nuNum*DDPI(1)+enLowNum*DDPI(4.666666)+enSupNum*DDPI(5)+otherNum*DDPI(6.666666)+DDPI(5.333333),DDPI(18.666666),SWP_NOOWNERZORDER);
	tooltip_str = str;
	if(!IsWindowVisible(HWNDM[H_tooltip])){
		ShowWindow(HWNDM[H_tooltip],SW_SHOWNA);
	}
	//AnimateWindow(HWNDM[H_tooltip],300,AW_BLEND);
	//这个动画是先显示窗体再绘制内容的，不知道怎么解决
	InvalidateRect(HWNDM[H_tooltip], NULL, FALSE);
	return 0;
}
int tooltip_hide(){
	SetWindowPos(HWNDM[H_tooltip],HWND_TOP,0,0,0,0,SWP_HIDEWINDOW|SWP_NOSIZE|SWP_NOMOVE);
	return 0;
}
