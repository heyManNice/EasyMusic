#include "tooltip.h"
RunningInfo running_info;

LRESULT CALLBACK TooltipProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam);



Tooltip::Tooltip()
{
    WNDCLASSEX tooltipClass;
	memset(&tooltipClass,0,sizeof(tooltipClass));
	tooltipClass.cbSize		 = sizeof(WNDCLASSEX);
	tooltipClass.lpfnWndProc = TooltipProc;
	tooltipClass.hInstance	 = running_info.hInstance;
	tooltipClass.style		 = CS_HREDRAW | CS_VREDRAW | CS_PARENTDC;
	tooltipClass.hbrBackground = CreateSolidBrush(RGB(255,255,255));
	tooltipClass.lpszClassName = TEXT("tooltip");
	if(!RegisterClassEx(&tooltipClass)) {
		MessageBoxW(NULL, L"窗口类注册失败!",L"错误!",MB_ICONEXCLAMATION|MB_OK);
		PostQuitMessage(0);
	}
	this->hwnd_ = CreateWindowExA(WS_EX_TOPMOST|WS_EX_TOOLWINDOW,"tooltip",NULL, 
									WS_POPUP,0, 0,
									0, 0,running_info.hMainWin,
									NULL, running_info.hInstance, NULL);
}

Tooltip::~Tooltip()
{
}
int Tooltip::Show_(std::wstring str,int x, int y){
    int LowerCase=0, UpperCase=0,digit=0, character=0,other=0;
    for (int i = 0; i < str.size(); )
	{
        if (str[i] >= 'a' && str[i] <= 'z')
		{
            LowerCase ++;i++;
		}
        else if (str[i] >= 'A' && str[i] <= 'Z')
		{
            UpperCase ++;i++;
		}
        else if (str[i] >= '0' && str[i] <= '9')
		{
            digit ++;i++;
		}else{
            other ++;i++;
        }
    }
	SetWindowPos(this->hwnd_,HWND_TOP,x+DDPI(11),y+DDPI(16.666666),digit*DDPI(4)+LowerCase*DDPI(4)+UpperCase*DDPI(5)+other*DDPI(12)+DDPI(5.333333),DDPI(18.666666),SWP_NOOWNERZORDER);
	this->Text_ = str;
	if(!IsWindowVisible(this->hwnd_)){
		ShowWindow(this->hwnd_,SW_SHOWNA);
	}
	InvalidateRect(this->hwnd_, NULL, FALSE);
	return 0;
}

int Tooltip::Hide_(){
	SetWindowPos(this->hwnd_,HWND_TOP,0,0,0,0,SWP_HIDEWINDOW|SWP_NOSIZE|SWP_NOMOVE);
	return 0;
}

int Tooltip::OnPaint_(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam){
    PAINTSTRUCT ps;
    HDC hdc = BeginPaint(hwnd, &ps);
    HPEN hpen = CreatePen(PS_SOLID, 1, RGB(77,62,64));
    SelectObject(hdc, (HGDIOBJ)hpen);
    Rectangle(hdc,0,0,ps.rcPaint.right,ps.rcPaint.bottom);
    
    HFONT hFont = CreateFont(DDPI(13.333333), 0, 0, 0, 400, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, TEXT("Arial"));
    HGDIOBJ hOldFont = SelectObject(hdc, hFont);
    SetTextColor(hdc, RGB(77,62,64));
    DrawTextW(hdc,this->Text_.c_str(),-1,&ps.rcPaint,DT_CENTER|DT_VCENTER|DT_SINGLELINE);
    DeleteObject(hFont);
    DeleteObject(hpen);
    ReleaseDC(hwnd, hdc);
    EndPaint(hwnd, &ps);
    return 0;
}


LRESULT CALLBACK TooltipProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam){
	switch(Message) {
		case WM_PAINT:
			tooltip.OnPaint_(hwnd,Message,wParam,lParam);
            break;
		default:
			return DefWindowProc(hwnd, Message, wParam, lParam);
	}
	return 0;
}
