#include "myhead.h"


struct mouseState
{
	int mouseHover = 0;
};

mouseState btn_close;
mouseState btn_tofullS;
mouseState btn_tosmallS;
mouseState btn_tomini;

struct ProgressMouseState_struct
{
	int progress = 0;
	int btn_group[5] = {0,0,0,0,0};
	int btn_groupTimerIndex = -1;
};
struct PlayingSetMouseState_struct
{
	int btn_group[3] = {0,0,0};
	int btn_groupTimerIndex = -1;
};

ProgressMouseState_struct ProgressMouseState;
PlayingSetMouseState_struct PlayingSetMouseState;
SearchResultPage_struct SearchResultPage;
SearchItemWidth_struct SearchItemWidth;

//主窗口事件
LRESULT CALLBACK WndProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam) {
	switch(Message) {
		case WM_GETMINMAXINFO:
			{
				MINMAXINFO* pMMI = (MINMAXINFO*)lParam;
			    pMMI->ptMinTrackSize.x = DPI(1022);
			    pMMI->ptMinTrackSize.y = DPI(670);
			    return 0;
			}
			break;
		case WM_PAINT:
			{	
				RECT Mainrect;
				GetWindowRect(hwnd, &Mainrect);
				int height = Mainrect.bottom - Mainrect.top;
				int width = Mainrect.right - Mainrect.left;
				PAINTSTRUCT ps;
			    HDC hdc = BeginPaint(hwnd, &ps);
			    HBRUSH hBrush = CreateSolidBrush(RGB(255,255,255));
			    HBRUSH hOldBrush = (HBRUSH)SelectObject(hdc, hBrush);
			    
			    HPEN hPen = CreatePen(PS_SOLID, 1, RGB(255,255,255));
			    HPEN hOldPen = (HPEN)SelectObject(hdc, hPen);
			    
			    Rectangle(hdc, 0, height-DPI(67), width, height);
			    
			    
			    //foot的分割线
			    HPEN hpen_lin1 = CreatePen(PS_SOLID, 1, RGB(224,224,224));
			    SelectObject(hdc, hpen_lin1);
			    
			    MoveToEx(hdc, 0, height-DPI(67), NULL);
			    LineTo(hdc, width, height-DPI(67));
			    
			    HPEN hpen_lin2 = CreatePen(PS_SOLID, 1, RGB(240,240,240));
				SelectObject(hdc, hpen_lin2);
				MoveToEx(hdc, 0, height-DPI(67)+1, NULL);
				LineTo(hdc, width, height-DPI(67)+1);
				
				SelectObject(hdc, myPEN["1_gray_153"]);
				//Rectangle(hdc, width-DPI(0), height-DPI(0), width-DPI(4), height-DPI(4));
				
				//右下角的拖动标志
				MoveToEx(hdc, width-DPI(12), height-DPI(4), NULL);
				LineTo(hdc, width-DPI(4), height-DPI(12));
				
				MoveToEx(hdc, width-DPI(9), height-DPI(4), NULL);
				LineTo(hdc, width-DPI(4), height-DPI(9));
								
				MoveToEx(hdc, width-DPI(6), height-DPI(4), NULL);
				LineTo(hdc, width-DPI(4), height-DPI(6));
			    
			    SelectObject(hdc, hOldBrush);
			    SelectObject(hdc, hOldPen);
			    
			    
			    DeleteObject(hpen_lin2);
			    DeleteObject(hpen_lin1);
			    DeleteObject(hPen);
			    DeleteObject(hBrush);
			    ReleaseDC(hwnd, hdc);
			    EndPaint(hwnd, &ps);
			    return 0;
			}
			break;
		case WM_DESTROY: {
			PostQuitMessage(0);
			break;
		}
		case WM_NCACTIVATE:
		    if (wParam == 0) {
		        return 0;
		    }
		    break;
		case WM_SIZE:{
				//响应式布局
				RECT myrect;
				GetWindowRect(hwnd, &myrect);
				int width = myrect.right - myrect.left;
				int height = myrect.bottom - myrect.top;
				if(HWNDM[H_MYHEAD]){
					SetWindowPos(HWNDM[H_MYHEAD],HWND_TOP,0,0,width,DPI(60),SWP_NOMOVE | SWP_ASYNCWINDOWPOS | SWP_NOOWNERZORDER);
				}
				if(HWNDM[H_OPBTN]){
					SetWindowPos(HWNDM[H_OPBTN],HWND_TOP,width-DPI(190),DPI(15),DPI(173),DPI(37),SWP_NOSIZE | SWP_ASYNCWINDOWPOS | SWP_NOOWNERZORDER);
				}
				if(HWNDM[H_MYFOOT]){
					SetWindowPos(HWNDM[H_MYFOOT],HWND_TOP,0,height-DPI(60),width,DPI(60),SWP_ASYNCWINDOWPOS | SWP_NOOWNERZORDER);
				}
				if(HWNDM[H_LMENU]){
					SetWindowPos(HWNDM[H_LMENU],HWND_TOP,0,DPI(60),DPI(200),height-DPI(127),SWP_ASYNCWINDOWPOS | SWP_NOOWNERZORDER);
				}
				if(HWNDM[H_PlayingInfo_m]){
					SetWindowPos(HWNDM[H_PlayingInfo_m],HWND_TOP,DPI(12),height-DPI(55),DPI(250),DPI(43),SWP_NOSIZE | SWP_ASYNCWINDOWPOS | SWP_NOOWNERZORDER);
				}
				if(HWNDM[H_PlayingSet_m]){
					SetWindowPos(HWNDM[H_PlayingSet_m],HWND_TOP,width-DPI(250)-DPI(12),height-DPI(55),DPI(250),DPI(43),SWP_NOSIZE | SWP_ASYNCWINDOWPOS | SWP_NOOWNERZORDER);
				}
				if(HWNDM[H_PlayingControl]){
					int PcontrolWidth = DPI(420);
					SetWindowPos(HWNDM[H_PlayingControl],HWND_TOP,(width-PcontrolWidth)/2,height-DPI(67-10),PcontrolWidth,DPI(67-10*2),SWP_ASYNCWINDOWPOS | SWP_NOOWNERZORDER);
				}
				if(HWNDM[H_VolumePanel]){
					SetWindowPos(HWNDM[H_VolumePanel],HWND_TOP,width-DPI(126),height-DPI(49+100),DPI(30),DPI(100),SWP_NOSIZE | SWP_ASYNCWINDOWPOS | SWP_NOOWNERZORDER);
				}
				if(HWNDM[H_SearchResultPage]){
					SetWindowPos(HWNDM[H_SearchResultPage],HWND_TOP,DPI(200),DPI(60),width-DPI(200),height-DPI(60)-DPI(67),SWP_ASYNCWINDOWPOS | SWP_NOOWNERZORDER);
					RECT SearchResultPageRect;
					GetWindowRect(HWNDM[H_SearchResultPage], &SearchResultPageRect);
					int sheight = SearchResultPageRect.bottom - SearchResultPageRect.top;
					int swidth = SearchResultPageRect.right - SearchResultPageRect.left;
					for(int i = 0;i<SearchItemInfo.size();i++){
						if(i>30){
							//防止意外出现死循环，手动退出
							PostQuitMessage(20);
							break;
						}
						SetWindowPos(SearchItemInfo[i].hwnd,HWND_TOP, SearchItemInfo[i].itemRect.left,SearchItemInfo[i].itemRect.top,swidth- SearchItemInfo[i].itemRect.left,DPI(34),SWP_ASYNCWINDOWPOS | SWP_NOOWNERZORDER);
					}
				}
				
				

				break;
			}
		case WM_NCCALCSIZE:{
			if (wParam)
			{
				return 0;
			}
			break;
		}
		case WM_NCHITTEST:{
			if (!IsZoomed(hwnd)){
				int x = 8;
				RECT rc; GetClientRect(hwnd, &rc);
				POINT pt; GetCursorPos(&pt); ScreenToClient(hwnd, &pt);
				if (pt.x >= rc.right - x){
					if (pt.y >= rc.bottom - x)return HTBOTTOMRIGHT;
					return HTRIGHT;
					}
				if (pt.y >= rc.bottom - x)return HTBOTTOM;
			}
			return HTCLIENT;
			break;
		}
		case WM_MOUSEMOVE:{
			for(int i = 0;i<SearchItemInfo.size();i++){
				if(SearchItemInfo[i].mouseHover==1){
					SearchItemInfo[i].mouseHover = 0;
					InvalidateRect(SearchItemInfo[i].hwnd, NULL, TRUE);
				}
			}
			break;
		}
		default:
			return DefWindowProc(hwnd, Message, wParam, lParam);
	}
	return 0;
}

//head栏事件
LRESULT CALLBACK mytitleProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam) {
	switch(Message) {
		case WM_NCHITTEST:
			{
			    SendMessage(GetParent(hwnd),WM_SYSCOMMAND,SC_MOVE|HTCAPTION,0);
			}
			return HTCLIENT;
			break;
		case WM_DESTROY: {
			PostQuitMessage(0);
			break;
		}
		default:
			return DefWindowProc(hwnd, Message, wParam, lParam);
	}
	return 0;
}
//右上角操作按钮组事件
LRESULT CALLBACK myOP_BtnProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam) {
	switch(Message) {
		case WM_NCHITTEST:
			{
			    SendMessage(GetParent(hwnd),Message,wParam,lParam);
			}
			return HTCLIENT;
			break;
		case WM_DESTROY: {
			PostQuitMessage(0);
			break;
		}
		default:
			return DefWindowProc(hwnd, Message, wParam, lParam);
	}
	return 0;
}
//输入框事件
LRESULT CALLBACK Edit_out_Proc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam) {
	switch(Message) {
		case WM_CTLCOLOREDIT:
			{
				HDC hdcEdit = (HDC)wParam;
				HWND hwndEdit = (HWND)lParam;
				HBRUSH hbrBkgnd = NULL;
				if (GetDlgCtrlID(hwndEdit) == 23)
				{
					SetTextColor(hdcEdit, RGB(255, 255, 255));
					SetBkColor(hdcEdit, RGB(227, 62, 62));
					hbrBkgnd = CreateSolidBrush(RGB(227, 62, 62));
				}
				return (INT_PTR)hbrBkgnd; // 返回画刷句柄给系统
			}
		case WM_DESTROY: {
			PostQuitMessage(0);
			break;
		}
		default:
			return DefWindowProc(hwnd, Message, wParam, lParam);
	}
	return 0;
}
//关闭按钮事件
LRESULT CALLBACK closeProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam) {
	switch(Message) {
		case WM_NCHITTEST:
			{
			    SendMessage(GetParent(hwnd),Message,wParam,lParam);
			}
			return HTCLIENT;
			break;
		case WM_SETCURSOR:
			{
				HCURSOR cur = LoadCursorA(NULL,IDC_HAND);
				SetCursor(cur);
			}
			break;
		case WM_TIMER:
			{
				if(wParam==777){
					POINT pt;
					GetCursorPos(&pt);
					if(hwnd == WindowFromPoint(pt)){
						tooltip_show(L"关闭",pt.x,pt.y);
					}
					KillTimer(hwnd,777);
				}
				break;
			}
		case WM_MOUSEMOVE:
			{
				
				TRACKMOUSEEVENT close;
				close.cbSize = sizeof(TRACKMOUSEEVENT);
				close.dwFlags = TME_HOVER | TME_LEAVE;
				close.hwndTrack = hwnd;
				close.dwHoverTime = 10;
				int tme = TrackMouseEvent(&close);
			}
			break;
		case WM_MOUSEHOVER:
			{
				if(!IsWindowVisible(HWNDM[H_tooltip])){
					SetTimer(hwnd,777,500,NULL);
				}
				btn_close.mouseHover = 1;
				InvalidateRect(hwnd, NULL, FALSE);
			}
			break;
		case WM_MOUSELEAVE:
			{
				tooltip_hide();
				btn_close.mouseHover = 0;
				InvalidateRect(hwnd, NULL, FALSE);
			}
			break;
		case WM_PAINT:
			{
				PAINTSTRUCT ps;
	            HDC hdc = BeginPaint(hwnd, &ps);
	            HPEN hpen;
	            if(btn_close.mouseHover==1){
					hpen = CreatePen(PS_SOLID, DPIW(1), RGB(255,255,255));
				}else{
					hpen = CreatePen(PS_SOLID, DPIW(1), RGB(251,217,217));
				}
	            HPEN hOldPen = (HPEN)SelectObject(hdc, (HGDIOBJ)hpen);
	            MoveToEx(hdc,DDPI(10.66666),DPI(10),NULL);
	            LineTo(hdc,DPI(22),DPI(22));
	            MoveToEx(hdc,DPI(22),DPI(10),NULL);
	            LineTo(hdc,DDPI(10.66666),DPI(22));
	            
	            SelectObject(hdc, hOldPen);
				DeleteObject(hpen);
	            ReleaseDC(hwnd, hdc);
	            EndPaint(hwnd, &ps);
			}
			return 0;
			break;
		case WM_LBUTTONDOWN:
			{
				PostQuitMessage(0);
			}
			break;
		case WM_DESTROY: 
			{
				PostQuitMessage(0);
				break;
			}
		default:
			DefWindowProc(hwnd, Message, wParam, lParam);
			return 0;
	}
	return 0;
}

//最大化还原按钮
LRESULT CALLBACK tofullSProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam){
	switch(Message) {
		case WM_TIMER:
			{
				if(wParam==777){
					POINT pt;
					GetCursorPos(&pt);
					if(hwnd == WindowFromPoint(pt)){
						if(IsZoomed(HWNDM[H_MAIN_WIN])){
							tooltip_show(L"向下还原",pt.x,pt.y);
						}else{
							tooltip_show(L"最大化",pt.x,pt.y);
						}
					}
					KillTimer(hwnd,777);
				}
				break;
			}
		case WM_MOUSEMOVE:
			{
				TRACKMOUSEEVENT close;
				close.cbSize = sizeof(TRACKMOUSEEVENT);
				close.dwFlags = TME_HOVER | TME_LEAVE;
				close.hwndTrack = hwnd;
				close.dwHoverTime = 10;
				int tme = TrackMouseEvent(&close);
				break;
			}
		case WM_MOUSEHOVER:
			{
				if(!IsWindowVisible(HWNDM[H_tooltip])){
					SetTimer(hwnd,777,500,NULL);
				}
				btn_tofullS.mouseHover = 1;
				InvalidateRect(hwnd, NULL, FALSE);
				break;
			}
		case WM_MOUSELEAVE:
			{
				btn_tofullS.mouseHover = 0;
				tooltip_hide();
				InvalidateRect(hwnd, NULL, FALSE);
				break;
			}
		case WM_SETCURSOR:
			{
				HCURSOR cur = LoadCursorA(NULL,IDC_HAND);
				SetCursor(cur);
				break;
			}
		case WM_LBUTTONDOWN:
			{
				if(IsZoomed(HWNDM[H_MAIN_WIN])){
					ShowWindow(HWNDM[H_MAIN_WIN],SW_RESTORE);
				}else{
					ShowWindow(HWNDM[H_MAIN_WIN],SW_MAXIMIZE);
				}
				InvalidateRect(hwnd, NULL, FALSE);
				break;
			}
		case WM_PAINT:
			{
				PAINTSTRUCT ps;
	            HDC hdc = BeginPaint(hwnd, &ps);
	            HPEN hpen;
	            if(btn_tofullS.mouseHover==1){
					hpen = CreatePen(PS_SOLID, DPIW(1), RGB(255,255,255));
				}else{
					hpen = CreatePen(PS_SOLID, DPIW(1), RGB(251,217,217));
				}
				HPEN hOldPen = (HPEN)SelectObject(hdc,hpen);
				if(IsZoomed(HWNDM[H_MAIN_WIN])){
					//窗口化
					MoveToEx(hdc,DPI(10),DDPI(12.666666),NULL);
					LineTo(hdc,DPI(22),DDPI(12.666666));
					LineTo(hdc,DPI(22),DDPI(22.666666));
					LineTo(hdc,DPI(10),DDPI(22.666666));
					LineTo(hdc,DPI(10),DDPI(12.666666));
					MoveToEx(hdc,DDPI(14.666666),DDPI(10.666666),NULL);
					LineTo(hdc,DPI(22),DDPI(10.666666));
					LineTo(hdc,DPI(24),DDPI(12.666666));
					LineTo(hdc,DPI(24),DDPI(18.666666));
				}else{
					//最大化
		            MoveToEx(hdc,DPI(10),DPI(10),NULL);
		            LineTo(hdc,DDPI(22.666666),DPI(10));
		            LineTo(hdc,DDPI(22.666666),DDPI(23.333333));
		            LineTo(hdc,DPI(10),DDPI(23.333333));
		            LineTo(hdc,DPI(10),DPI(10));
		            
				}
				SelectObject(hdc,hOldPen);
				DeleteObject(hpen);
				ReleaseDC(hwnd, hdc);
				EndPaint(hwnd, &ps);
	            break;
			}
		default:
			return DefWindowProc(hwnd, Message, wParam, lParam);
	}
	return 0;
}
//最小化按钮
LRESULT CALLBACK tosmallSProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam){
	switch(Message) {
		case WM_TIMER:
			{
				if(wParam==777){
					POINT pt;
					GetCursorPos(&pt);
					if(hwnd == WindowFromPoint(pt)){
						tooltip_show(L"最小化",pt.x,pt.y);
					}
					KillTimer(hwnd,777);
				}
				break;
			}
		case WM_MOUSEMOVE:
			{
				TRACKMOUSEEVENT close;
				close.cbSize = sizeof(TRACKMOUSEEVENT);
				close.dwFlags = TME_HOVER | TME_LEAVE;
				close.hwndTrack = hwnd;
				close.dwHoverTime = 10;
				int tme = TrackMouseEvent(&close);
				break;
			}
		case WM_MOUSEHOVER:
			{
				if(!IsWindowVisible(HWNDM[H_tooltip])){
					SetTimer(hwnd,777,500,NULL);
				}
				btn_tosmallS.mouseHover = 1;
				InvalidateRect(hwnd, NULL, FALSE);
				break;
			}
		case WM_MOUSELEAVE:
			{
				btn_tosmallS.mouseHover = 0;
				tooltip_hide();
				InvalidateRect(hwnd, NULL, FALSE);
				break;
			}
		case WM_SETCURSOR:
			{
				HCURSOR cur = LoadCursorA(NULL,IDC_HAND);
				SetCursor(cur);
				break;
			}
		case WM_LBUTTONDOWN:
			{
				ShowWindow(HWNDM[H_MAIN_WIN],SW_MINIMIZE);
				break;
			}
		case WM_PAINT:
			{
				PAINTSTRUCT ps;
	            HDC hdc = BeginPaint(hwnd, &ps);
	            HPEN hpen;
	            if(btn_tosmallS.mouseHover==1){
					hpen = CreatePen(PS_SOLID, DPIW(1), RGB(255,255,255));
				}else{
					hpen = CreatePen(PS_SOLID, DPIW(1), RGB(251,217,217));
				}
				HPEN hOldPen = (HPEN)SelectObject(hdc, (HGDIOBJ)hpen);
				MoveToEx(hdc,DPI(10),DPI(18),NULL);
				LineTo(hdc,DDPI(22.666666),DPI(18));
				
				SelectObject(hdc,hOldPen);
				DeleteObject(hpen);
				ReleaseDC(hwnd, hdc);
				EndPaint(hwnd, &ps);
	            break;
			}
		default:
			return DefWindowProc(hwnd, Message, wParam, lParam);
	}
	return 0;
}
//变迷你按钮
LRESULT CALLBACK tominiProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam){
	switch(Message) {
		case WM_TIMER:
			{
				if(wParam==777){
					POINT pt;
					GetCursorPos(&pt);
					if(hwnd == WindowFromPoint(pt)){
						tooltip_show(L"mini模式(Ctrl+M)",pt.x,pt.y);
					}
					KillTimer(hwnd,777);
				}
				break;
			}
		case WM_MOUSEMOVE:
			{
				TRACKMOUSEEVENT close;
				close.cbSize = sizeof(TRACKMOUSEEVENT);
				close.dwFlags = TME_HOVER | TME_LEAVE;
				close.hwndTrack = hwnd;
				close.dwHoverTime = 10;
				int tme = TrackMouseEvent(&close);
				break;
			}
		case WM_MOUSEHOVER:
			{
				if(!IsWindowVisible(HWNDM[H_tooltip])){
					SetTimer(hwnd,777,500,NULL);
				}
				btn_tomini.mouseHover = 1;
				InvalidateRect(hwnd, NULL, FALSE);
				break;
			}
		case WM_MOUSELEAVE:
			{
				btn_tomini.mouseHover = 0;
				tooltip_hide();
				InvalidateRect(hwnd, NULL, FALSE);
				break;
			}
		case WM_SETCURSOR:
			{
				HCURSOR cur = LoadCursorA(NULL,IDC_HAND);
				SetCursor(cur);
				break;
			}
		case WM_PAINT:
			{
				PAINTSTRUCT ps;
	            HDC hdc = BeginPaint(hwnd, &ps);
	            HPEN hpen;
	            if(btn_tomini.mouseHover==1){
					hpen = CreatePen(PS_SOLID, DPIW(1), RGB(255,255,255));
				}else{
					hpen = CreatePen(PS_SOLID, DPIW(1), RGB(251,217,217));
				}
				HPEN hOldPen = (HPEN)SelectObject(hdc, (HGDIOBJ)hpen);
				MoveToEx(hdc,DDPI(8.666666),DDPI(14.666666),NULL);
				LineTo(hdc,DDPI(8.666666),DPI(10));
				LineTo(hdc,DDPI(22.666666),DPI(10));
				LineTo(hdc,DDPI(22.666666),DPI(22));
				LineTo(hdc,DDPI(18.666666),DPI(22));
				MoveToEx(hdc,DDPI(8.666666),DPI(18),NULL);
				LineTo(hdc,DDPI(15.333333),DPI(18));
				LineTo(hdc,DDPI(15.333333),DPI(22));
				LineTo(hdc,DDPI(8.666666),DPI(22));
				LineTo(hdc,DDPI(8.666666),DPI(18));
				
				SelectObject(hdc,hOldPen);
				DeleteObject(hpen);
				ReleaseDC(hwnd, hdc);
				EndPaint(hwnd, &ps);
	            break;
			}
		default:
			return DefWindowProc(hwnd, Message, wParam, lParam);
	}
	return 0;
}

//搜索栏搜索图标
LRESULT CALLBACK searchProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam){
	switch(Message) {
		case WM_PAINT:
			{
				PAINTSTRUCT ps;
	            HDC hdc = BeginPaint(hwnd, &ps);
	            HPEN hpen = CreatePen(PS_SOLID, DPI(1), RGB(251,217,217));
				HPEN hOldPen = (HPEN)SelectObject(hdc,hpen);
				SelectObject(hdc, GetStockObject(NULL_BRUSH));
				Ellipse (hdc, DDPI(5.333333), DPI(6), DDPI(15.333333), DPI(16));
				MoveToEx(hdc,DDPI(13.55),DDPI(14.666),NULL);
				LineTo(hdc,DDPI(17.333333),DPI(18));
				
				SelectObject(hdc,hOldPen);
				DeleteObject(hpen);
				ReleaseDC(hwnd, hdc);
				EndPaint(hwnd, &ps);
	            break;
			}
		default:
			return DefWindowProc(hwnd, Message, wParam, lParam);
	}
	return 0;
}
//logo过程
LRESULT CALLBACK logoProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam){
	switch(Message) {
		case WM_PAINT:
			{
				PAINTSTRUCT ps;
	            HDC hdc = BeginPaint(hwnd, &ps);
	            HPEN hpen = CreatePen(PS_NULL, 0, RGB(0,0,0));
	            HPEN holdpen = (HPEN)SelectObject(hdc, (HGDIOBJ)hpen);
				SelectObject(hdc, GetStockObject(WHITE_BRUSH));
				Ellipse (hdc, DDPI(5), DDPI(3), DDPI(31), DDPI(29));
				SelectObject(hdc, GetStockObject(NULL_BRUSH));
				
				HPEN hpen_red = CreatePen(PS_SOLID, DPI(2), RGB(236,65,65));
				SelectObject(hdc, (HGDIOBJ)hpen_red);
				MoveToEx(hdc,DDPI(22.6),DDPI(8.7),NULL);
				LineTo(hdc,DDPI(20.5),DDPI(8.1));
				LineTo(hdc,DDPI(18.7),DDPI(9.6));
				LineTo(hdc,DDPI(20.3),DDPI(16.1));
				LineTo(hdc,DDPI(18.2),DDPI(18.5));
				LineTo(hdc,DDPI(15.6),DDPI(16));
				LineTo(hdc,DDPI(17.4),DDPI(12.9));
				LineTo(hdc,DDPI(21.3),DDPI(12.6));
				LineTo(hdc,DDPI(24.4),DDPI(16.6));
				LineTo(hdc,DDPI(23.5),DDPI(20.5));
				LineTo(hdc,DDPI(18.9),DDPI(23.4));
				LineTo(hdc,DDPI(13.8),DDPI(21.9));
				LineTo(hdc,DDPI(11),DDPI(17.2));
				LineTo(hdc,DDPI(12.4),DDPI(12.2));
				LineTo(hdc,DDPI(16),DDPI(9.5));
				
				//Rectangle(hdc,0,0,ps.rcPaint.right,ps.rcPaint.bottom);
				
				
				HFONT hFont = CreateFont(DDPI(18), DDPI(9.2), 0, 0, 900, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, TEXT("YouYuan"));
				//SetTextCharacterExtra(hdc,DDPI(0.5));
				HGDIOBJ hOldFont = SelectObject(hdc, hFont);
				SetTextColor(hdc, RGB(255,255,255));
				SetBkMode(hdc,TRANSPARENT);
				RECT logoTextRc;
				CopyRect(&logoTextRc,&ps.rcPaint);
				logoTextRc.left = DDPI(28);
				
				//Rectangle(hdc,logoTextRc.left,logoTextRc.top,logoTextRc.right,logoTextRc.bottom);
				DrawText(hdc,appName,-1,&logoTextRc,DT_CENTER|DT_VCENTER|DT_SINGLELINE);
				
				SelectObject(hdc,hOldFont);
				DeleteObject(hFont);
				SelectObject(hdc,holdpen);
				DeleteObject(hpen_red);
				DeleteObject(hpen);
				ReleaseDC(hwnd, hdc);
				EndPaint(hwnd, &ps);
	            break;
			}
		default:
			return DefWindowProc(hwnd, Message, wParam, lParam);
	}
	return 0;
}

//myfoot事件
LRESULT CALLBACK myfootProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam) {
	switch(Message) {
		case WM_PAINT:
			{
				PAINTSTRUCT ps;
				HDC hdc = BeginPaint(hwnd, &ps);
				HPEN hpen = CreatePen(PS_SOLID, 1, RGB(224,224,224));
			    HPEN holdpen=(HPEN)SelectObject(hdc, hpen);
			    MoveToEx(hdc, 0, 0, NULL);
			    LineTo(hdc, ps.rcPaint.right, 0);
			    SelectObject(hdc,holdpen);
			    DeleteObject(hpen);
			    ReleaseDC(hwnd, hdc);
			    EndPaint(hwnd, &ps);
			}
			break;
		case WM_NCHITTEST:
			{
			    return SendMessage(GetParent(hwnd),Message,wParam,lParam);
			}
			break;
		case WM_DESTROY: {
			PostQuitMessage(0);
			break;
		}
		default:
			return DefWindowProc(hwnd, Message, wParam, lParam);
	}
	return 0;
}

//左边菜单事件
LRESULT CALLBACK L_menuProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam) {
	switch(Message) {
		case WM_PAINT:
			{
				PAINTSTRUCT ps;
				HDC hdc = BeginPaint(hwnd, &ps);
				HPEN hpen = CreatePen(PS_SOLID, 1, RGB(224,224,224));
			    HPEN holdpen=(HPEN)SelectObject(hdc, hpen);
			    //Rectangle(hdc,0,0,ps.rcPaint.right,ps.rcPaint.bottom);
			    MoveToEx(hdc, ps.rcPaint.right-1, 0, NULL);
			    LineTo(hdc, ps.rcPaint.right-1, ps.rcPaint.bottom);
			    SelectObject(hdc,holdpen);
			    DeleteObject(hpen);
			    ReleaseDC(hwnd, hdc);
			    EndPaint(hwnd, &ps);
			}
			break;
		case WM_DESTROY: {
			PostQuitMessage(0);
			break;
		}
		default:
			return DefWindowProc(hwnd, Message, wParam, lParam);
	}
	return 0;
}
//主功能菜单
LRESULT CALLBACK L_MainIndexProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam) {
	switch(Message) {
		case WM_PAINT:
			{
				PAINTSTRUCT ps;
				HDC hdc = BeginPaint(hwnd, &ps);
				HPEN hpen = CreatePen(PS_SOLID, 1, RGB(224,224,224));
			    HPEN holdpen=(HPEN)SelectObject(hdc, hpen);
			    //Rectangle(hdc,0,0,ps.rcPaint.right,ps.rcPaint.bottom);
			    SelectObject(hdc,holdpen);
				DeleteObject(hpen);
			    ReleaseDC(hwnd, hdc);
			    EndPaint(hwnd, &ps);
			}
			break;
		case WM_DESTROY: {
			PostQuitMessage(0);
			break;
		}
		default:
			return DefWindowProc(hwnd, Message, wParam, lParam);
	}
	return 0;
}
//我的音乐功能菜单
LRESULT CALLBACK MyMusicIndexProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam) {
	switch(Message) {
		case WM_PAINT:
			{
				PAINTSTRUCT ps;
				HDC hdc = BeginPaint(hwnd, &ps);
				HPEN hpen = CreatePen(PS_SOLID, 1, RGB(224,224,224));
			    HPEN holdpen = (HPEN)SelectObject(hdc, hpen);
			    //Rectangle(hdc,0,0,ps.rcPaint.right,ps.rcPaint.bottom);
			    SelectObject(hdc,holdpen);
				DeleteObject(hpen);
			    ReleaseDC(hwnd, hdc);
			    EndPaint(hwnd, &ps);
			}
			break;
		case WM_DESTROY: {
			PostQuitMessage(0);
			break;
		}
		default:
			return DefWindowProc(hwnd, Message, wParam, lParam);
	}
	return 0;
}

mouseState MainIndex_btn;

//主功能菜单按钮
LRESULT CALLBACK L_MainIndex_btnProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam) {
	switch(Message) {
		case WM_MOUSEMOVE:
			{
				int ctrlId = GetDlgCtrlID(hwnd);
				if(!MainIndexList[ctrlId].mouseHover){
					MainIndexList[ctrlId].mouseHover = 1;
					InvalidateRect(MainIndexList[ctrlId].hwnd, NULL, TRUE);
				}
				TRACKMOUSEEVENT temp;
				temp.cbSize = sizeof(TRACKMOUSEEVENT);
				temp.dwFlags = TME_LEAVE;
				temp.hwndTrack = hwnd;
				temp.dwHoverTime = 10;
				int tme = TrackMouseEvent(&temp);
				break;
			}
		case WM_MOUSEHOVER:
			{
				//printf("进入\n");
				//int ctrlId = GetDlgCtrlID(hwnd);
				
				break;
			}
		case WM_MOUSELEAVE:
			{
				//printf("离开\n");
				int ctrlId = GetDlgCtrlID(hwnd);
				MainIndexList[ctrlId].mouseHover = 0;
				InvalidateRect(MainIndexList[ctrlId].hwnd, NULL, TRUE);
				break;
			}
		case WM_SETCURSOR:
			{
				HCURSOR cur = LoadCursorA(NULL,IDC_HAND);
				SetCursor(cur);
				break;
			}
		case WM_LBUTTONDOWN:
			{
				for(int i=1;i<=MainIndexList.size();i++){
					if(MainIndexList[i].checked==1){
						MainIndexList[i].checked=0;
						InvalidateRect(MainIndexList[i].hwnd, NULL, TRUE);
					}
				}
				for(int i=1;i<=MyMusicItemList.size();i++){
					if(MyMusicItemList[i].checked==1){
						MyMusicItemList[i].checked=0;
						InvalidateRect(MyMusicItemList[i].hwnd, NULL, TRUE);
					}
				}
				int ctrlId = GetDlgCtrlID(hwnd);
				MainIndexList[ctrlId].checked = 1;
				InvalidateRect(hwnd, NULL, TRUE);
				break;
			}
		case WM_PAINT:
			{
				int ctrlId = GetDlgCtrlID(hwnd);
				PAINTSTRUCT ps;
				HDC hdc = BeginPaint(hwnd, &ps);
				HPEN hpen = CreatePen(PS_SOLID, 1, RGB(246,246,247));
			    HPEN holdpen = (HPEN)SelectObject(hdc, hpen);
			    if(MainIndexList[ctrlId].checked||MainIndexList[ctrlId].mouseHover){
					HBRUSH hBrush = CreateSolidBrush(RGB(246,246,247));
				    HBRUSH oldhBrush = (HBRUSH)SelectObject(hdc, hBrush);
				    RoundRect(hdc,ps.rcPaint.left,ps.rcPaint.top,ps.rcPaint.right,ps.rcPaint.bottom,DPI(7),DPI(7));
				    SelectObject(hdc, oldhBrush);
				    DeleteObject(hBrush);
				};
			    int Fwidth;
			    int Fsize;
			    if(MainIndexList[ctrlId].checked){
					Fwidth = 800;
					Fsize = DDPI(24);
				}else{
					Fwidth = 500;
					Fsize = DDPI(20);
				}
				HFONT hFont = CreateFont(Fsize, 0, 0, 0, Fwidth, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, TEXT("Microsoft YaHei"));
				HFONT oldhFont =(HFONT)SelectObject(hdc, hFont);
			    SetTextColor(hdc, RGB(57,57,57));
				SetBkMode(hdc,TRANSPARENT);
				RECT TextRc;
				CopyRect(&TextRc,&ps.rcPaint);
				TextRc.left = DDPI(8);
				DrawText(hdc,MainIndexList[ctrlId].text.c_str(),-1,&TextRc,DT_VCENTER|DT_SINGLELINE);
			    //printf("%d\n",ctrlId);
				SelectObject(hdc,holdpen);
				DeleteObject(hpen);
				SelectObject(hdc,oldhFont);
				DeleteObject(hFont);
				
				ReleaseDC(hwnd, hdc);
			    EndPaint(hwnd, &ps);
			}
			break;
		case WM_DESTROY: {
			PostQuitMessage(0);
			break;
		}
		default:
			return DefWindowProc(hwnd, Message, wParam, lParam);
	}
	return 0;
}

//我的音乐菜单按钮
LRESULT CALLBACK L_Mymusic_btnProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam) {
	switch(Message) {
		case WM_MOUSEMOVE:
			{
				int ctrlId = GetDlgCtrlID(hwnd);
				if(!MyMusicItemList[ctrlId].mouseHover){
					MyMusicItemList[ctrlId].mouseHover = 1;
					InvalidateRect(MyMusicItemList[ctrlId].hwnd, NULL, TRUE);
				}
				TRACKMOUSEEVENT temp;
				temp.cbSize = sizeof(TRACKMOUSEEVENT);
				temp.dwFlags = TME_LEAVE;
				temp.hwndTrack = hwnd;
				temp.dwHoverTime = 10;
				int tme = TrackMouseEvent(&temp);
				break;
			}
		case WM_MOUSEHOVER:
			{
				//int ctrlId = GetDlgCtrlID(hwnd);
				
				break;
			}
		case WM_MOUSELEAVE:
			{

				int ctrlId = GetDlgCtrlID(hwnd);
				MyMusicItemList[ctrlId].mouseHover = 0;
				InvalidateRect(MyMusicItemList[ctrlId].hwnd, NULL, TRUE);
				break;
			}
		case WM_SETCURSOR:
			{
				HCURSOR cur = LoadCursorA(NULL,IDC_HAND);
				SetCursor(cur);
				break;
			}
		case WM_LBUTTONDOWN:
			{
				for(int i=1;i<=MyMusicItemList.size();i++){
					if(MyMusicItemList[i].checked==1){
						MyMusicItemList[i].checked=0;
						InvalidateRect(MyMusicItemList[i].hwnd, NULL, TRUE);
					}
				}
				for(int i=1;i<=MainIndexList.size();i++){
					if(MainIndexList[i].checked==1){
						MainIndexList[i].checked=0;
						InvalidateRect(MainIndexList[i].hwnd, NULL, TRUE);
					}
				}
				int ctrlId = GetDlgCtrlID(hwnd);
				MyMusicItemList[ctrlId].checked = 1;
				InvalidateRect(hwnd, NULL, TRUE);
				break;
			}
		case WM_LBUTTONUP:
			{
				//printf("抬起\n");
				break;
			}
		case WM_PAINT:
			{
				int ctrlId = GetDlgCtrlID(hwnd);
				PAINTSTRUCT ps;
				HDC hdc = BeginPaint(hwnd, &ps);
				HPEN hpen = CreatePen(PS_SOLID, 1, RGB(246,246,247));
			    HPEN holdpen = (HPEN) SelectObject(hdc, hpen);
			    if(MyMusicItemList[ctrlId].checked||MyMusicItemList[ctrlId].mouseHover){
					HBRUSH hBrush = CreateSolidBrush(RGB(246,246,247));
				    HBRUSH oldhBrush = (HBRUSH)SelectObject(hdc, hBrush);
				    RoundRect(hdc,ps.rcPaint.left,ps.rcPaint.top,ps.rcPaint.right,ps.rcPaint.bottom,DPI(7),DPI(7));
				    SelectObject(hdc, oldhBrush);
				    DeleteObject(hBrush);
				};
				HFONT hFont = CreateFont(DDPI(19), 0, 0, 0, 400, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, TEXT("Microsoft YaHei"));
				HFONT holdFont = (HFONT) SelectObject(hdc, hFont);
			    SetTextColor(hdc, RGB(57,57,57));
				SetBkMode(hdc,TRANSPARENT);
				RECT TextRc;
				CopyRect(&TextRc,&ps.rcPaint);
				TextRc.left = DDPI(30);
				DrawText(hdc,MyMusicItemList[ctrlId].text.c_str(),-1,&TextRc,DT_VCENTER|DT_SINGLELINE);
				
				//如果有图标就绘画图标
				if(MyMusicItemList[ctrlId].emf){
					//cout << ctrlId << "有图标" <<endl;
					RECT iconRc;
					CopyRect(&iconRc,&ps.rcPaint);
					iconRc.left+=DPI(8);
					iconRc.top+=DPI(11);
					iconRc.bottom-=DPI(11);
					iconRc.right = DPI(23);
					//HENHMETAFILE emf = GetEnhMetaFileA(".\\res\\emf\\heart.emf");
					
					
					PlayEnhMetaFile(hdc,MyMusicItemList[ctrlId].emf,&iconRc);	
				}
				SelectObject(hdc,holdFont);
				DeleteObject(hFont);
				SelectObject(hdc,holdpen);
				DeleteObject(hpen);
				ReleaseDC(hwnd, hdc);
			    EndPaint(hwnd, &ps);
			    
			    
			}
			break;
		case WM_DESTROY: {
			PostQuitMessage(0);
			break;
		}
		default:
			return DefWindowProc(hwnd, Message, wParam, lParam);
	}
	return 0;
}



//功能菜单小标题
LRESULT CALLBACK IndexTitleProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam) {
	switch(Message) {
		case WM_PAINT:
			{
				HFONT hFont = CreateFont(DPI(17), 0, 0, 0, 500, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, TEXT("Microsoft YaHei"));
				PAINTSTRUCT ps;
				HDC hdc = BeginPaint(hwnd, &ps);
				HPEN hpen = CreatePen(PS_SOLID, 1, RGB(224,224,224));
			    HPEN holdpen = (HPEN)SelectObject(hdc, hpen);
			    //Rectangle(hdc,0,0,ps.rcPaint.right,ps.rcPaint.bottom);
			    
			    HFONT holdFont = (HFONT)SelectObject(hdc, hFont);
			    SetTextColor(hdc, RGB(153,153,153));
				SetBkMode(hdc,TRANSPARENT);
				RECT TextRc;
				CopyRect(&TextRc,&ps.rcPaint);
				TextRc.left = DDPI(8);
				DrawText(hdc,"我的音乐",-1,&TextRc,DT_VCENTER|DT_SINGLELINE);
			    SelectObject(hdc,holdpen);
			    DeleteObject(hpen);
			    SelectObject(hdc,holdFont);
			    DeleteObject(hFont);
			    ReleaseDC(hwnd, hdc);
			    EndPaint(hwnd, &ps);
			}
			break;
		case WM_DESTROY: {
			PostQuitMessage(0);
			break;
		}
		default:
			return DefWindowProc(hwnd, Message, wParam, lParam);
	}
	return 0;
}

//底部左侧播放中的歌曲信息
LRESULT CALLBACK footLProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam) {
	switch(Message) {
		case WM_PAINT:
			{
				PAINTSTRUCT ps;
				HDC hdc = BeginPaint(hwnd, &ps);
				HPEN hpen = CreatePen(PS_SOLID, 1, RGB(255,255,255));
				HPEN holdpen = (HPEN)SelectObject(hdc, hpen);
			    if(player.name.length()){
					SetTextColor(hdc,RGB(51,51,51));
				    //重绘背景
				    HBRUSH hBrush = CreateSolidBrush(RGB(255,255,255));
				    HBRUSH oldhBrush = (HBRUSH)SelectObject(hdc, hBrush);
				    Rectangle(hdc,0,0,ps.rcPaint.right,ps.rcPaint.bottom);
				    hpen = CreatePen(PS_SOLID, 1, RGB(0,0,0));
				    DeleteObject(holdpen);
				    holdpen = (HPEN)SelectObject(hdc, hpen);
				    
				    //图片位置
				    //gdi只支持显示bitmap图片，而网易云返回jpeg格式，此处需要将jpeg转为bitmap，没研究出来，所以没搞
				    RoundRect(hdc,0,0,DPI(43),DPI(43),DPI(7),DPI(7));
				    RECT TextRc;
				    TextRc.left = 0;
				    TextRc.top = 0;
				    TextRc.right = DPI(43);
				    TextRc.bottom = DPI(43);
				    DrawText(hdc,"图片",-1,&TextRc,DT_CENTER|DT_VCENTER|DT_SINGLELINE);
				    
				    //歌曲名
				    HFONT hFont = CreateFont(DPI(19), 0, 0, 0, 500, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, TEXT("Microsoft YaHei"));
				    HFONT holdFont = (HFONT)SelectObject(hdc, hFont);
				    RECT SongNameRc;
				    SongNameRc.left = DPI(49);
				    SongNameRc.top = DPI(3);
				    SongNameRc.bottom = DPI(21);
				    SongNameRc.right = ps.rcPaint.right-SongNameRc.left;
				    DrawText(hdc,player.name.c_str(),-1,&SongNameRc,DT_VCENTER|DT_SINGLELINE);
				    
				    //歌手名
				    SelectObject(hdc,holdFont);
				    DeleteObject(hFont);
				    hFont = CreateFont(DPI(16), 0, 0, 0, 500, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, TEXT("Microsoft YaHei"));
				    holdFont = (HFONT)SelectObject(hdc, hFont);
				    
				    
				    RECT ArtistNameRc;
				    ArtistNameRc.left = DPI(49);
				    ArtistNameRc.top = DPI(23);
				    ArtistNameRc.bottom = DPI(38);
				    ArtistNameRc.right = ps.rcPaint.right-ArtistNameRc.left;
					DrawText(hdc,player.artist.c_str(),-1,&ArtistNameRc,DT_VCENTER|DT_SINGLELINE);
				    SelectObject(hdc,holdFont);
				    DeleteObject(hFont);
				    SelectObject(hdc, oldhBrush);
				    DeleteObject(hBrush);
				}
			    DeleteObject(hpen);
			    ReleaseDC(hwnd, hdc);
			    EndPaint(hwnd, &ps);
			}
			break;
		case WM_DESTROY: {
			PostQuitMessage(0);
			break;
		}
		default:
			return DefWindowProc(hwnd, Message, wParam, lParam);
	}
	return 0;
}


//底部控制按钮组
LRESULT CALLBACK PlayingControlProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam) {
	switch(Message) {
		case WM_PAINT:
			{
				PAINTSTRUCT ps;
				HDC hdc = BeginPaint(hwnd, &ps);
			    HPEN hpen = CreatePen(PS_NULL, 0, 0);
				HPEN holdpen = (HPEN)SelectObject(hdc, hpen);
				//重绘背景
				Rectangle(hdc,0,0,ps.rcPaint.right,ps.rcPaint.bottom);
			    //歌曲进度条
			    if(player.totalTime_str.length()){
				    HFONT hFont = CreateFont(DPI(15), 0, 0, 0, 500, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, TEXT("Microsoft YaHei"));
				    
					HFONT holdFont = (HFONT)SelectObject(hdc, hFont);
				    SetTextColor(hdc,RGB(177,177,177));
				    RECT TimeTextRc;
				    TimeTextRc.left = 0;
				    TimeTextRc.top = DPI(67-10*2 - 14);
				    TimeTextRc.bottom = DPI(67-10*2 - 4);
				    TimeTextRc.right = DPI(27);
				    //当前位置
				    DrawText(hdc,player.position_str.c_str(),-1,&TimeTextRc,DT_VCENTER|DT_SINGLELINE);
				    //总时间
					TimeTextRc.left = ps.rcPaint.right - DPI(27);
				    TimeTextRc.right = ps.rcPaint.right;
				    DrawText(hdc,player.totalTime_str.c_str(),-1,&TimeTextRc,DT_VCENTER|DT_SINGLELINE);
				    
					//进度条
					int progressWidth = ps.rcPaint.right - DPI(27+5)*2;
					int progressNow = progressWidth*player.position/(player.totalTime*1.0);
					//cout<<progressNow<<","<<progressWidth<<endl;
					//cout<<(player.position)<<","<<player.totalTime<<","<<(player.position/(player.totalTime*1.0))<<endl;
					if(ProgressMouseState.progress){
						HBRUSH hBrush = CreateSolidBrush(RGB(206,206,206));
						HBRUSH oldhBrush = (HBRUSH)SelectObject(hdc, hBrush);
						RoundRect(hdc,DPI(27+5),DDPI(67-10*2 - 11.6),progressWidth+DPI(27+5),DDPI(67-10*2 - 5.3),DPI(3),DPI(3));
						hBrush = CreateSolidBrush(RGB(255,52,52));
						SelectObject(hdc, hBrush);
						RoundRect(hdc,DPI(27+5),DDPI(67-10*2 - 11.6),progressNow+DPI(27+5),DDPI(67-10*2 - 5.3),DPI(3),DPI(3));
						hBrush = CreateSolidBrush(RGB(236,65,65));
						SelectObject(hdc, hBrush);
						Ellipse (hdc, progressNow+DDPI(27+2), DDPI(67-10*2 - 14), progressNow+DDPI(27+5 +7), DDPI(67-10*2 - 12+8.5));
						SelectObject(hdc, oldhBrush);
						DeleteObject(hBrush);
					}else{
						HBRUSH hBrush = CreateSolidBrush(RGB(206,206,206));
						HBRUSH oldhBrush = (HBRUSH)SelectObject(hdc, hBrush);
						RoundRect(hdc,DPI(27+5),DPI(67-10*2 - 11),progressWidth+DPI(27+5),DPI(67-10*2 - 7),DPI(3),DPI(3));
						
						hBrush = CreateSolidBrush(RGB(255,52,52));
						SelectObject(hdc, hBrush);
						RoundRect(hdc,DPI(27+5),DPI(67-10*2 - 11),progressNow+DPI(27+5),DPI(67-10*2 - 7),DPI(3),DPI(3));
						SelectObject(hdc, oldhBrush);
						DeleteObject(hBrush);
					}
					SelectObject(hdc,holdFont);
				    DeleteObject(hFont);
				}
				HBRUSH hBrush = CreateSolidBrush(RGB(255,255,255));
			    HBRUSH oldhBrush = (HBRUSH)SelectObject(hdc, hBrush);
			    //操控按钮
			    DeleteObject(holdpen);
			    hpen = CreatePen(PS_SOLID, 1, RGB(0,0,0));
				holdpen = (HPEN)SelectObject(hdc, hpen);
				
			    int btn_width = DPI(67-10*2 - 17);
			    int margin = DPI(23);
			    int padding = (DPI(420)-5*btn_width-4*margin)/2;
				//Rectangle(hdc,padding,0,padding+btn_width,btn_width);
				for(int i=0;i<5;i++){
					int thisLeft = padding+(margin+btn_width)*i;
					int thisRight = padding+btn_width+(margin+btn_width)*i;
					//用这个比较好定位
					//Rectangle(hdc,thisLeft,0,thisRight,btn_width);
					switch (i) {
						case 0:{
								//播放次序图标
								if(ProgressMouseState.btn_group[i]){
									hpen = CreatePen(PS_SOLID, DPIW(1), RGB(240,103,103));
								}else{
									hpen = CreatePen(PS_SOLID, DPIW(1), RGB(51,51,51));
								}
								HPEN oldhpen = (HPEN)SelectObject(hdc, hpen);
								DeleteObject(oldhpen);
								MoveToEx(hdc, thisLeft+DPI(8), DPI(10), NULL);
								LineTo(hdc, thisLeft+DPI(20), DPI(10));
								MoveToEx(hdc, thisLeft+DPI(8), DPI(15), NULL);
								LineTo(hdc, thisLeft+DPI(20), DPI(15));
								MoveToEx(hdc, thisLeft+DPI(8), DPI(20), NULL);
								LineTo(hdc, thisLeft+DPI(20), DPI(20));
								//箭头
								LineTo(hdc, thisLeft+DPI(18), DPI(18));
								MoveToEx(hdc, thisLeft+DPI(20), DPI(20), NULL);
								LineTo(hdc, thisLeft+DPI(18), DPI(22));
								break;
							}	
						case 1:{
								//上一曲
								if(ProgressMouseState.btn_group[i]){
									hpen = CreatePen(PS_SOLID, DPIW(1), RGB(240,103,103));
									hBrush = CreateSolidBrush(RGB(240,103,103));
								}else{
									hpen = CreatePen(PS_SOLID, DPIW(1), RGB(51,51,51));
									hBrush = CreateSolidBrush(RGB(51,51,51));
								}
								DeleteObject((HPEN)SelectObject(hdc, hpen));
								DeleteObject((HBRUSH)SelectObject(hdc, hBrush));
								MoveToEx(hdc, thisLeft+DPI(10), DPI(9), NULL);
								LineTo(hdc, thisLeft+DPI(10), DPI(20));
								//三角形
								POINT vertex[3];
								vertex[0].x = thisLeft+DPI(10);
								vertex[0].y = DPI(15);
								vertex[1].x = thisLeft+DPI(19);
								vertex[1].y = DPI(9);
								vertex[2].x = thisLeft+DPI(19);
								vertex[2].y = DPI(21);
								SetPolyFillMode(hdc,WINDING);
								Polygon(hdc,vertex,3);
								break;
							}
						case 2:{
							//播放与暂停
							//背景
							if(ProgressMouseState.btn_group[i]){
								hBrush = CreateSolidBrush(RGB(229,229,229));
								hpen = CreatePen(PS_SOLID, DPIW(1), RGB(229,229,229));
							}else{
								hBrush = CreateSolidBrush(RGB(245,245,245));
								hpen = CreatePen(PS_SOLID, DPIW(1), RGB(245,245,245));
							}
							DeleteObject((HPEN)SelectObject(hdc, hpen));
							DeleteObject((HBRUSH)SelectObject(hdc, hBrush));
							Ellipse (hdc, thisLeft, 0, thisRight, btn_width);
							
							//图标
							hBrush = CreateSolidBrush(RGB(46,46,46));
							hpen = CreatePen(PS_SOLID, DPIW(1), RGB(46,46,46));
							DeleteObject((HPEN)SelectObject(hdc, hpen));
							DeleteObject((HBRUSH)SelectObject(hdc, hBrush));
							if(player.playing){
								//暂停图标
								Rectangle(hdc,thisLeft+DPI(10),DPI(9),thisLeft+DDPI(13.7),DPI(21));
								Rectangle(hdc,thisLeft+DDPI(17.777777),DPI(9),thisLeft+DDPI(20.9999),DPI(21));
							}else{
								//播放图标
								POINT vertex[3];
								vertex[0].x = thisLeft+DPI(21);
								vertex[0].y = DPI(15);
								vertex[1].x = thisLeft+DPI(11);
								vertex[1].y = DPI(9);
								vertex[2].x = thisLeft+DPI(11);
								vertex[2].y = DPI(21);
								SetPolyFillMode(hdc,WINDING);
								Polygon(hdc,vertex,3);
								
							}
							
							break;
						}
						case 3:{
								//下一曲
								if(ProgressMouseState.btn_group[i]){
									hpen = CreatePen(PS_SOLID, DPIW(1), RGB(240,103,103));
									hBrush = CreateSolidBrush(RGB(240,103,103));
								}else{
									hpen = CreatePen(PS_SOLID, DPIW(1), RGB(51,51,51));
									hBrush = CreateSolidBrush(RGB(51,51,51));
								}
								DeleteObject((HPEN)SelectObject(hdc, hpen));
								DeleteObject((HBRUSH)SelectObject(hdc, hBrush));
								MoveToEx(hdc, thisLeft+DPI(19), DPI(9), NULL);
								LineTo(hdc, thisLeft+DPI(19), DPI(21));
								//三角形
								POINT vertex[3];
								vertex[0].x = thisLeft+DPI(19);
								vertex[0].y = DPI(15);
								vertex[1].x = thisLeft+DPI(9);
								vertex[1].y = DPI(9);
								vertex[2].x = thisLeft+DPI(9);
								vertex[2].y = DPI(21);
								SetPolyFillMode(hdc,WINDING);
								Polygon(hdc,vertex,3);
								break;
							}
						case 4:{
							//词开关
							if(ProgressMouseState.btn_group[i]){
								SetTextColor(hdc,RGB(240,103,103));
							}else{
								SetTextColor(hdc,RGB(51,51,51));
							}
							HFONT hFont = CreateFont(DDPI(18.5), 0, 0, 0, 600, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, TEXT("Microsoft YaHei"));
							DeleteObject((HFONT)SelectObject(hdc, hFont));
							RECT lyricTextRc;
						    lyricTextRc.left = thisLeft;
						    lyricTextRc.top = 0;
						    lyricTextRc.bottom = btn_width;
						    lyricTextRc.right = thisRight;
						    //当前位置
						    DrawText(hdc,"词",-1,&lyricTextRc,DT_CENTER|DT_VCENTER|DT_SINGLELINE);
							break;
							}
						default:
							//TODO
							break;
					}
				}
			    ReleaseDC(hwnd, hdc);
			    EndPaint(hwnd, &ps);
			}
			break;
		case WM_MOUSEMOVE: {
			int xPos = GET_X_LPARAM(lParam); 
			int yPos = GET_Y_LPARAM(lParam); 
			//cout<<xPos<<","<<yPos<<endl;
			//添加一些鼠标触控间隙
			int gap = 2;
			//进度条位置
			if(xPos>DPI(27+5-gap)&&yPos>DPI(67-10*2 - 11-gap)&&xPos<DPI(420-27-5+gap)&&yPos<DPI(67-10*2 - 7+gap)){
				//进度条显示时长的tootip
				int Pmousex =  xPos-DPI(27+5);
				if(Pmousex<0){
					Pmousex=0;
				}
				int progressWidth = DPI(420) - DPI(27+5)*2;
				if(Pmousex>progressWidth){
					Pmousex=progressWidth;
				}
				long newPosition = Pmousex/(progressWidth*1.0)*player.totalTime;
				
				//计算当前播放的长度
				int mm = 0;
				int ss;
				newPosition = newPosition/1000;
				while(newPosition>59){
					newPosition-=60;
					mm++;
				}
				ss=newPosition;
				wstring tooltipcontext = (mm<10?L"0":L"") + to_wstring(mm)+L":" + (ss<10?L"0":L"") + to_wstring(ss);
				POINT pt;
				GetCursorPos(&pt);
				tooltip_show(tooltipcontext,pt.x,pt.y);
				
				if(!ProgressMouseState.progress){
					ProgressMouseState.progress=1;
					InvalidateRect(hwnd, NULL, TRUE);
					return 0;
				}
			}else{
				if(ProgressMouseState.progress){
					ProgressMouseState.progress=0;
					InvalidateRect(hwnd, NULL, TRUE);
					
					if(IsWindowVisible(HWNDM[H_tooltip])){
						tooltip_hide();
					}
					return 0;
				};
			}
			//操作按钮位置
			int btn_width = DPI(67-10*2 - 17);
		    int margin = DPI(23);
		    int padding = (DPI(420)-5*btn_width-4*margin)/2;
		    //按钮图标比边框小6
		    int padding_gap = DPI(6);
			for(int i=0;i<5;i++){
				//第三个图标大一些
				if(i==2){
					padding_gap=0;
				}else{
					padding_gap = DPI(6);
				}
				int thisLeft = padding+(margin+btn_width)*i;
				int thisRight = padding+btn_width+(margin+btn_width)*i;
				if(xPos>thisLeft+padding_gap&&yPos>padding_gap&&xPos<thisRight-padding_gap&&yPos<btn_width-padding_gap){
					if(!ProgressMouseState.btn_group[i]){
						ProgressMouseState.btn_group[i]=1;
						InvalidateRect(hwnd, NULL, TRUE);
						SendMessageA(hwnd, WM_SETCURSOR,1,0);
						if(!IsWindowVisible(HWNDM[H_tooltip])){
							ProgressMouseState.btn_groupTimerIndex=i;
							SetTimer(hwnd,777,500,NULL);
						}
						//cout<<i<<":"<<ProgressMouseState.btn_group[i]<<endl;
						return 0;
					}
				}else{
					if(ProgressMouseState.btn_group[i]){
						ProgressMouseState.btn_group[i]=0;
						InvalidateRect(hwnd, NULL, TRUE);
						SendMessageA(hwnd, WM_SETCURSOR,2,0);
						if(IsWindowVisible(HWNDM[H_tooltip])){
							tooltip_hide();
						}
						//cout<<i<<":"<<ProgressMouseState.btn_group[i]<<endl;
						return 0;
					}
				}
			}
			break;
		}
		case WM_LBUTTONDOWN: {
			//隐藏tooltip
			if(IsWindowVisible(HWNDM[H_tooltip])){
				tooltip_hide();
			}
			//进度条
			if(ProgressMouseState.progress){
				int xPos = GET_X_LPARAM(lParam);
				int Pmousex =  xPos-DPI(27+5);
				if(Pmousex<0){
					Pmousex=0;
				}
				int progressWidth = DPI(420) - DPI(27+5)*2;
				if(Pmousex>progressWidth){
					Pmousex=progressWidth;
				}
				long newPosition = Pmousex/(progressWidth*1.0)*player.totalTime;
				player.PlayFromPosition(newPosition);
				player.getPosition_str();
				InvalidateRect(HWNDM[H_PlayingControl], NULL, TRUE);
				return 0;
			}
			//按钮组
			for(int i = 0;i<5;i++){
				if(ProgressMouseState.btn_group[i]){
					switch (i) {
						case 2:{
								//播放和暂停
								if(player.playing){
									player.Pause();
								}else{
									player.Play();
								}
								InvalidateRect(HWNDM[H_PlayingControl], NULL, TRUE);
							}
							break;
						default:
							//TODO
							break;
					}
				}
			}
			break;
		}
		case WM_SETCURSOR:{
						if(wParam==1){
							HCURSOR cur = LoadCursorA(NULL,IDC_HAND);
							SetCursor(cur);
							return 0;
						}
						if(wParam==2){
							HCURSOR cur = LoadCursorA(NULL,IDC_ARROW);
							SetCursor(cur);
							return 0;
						}
						break;
					}
		case WM_DESTROY: {
			PostQuitMessage(0);
			break;
		}
		case WM_TIMER: {
			switch (wParam) {
				case 163:
					player.ProgressLoop();
					break;
				case 777:
					//tooltip
					if(ProgressMouseState.btn_groupTimerIndex<0){
						KillTimer(hwnd,777);
						return 0;
					}
					if(ProgressMouseState.btn_group[ProgressMouseState.btn_groupTimerIndex]){
						POINT pt;
						GetCursorPos(&pt);
						wstring context;
						switch (ProgressMouseState.btn_groupTimerIndex) {
							case 0:
								context = L"顺序播放";
								break;
							case 1:
								context = L"上一曲";
								break;
							case 2:{
									if(player.playing){
										context = L"暂停";
									}else{
										context = L"播放";
									}
									break;
								}
							case 3:
								context = L"下一曲";
								break;
							case 4:
								context = L"打开歌词";
								break;
							default:
								context = L"出Bug了";
								break;
						}
						tooltip_show(context.c_str(),pt.x,pt.y);
						KillTimer(hwnd,777);
					}
					KillTimer(hwnd,777);
					break;
				default:
					//TODO
					break;
			}
			break;
		}
		default:
			return DefWindowProc(hwnd, Message, wParam, lParam);
	}
	return 0;
}


//底部右侧的播放设置
LRESULT CALLBACK PlayingSetProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam) {
	switch(Message) {
		case WM_PAINT:
			{
				PAINTSTRUCT ps;
				HDC hdc = BeginPaint(hwnd, &ps);
				//HPEN hpen = CreatePen(PS_SOLID, 1, RGB(0,0,0));
				HPEN hpen = CreatePen(PS_NULL, 0, 0);
			    DeleteObject((HPEN)SelectObject(hdc, hpen));
			    HBRUSH hBrush = CreateSolidBrush(RGB(255,255,255));
				DeleteObject((HBRUSH)SelectObject(hdc, hBrush));
			    Rectangle(hdc,0,0,ps.rcPaint.right,ps.rcPaint.bottom);
			    
			    
			    int btn_width = DPI(39);
			    int margin = DPI(8);
			    int padding = (DPI(420)-5*btn_width-4*margin)/2;
			    int Bar_width = DPI(250);
			    for(int i = 0;i<3;i++){
					//Rectangle(hdc,Bar_width-btn_width+margin-btn_width*i,margin,Bar_width-margin-btn_width*i,btn_width-margin);
					int thisLeft = Bar_width-btn_width+margin-btn_width*i;
					int thisTop = margin;
					int thisRight = Bar_width-margin-btn_width*i;
					int thisBottom = btn_width-margin;
					switch (i) {
						case 0:{
								//播放列表
								hpen = CreatePen(PS_SOLID, DPIW(1), RGB(71,71,71));
								DeleteObject((HPEN)SelectObject(hdc, hpen));
								MoveToEx(hdc, thisLeft+DPI(3), thisTop+DPI(18), NULL);
								LineTo(hdc, thisLeft+DPI(19), thisTop+DPI(18));
								MoveToEx(hdc, thisLeft+DPI(3), thisTop+DPI(12), NULL);
								LineTo(hdc, thisLeft+DPI(19), thisTop+DPI(12));
								MoveToEx(hdc, thisLeft+DPI(10), thisTop+DPI(6), NULL);
								LineTo(hdc, thisLeft+DPI(19), thisTop+DPI(6));
								
								hBrush = CreateSolidBrush(RGB(71,71,71));
								DeleteObject((HBRUSH)SelectObject(hdc, hBrush));
								hpen = CreatePen(PS_SOLID, 1, RGB(71,71,71));
								DeleteObject((HPEN)SelectObject(hdc, hpen));
								POINT vertex[3];
								vertex[0].x = thisLeft+DDPI(3);
								vertex[0].y = thisTop+DDPI(3);
								vertex[1].x = thisLeft+DDPI(3);
								vertex[1].y = thisTop+DDPI(8);
								vertex[2].x = thisLeft+DDPI(7);
								vertex[2].y = thisTop+DDPI(6);
								SetPolyFillMode(hdc,WINDING);
								Polygon(hdc,vertex,3);
								break;
							}	
						case 1:{
								//开始一起听
								hBrush = CreateSolidBrush(RGB(255,255,255));
								DeleteObject((HBRUSH)SelectObject(hdc, hBrush));
								hpen = CreatePen(PS_SOLID, DPIW(1), RGB(71,71,71));
								DeleteObject((HPEN)SelectObject(hdc, hpen));
								MoveToEx(hdc, thisLeft+DPI(20), thisTop+DPI(5), NULL);
								LineTo(hdc, thisLeft+DPI(20), thisTop+DPI(10));
								
								Ellipse (hdc, thisLeft+DDPI(8.84), thisTop+DDPI(3.72), thisLeft+DDPI(18.53), thisTop+DDPI(12.94));
								Ellipse (hdc, thisLeft+DDPI(5.25), thisTop+DDPI(11.81), thisLeft+DDPI(21), thisTop+DDPI(29));
								
								
								hpen = CreatePen(PS_NULL, 0, 0);
								DeleteObject((HPEN)SelectObject(hdc, hpen));
								
								Rectangle(hdc,thisLeft,thisTop,thisLeft+DPI(14),thisTop+DPI(29));
								
								hpen = CreatePen(PS_SOLID, DPIW(1), RGB(51,51,51));
								DeleteObject((HPEN)SelectObject(hdc, hpen));
								Ellipse (hdc, thisLeft+DDPI(4.84), thisTop+DDPI(3.72), thisLeft+DDPI(14.53), thisTop+DDPI(12.94));
								Ellipse (hdc, thisLeft+DDPI(1.9), thisTop+DDPI(11.81), thisLeft+DDPI(17), thisTop+DDPI(29));
								MoveToEx(hdc, thisLeft+DPI(2), thisTop+DPI(5), NULL);
								LineTo(hdc, thisLeft+DPI(2), thisTop+DPI(10));
								
								hpen = CreatePen(PS_NULL, 0, 0);
								DeleteObject((HPEN)SelectObject(hdc, hpen));
								Rectangle(hdc,thisLeft,thisTop+DDPI(19.5),thisRight,thisTop+DPI(30));
								
								break;
							}
						case 2:{
								//音量
								hpen = CreatePen(PS_SOLID, DPIW(1), RGB(51,51,51));
								DeleteObject((HPEN)SelectObject(hdc, hpen));
								MoveToEx(hdc, thisLeft+DDPI(6.5), thisTop+DPI(6), NULL);
								LineTo(hdc, thisLeft+DDPI(3.5), thisTop+DPI(6));
								LineTo(hdc, thisLeft+DDPI(3.5), thisTop+DPI(16));
								LineTo(hdc, thisLeft+DDPI(6.5), thisTop+DPI(16));
								MoveToEx(hdc, thisLeft+DPI(10), thisTop+DPI(6), NULL);
								LineTo(hdc, thisLeft+DPI(17), thisTop+DDPI(2.5));
								LineTo(hdc, thisLeft+DPI(17), thisTop+DDPI(19.5));
								LineTo(hdc, thisLeft+DPI(10), thisTop+DPI(16));
								LineTo(hdc, thisLeft+DPI(10), thisTop+DPI(6));
								if(player.getVolume()==0){
									hpen = CreatePen(PS_NULL, 0, 0);
									DeleteObject((HPEN)SelectObject(hdc, hpen));
									Rectangle(hdc,thisLeft+DPI(14),thisTop+DDPI(8),thisLeft+DPI(21),thisTop+DPI(14));
									
									
									hpen = CreatePen(PS_SOLID, DPIW(1), RGB(51,51,51));
									DeleteObject((HPEN)SelectObject(hdc, hpen));
									MoveToEx(hdc, thisLeft+DPI(14), thisTop+DPI(9), NULL);
									LineTo(hdc, thisLeft+DPI(19), thisTop+DPI(13));
									MoveToEx(hdc, thisLeft+DPI(19), thisTop+DPI(9), NULL);
									LineTo(hdc, thisLeft+DPI(14), thisTop+DPI(13));
								}
								break;
							}
						default:
							//TODO
							break;
					}
					
				}
			    ReleaseDC(hwnd, hdc);
			    EndPaint(hwnd, &ps);
			    break;
			}
		case WM_MOUSEMOVE:{
			int xPos = GET_X_LPARAM(lParam); 
			int yPos = GET_Y_LPARAM(lParam); 
			//添加一些鼠标触控间隙
			int gap = DPI(2);
			
			int btn_width = DPI(39);
		    int margin = DPI(8);
		    int padding = (DPI(420)-5*btn_width-4*margin)/2;
		    int Bar_width = DPI(250);
		    for(int i = 0;i<3;i++){
		    	int thisLeft = Bar_width-btn_width+margin-btn_width*i;
				int thisTop = margin;
				int thisRight = Bar_width-margin-btn_width*i;
				int thisBottom = btn_width-margin;
				int topExtend;
				//音量按钮要搞特殊
				if(i==2){
					topExtend = DPI(10);
				}else{
					topExtend=0;
				}
				if(xPos>thisLeft+gap&&yPos>thisTop+gap-topExtend&&xPos<thisRight-gap&&yPos<thisBottom-gap){
					//长时间悬浮只执行一次
					if(!PlayingSetMouseState.btn_group[i]){
						PlayingSetMouseState.btn_groupTimerIndex = i;
						PlayingSetMouseState.btn_group[i] = 1;
						SendMessageA(hwnd, WM_SETCURSOR,1,0);
						if(!IsWindowVisible(HWNDM[H_tooltip])){
							PlayingSetMouseState.btn_groupTimerIndex=i;
							SetTimer(hwnd,777,500,NULL);
						}
						switch (i) {
							case 1:
								//TODO
								break;
							case 2:
								//声音设置面板
								VolumePanel_show();
								break;
							default:
								//TODO
								break;
						}
						//cout<<i<<":"<<PlayingSetMouseState.btn_group[i]<<endl;
					}
				}else{
					if(PlayingSetMouseState.btn_group[i]){
						PlayingSetMouseState.btn_group[i] = 0;
						PlayingSetMouseState.btn_groupTimerIndex = -1;
						SendMessageA(hwnd, WM_SETCURSOR,2,0);
						if(IsWindowVisible(HWNDM[H_tooltip])){
							tooltip_hide();
						}
						switch (i) {
							case 1:
								//TODO
								break;
							case 2:
								//声音设置面板
								VolumePanel_hide();
								InvalidateRect(hwnd, NULL, TRUE);
								break;
							default:
								//TODO
								break;
						}
						//cout<<i<<":"<<PlayingSetMouseState.btn_group[i]<<endl;
					}
				}
			}
			break;
		}
		case WM_DESTROY: {
			PostQuitMessage(0);
			break;
		}
		case WM_TIMER: {
			switch (wParam) {
				case 777:
					//tooltip
					if(PlayingSetMouseState.btn_groupTimerIndex<0){
						KillTimer(hwnd,777);
						return 0;
					}
					if(PlayingSetMouseState.btn_group[PlayingSetMouseState.btn_groupTimerIndex]){
						POINT pt;
						GetCursorPos(&pt);
						wstring context;
						switch (PlayingSetMouseState.btn_groupTimerIndex) {
							case 0:
								context = L"打开播放列表";
								break;
							case 1:
								context = L"开始一起听";
								break;
							case 2:{
								if(player.getVolume()==0){
									context = L"恢复音量";
								}else{
									context = L"静音";
								}
								break;
								}
							default:
								context = L"出Bug了";
								break;
						}
						tooltip_show(context.c_str(),pt.x,pt.y);
						KillTimer(hwnd,777);
					}
					KillTimer(hwnd,777);
					break;
				default:
					//TODO
					break;
			}
			break;
		}
		case WM_LBUTTONDOWN:{
			if(PlayingSetMouseState.btn_groupTimerIndex<0){
				return 0;
			}
			switch (PlayingSetMouseState.btn_groupTimerIndex) {
				case 0:
					//TODO
					break;
				case 1:
					//TODO
					break;
				case 2:
					//静音
					if(player.getVolume()==0){
						player.newVolume = player.theVolumeBeforeMute;
						player.setVolume(player.theVolumeBeforeMute);
					}else{
						player.theVolumeBeforeMute=player.getVolume();
						player.newVolume = 0;
						player.setVolume(0);
					}
					InvalidateRect(HWNDM[H_PlayingSet_m], NULL, TRUE);
					InvalidateRect(HWNDM[H_VolumePanel], NULL, TRUE);
					break;
				default:
					//TODO
					break;
			}
			if(IsWindowVisible(HWNDM[H_tooltip])){
				tooltip_hide();
			}
			break;
		}
		case WM_SETCURSOR:{
			if(wParam==1){
				HCURSOR cur = LoadCursorA(NULL,IDC_HAND);
				SetCursor(cur);
				return 0;
			}
			if(wParam==2){
				HCURSOR cur = LoadCursorA(NULL,IDC_ARROW);
				SetCursor(cur);
				return 0;
			}
			break;
		}
		default:
			return DefWindowProc(hwnd, Message, wParam, lParam);
	}
	return 0;
}


//控制音量面板
LRESULT CALLBACK VolumePanelProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam) {
	switch(Message) {
		case WM_PAINT:
			{
				PAINTSTRUCT ps;
				HDC hdc = BeginPaint(hwnd, &ps);
				RECT thisRect;
				GetWindowRect(hwnd, &thisRect);
				int height = thisRect.bottom - thisRect.top;
				int width = thisRect.right - thisRect.left;
				int shoadow_width = DPI(3);
				int padding = DPI(13);
				HPEN hpen = CreatePen(PS_SOLID, 1, RGB(229,229,229));
			    DeleteObject((HPEN)SelectObject(hdc, hpen));
			    
			    
			    Rectangle(hdc,0,0,ps.rcPaint.right,ps.rcPaint.bottom);
			    
			    hpen = CreatePen(PS_NULL, 0, 0);
			    DeleteObject((HPEN)SelectObject(hdc, hpen));
			    
			    HBRUSH hBrush = CreateSolidBrush(RGB(229,229,229));
				DeleteObject((HBRUSH)SelectObject(hdc, hBrush));
				RoundRect(hdc,padding,padding,ps.rcPaint.right-padding,ps.rcPaint.bottom-padding,DPI(3),DPI(3));
				int hight = ps.rcPaint.bottom-padding*2;
				//cout<<hight<<endl;
				int newHight = hight*(player.newVolume/1000.0);
				hBrush = CreateSolidBrush(RGB(236,65,65));
				DeleteObject((HBRUSH)SelectObject(hdc, hBrush));
			    RoundRect(hdc,padding,ps.rcPaint.bottom-padding-newHight,ps.rcPaint.right-padding,ps.rcPaint.bottom-padding,DPI(3),DPI(3));
			    Ellipse(hdc, padding-DPI(3), ps.rcPaint.bottom-padding-newHight-DPI(3),ps.rcPaint.right-padding+DPI(3),ps.rcPaint.bottom-padding-newHight+DPI(3+4));
			    
			    ReleaseDC(hwnd, hdc);
			    EndPaint(hwnd, &ps);
			}
			break;
		case WM_MOUSEMOVE:{
					//当鼠标从音量图标移到面板的时候，关闭音量图标的悬浮操作
					if(PlayingSetMouseState.btn_group[2]==1){
						PlayingSetMouseState.btn_group[2]=0;
						SendMessageA(hwnd, WM_SETCURSOR,2,0);
						PlayingSetMouseState.btn_groupTimerIndex = -1;
						if(IsWindowVisible(HWNDM[H_tooltip])){
							tooltip_hide();
						}
					}
					int yPos = GET_Y_LPARAM(lParam);
					RECT thisRect;
					GetWindowRect(hwnd, &thisRect);
					int height = thisRect.bottom - thisRect.top;
					int width = thisRect.right - thisRect.left;
					int gap = DPI(2);
					int shoadow_width = DPI(3);
					int padding = DPI(13);
					//cout<<xPos<<","<<yPos<<","<<width<<","<<height<<endl;
					if(yPos>padding-gap&&yPos<height-padding+gap){
						//cout<<1<<endl;
						if(wParam==MK_LBUTTON){
							int tempV = 1000*(height-yPos-padding)/((height-padding*2)*1.0);
							if(tempV>1000){
								tempV=1000;
							}
							if(tempV<=0){
								tempV = 0;
								//保存静音前的音量
								player.theVolumeBeforeMute = player.newVolume;
								InvalidateRect(HWNDM[H_PlayingSet_m], NULL, TRUE);
							}
							//cout<<player.newVolume<<","<<tempV<<endl;
							if(player.newVolume==0&&tempV>0){
								InvalidateRect(HWNDM[H_PlayingSet_m], NULL, TRUE);
							}
							player.newVolume = tempV;
							InvalidateRect(hwnd, NULL, TRUE);
							player.setVolume(tempV);
						}
					}else{
						//cout<<0<<endl;
					}
					TRACKMOUSEEVENT temp;
					temp.cbSize = sizeof(TRACKMOUSEEVENT);
					temp.dwFlags = TME_LEAVE;
					temp.hwndTrack = hwnd;
					temp.dwHoverTime = 100;
					int tme = TrackMouseEvent(&temp);
				break;
			}
		case WM_MOUSELEAVE:{
			if(!PlayingSetMouseState.btn_group[2]){
				VolumePanel_hide();
				InvalidateRect(HWNDM[H_PlayingSet_m], NULL, TRUE);
			}
			break;
			}
		case WM_LBUTTONDOWN:{
				int yPos = GET_Y_LPARAM(lParam);
				RECT thisRect;
				GetWindowRect(hwnd, &thisRect);
				int height = thisRect.bottom - thisRect.top;
				int width = thisRect.right - thisRect.left;
				int gap = DPI(2);
				int shoadow_width = DPI(3);
				int padding = DPI(13);
				if(yPos>padding-gap&&yPos<height-padding+gap){
					int tempV = 1000*(height-yPos-padding)/((height-padding*2)*1.0);
					if(tempV>1000){
						tempV=1000;
					}
					if(tempV<=0){
						tempV = 0;
						//保存静音前的音量
						player.theVolumeBeforeMute = player.newVolume;
						InvalidateRect(HWNDM[H_PlayingSet_m], NULL, TRUE);
					}
					//cout<<player.newVolume<<","<<tempV<<endl;
					if(player.newVolume==0&&tempV>0){
						InvalidateRect(HWNDM[H_PlayingSet_m], NULL, TRUE);
					}
					player.newVolume = tempV;
					//cout<<player.newVolume<<endl;
					InvalidateRect(hwnd, NULL, TRUE);
					player.setVolume(tempV);
				}else{
					//cout<<0<<endl;
				}
			break;
		}
		case WM_DESTROY: {
			PostQuitMessage(0);
			break;
		}
		default:
			return DefWindowProc(hwnd, Message, wParam, lParam);
	}
	return 0;
}

//搜索结果页
LRESULT CALLBACK SearchResultPageProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam) {
	switch(Message) {
		case WM_PAINT:
			{
				PAINTSTRUCT ps;
				HDC hdc = BeginPaint(hwnd, &ps);
				HPEN hpen = CreatePen(PS_SOLID, 1, RGB(236,65,65));
			    DeleteObject((HPEN)SelectObject(hdc, hpen));
			    //Rectangle(hdc,0,0,ps.rcPaint.right,ps.rcPaint.bottom);
			    
			    int padding = DPI(28);
			    //Rectangle(hdc,padding,padding,ps.rcPaint.right,ps.rcPaint.bottom);
			    
			    HFONT hFont = CreateFont(DPI(24), 0, 0, 0, 800, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, TEXT("Microsoft YaHei"));
				DeleteObject((HFONT)SelectObject(hdc, hFont));
				SetTextColor(hdc, RGB(57,57,57));
				RECT TextRc;
				TextRc.left = padding;
				TextRc.top = padding - DPI(8);
				TextRc.right = ps.rcPaint.right - padding;
				TextRc.bottom = padding+DPI(16);
				//Rectangle(hdc,TextRc.left,TextRc.top,TextRc.right,TextRc.bottom);
				string mytext = "搜索 "+SearchResultPage.keyword;
			    DrawText(hdc,mytext.c_str(),-1,&TextRc,DT_VCENTER|DT_SINGLELINE);
			    
			    //播放全部
			    if(SearchResultPage.PlayALL){
					DeleteObject((HBRUSH)SelectObject(hdc,CreateSolidBrush(RGB(205,50,50))));
					SetBkColor(hdc,RGB(205,50,50));
				}else{
					DeleteObject((HBRUSH)SelectObject(hdc,CreateSolidBrush(RGB(236,65,65))));
					SetBkColor(hdc,RGB(236,65,65));
				}
			    RoundRect(hdc,padding,padding+DPI(40),padding+DPI(140),padding+DPI(74),DPI(32),DPI(32));
			    TextRc.left = padding;
				TextRc.top = padding+DPI(40);
				TextRc.right = padding+DPI(140);
				TextRc.bottom = padding+DPI(74);
				hFont = CreateFont(DPI(20), 0, 0, 0, 500, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, TEXT("Microsoft YaHei"));
				DeleteObject((HFONT)SelectObject(hdc, hFont));
				SetTextColor(hdc, RGB(255,255,255));
			    DrawText(hdc,"播放全部",-1,&TextRc,DT_CENTER|DT_VCENTER|DT_SINGLELINE);
			    
			    DeleteObject((HBRUSH)SelectObject(hdc,CreateSolidBrush(RGB(255,255,255))));
			    POINT vertex[3];
				vertex[0].x = padding+DDPI(22);
				vertex[0].y = padding+DPI(40)+DDPI(10);
				vertex[1].x = padding+DDPI(22);
				vertex[1].y = padding+DPI(40)+DDPI(24);
				vertex[2].x = padding+DDPI(32);
				vertex[2].y = padding+DPI(40)+DDPI(17);
				SetPolyFillMode(hdc,WINDING);
				Polygon(hdc,vertex,3);
				
				safeSwitchColor(hdc,1,1,242,85,85);
				
				MoveToEx(hdc, padding+DPI(105), padding+DPI(40), NULL);
				LineTo(hdc, padding+DPI(105), padding+DPI(40)+DPI(34));
				
			    DeleteObject((HPEN)SelectObject(hdc, CreatePen(PS_SOLID, DPIW(1), RGB(255,255,255))));
			    MoveToEx(hdc, padding+DPI(121), padding+DPI(40)+DPI(11), NULL);
				LineTo(hdc, padding+DPI(121), padding+DPI(40)+DPI(22));
				
				MoveToEx(hdc, padding+DPI(115), padding+DPI(40)+DPI(17), NULL);
				LineTo(hdc, padding+DPI(127), padding+DPI(40)+DPI(17));
				
			    //下载全部
			    
			    if(SearchResultPage.DownloadALL){
					SelectObject(hdc,myBRUSH["white_1_hover"]);
					SetBkColor(hdc,RGB(242,242,242));
				}else{
					SelectObject(hdc,myBRUSH["white_1"]);
					SetBkColor(hdc,RGB(255,255,255));
				}
			    hpen = CreatePen(PS_SOLID, DPIW(1), RGB(217,217,217));
				DeleteObject((HPEN)SelectObject(hdc, hpen));
				int DownloadAll_x = DPI(140);
			    RoundRect(hdc,padding+DownloadAll_x+DPI(10),padding+DPI(40),padding+DPI(140)+DownloadAll_x,padding+DPI(74),DPI(32),DPI(32));
			    TextRc.left = padding+DownloadAll_x+DPI(30);
				TextRc.top = padding+DPI(40);
				TextRc.right = padding+DPI(140)+DownloadAll_x;
				TextRc.bottom = padding+DPI(74);
				SetTextColor(hdc, RGB(89,89,89));
			    DrawText(hdc,"下载全部",-1,&TextRc,DT_CENTER|DT_VCENTER|DT_SINGLELINE);
			    
			    hpen = CreatePen(PS_SOLID, DPIW(1), RGB(89,89,89));
				DeleteObject((HPEN)SelectObject(hdc, hpen));
				Ellipse (hdc, padding+DownloadAll_x+DPI(10)+DPI(16), padding+DPI(40)+DPI(7), padding+DownloadAll_x+DPI(10)+DPI(34), padding+DPI(40)+DPI(25));
				hpen = CreatePen(PS_NULL, 0, 0);
				DeleteObject((HPEN)SelectObject(hdc, hpen));
				Rectangle(hdc,padding+DownloadAll_x+DPI(10)+DPI(11),padding+DPI(40)+DPI(4),padding+DownloadAll_x+DPI(10)+DPI(40),padding+DPI(40)+DPI(12));
				hpen = CreatePen(PS_SOLID, DPIW(1), RGB(89,89,89));
				DeleteObject((HPEN)SelectObject(hdc, hpen));
				MoveToEx(hdc, padding+DownloadAll_x+DPI(11)+DPI(24), padding+DPI(40)+DPI(9), NULL);
				LineTo(hdc, padding+DownloadAll_x+DPI(11)+DPI(24), padding+DPI(40)+DPI(19));
				LineTo(hdc, padding+DownloadAll_x+DPI(11)+DPI(21), padding+DPI(40)+DPI(16));
				MoveToEx(hdc, padding+DownloadAll_x+DPI(11)+DPI(24), padding+DPI(40)+DPI(19), NULL);
				LineTo(hdc, padding+DownloadAll_x+DPI(11)+DPI(27), padding+DPI(40)+DPI(16));
			    
				
				//搜索到的项目标题
				RECT TitleTextRc;
				TitleTextRc.left = padding;
				TitleTextRc.top  = padding+DPI(90);
				TitleTextRc.right= ps.rcPaint.right-padding;
				TitleTextRc.bottom=padding+DPI(90)+DPI(34);
				DeleteObject((HPEN)SelectObject(hdc, myPEN["1_black"]));
				
				DeleteObject((HBRUSH)SelectObject(hdc, myBRUSH["white_1"]));
				//Rectangle(hdc,TitleTextRc.left,TitleTextRc.top,TitleTextRc.right,TitleTextRc.bottom);
				
				//算标题的长度
				int subWidth = ps.rcPaint.right - 2*padding - SearchItemWidth.empty -SearchItemWidth.index -SearchItemWidth.love -SearchItemWidth.downlaod -SearchItemWidth.length-SearchItemWidth.heat;
				SearchItemWidth.title = subWidth*0.5195;
				SearchItemWidth.artist = subWidth*0.2225;
				SearchItemWidth.album = subWidth*0.2579;
				int ItemWidthArr[9]={SearchItemWidth.empty,SearchItemWidth.index,SearchItemWidth.love,SearchItemWidth.downlaod,SearchItemWidth.title,SearchItemWidth.artist,SearchItemWidth.album,SearchItemWidth.length,SearchItemWidth.heat};

				int nowLeft = padding;
				hFont = CreateFont(DPI(18), 0, 0, 0, 500, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, TEXT("Microsoft YaHei"));
				DeleteObject((HFONT)SelectObject(hdc, hFont));
				SetTextColor(hdc, RGB(100,100,100));
				SetBkColor(hdc,RGB(255,255,255));
				for(int i = 0;i<9;i++){
					//Rectangle(hdc,nowLeft,TitleTextRc.top,nowLeft+ItemWidthArr[i],TitleTextRc.bottom);
					TextRc.left = nowLeft;
					TextRc.top = TitleTextRc.top;
					TextRc.right = nowLeft+ItemWidthArr[i];
					TextRc.bottom = TitleTextRc.bottom;
					switch (i) {
						case 4:
							DrawText(hdc,"音乐标题",-1,&TextRc,DT_VCENTER|DT_SINGLELINE);
							break;
						case 5:
							DrawText(hdc,"歌手",-1,&TextRc,DT_VCENTER|DT_SINGLELINE);
							break;
						case 6:
							DrawText(hdc,"专辑",-1,&TextRc,DT_VCENTER|DT_SINGLELINE);
							break;
						case 7:
							DrawText(hdc,"时长",-1,&TextRc,DT_VCENTER|DT_SINGLELINE);
							break;
						case 8:
							DrawText(hdc,"热度",-1,&TextRc,DT_VCENTER|DT_SINGLELINE);
							break;
						default:
							//TODO
							break;
					}
					
					nowLeft+=ItemWidthArr[i];
				}

			    ReleaseDC(hwnd, hdc);
			    EndPaint(hwnd, &ps);
			}
			break;
		case WM_DESTROY: {
			PostQuitMessage(0);
			break;
		}
		case WM_MOUSEMOVE:{
			int padding = DPI(28);
			int xPos = GET_X_LPARAM(lParam); 
			int yPos = GET_Y_LPARAM(lParam); 
			//添加一些鼠标触控间隙
			int gap = 2;
			int DownloadAll_x = DPI(140);
			
			
			RECT flashRect;
			flashRect.left = padding;
			flashRect.top = padding+DPI(40);
			flashRect.right = padding+DPI(140)+DownloadAll_x;
			flashRect.bottom = padding+DPI(74);
			
			
			if(xPos>padding-gap&&yPos>padding+DPI(40)-gap&&xPos<padding+DPI(140)+gap&&yPos<padding+DPI(74)+gap){
				if(!SearchResultPage.PlayALL){
					SearchResultPage.PlayALL = 1;
					InvalidateRect(HWNDM[H_SearchResultPage], NULL, TRUE);
				}
			}else{
				if(SearchResultPage.PlayALL){
					SearchResultPage.PlayALL = 0;
					InvalidateRect(HWNDM[H_SearchResultPage], NULL, TRUE);
				}
			}
			if(xPos>padding+DownloadAll_x+DPI(10)-gap&&yPos>padding+DPI(40)-gap&&xPos<padding+DPI(140)+DownloadAll_x+gap&&yPos<padding+DPI(74)+gap){
				if(!SearchResultPage.DownloadALL){
					SearchResultPage.DownloadALL = 1;
					InvalidateRect(HWNDM[H_SearchResultPage], NULL, TRUE);
				}
			}else{
				if(SearchResultPage.DownloadALL){
					SearchResultPage.DownloadALL = 0;
					InvalidateRect(HWNDM[H_SearchResultPage], NULL, TRUE);
				}
			}
			for(int i = 0;i<SearchItemInfo.size();i++){
				if(SearchItemInfo[i].mouseHover==1){
					SearchItemInfo[i].mouseHover = 0;
					InvalidateRect(SearchItemInfo[i].hwnd, NULL, TRUE);
				}
			}
			break;
		}
		default:
			return DefWindowProc(hwnd, Message, wParam, lParam);
	}
	return 0;
}


//音乐搜索结果项目
LRESULT CALLBACK SearchItemInfoProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam) {
	switch(Message) {
		case WM_PAINT:
			{
				PAINTSTRUCT ps;
				HDC hdc = BeginPaint(hwnd, &ps);
				HPEN hpen = CreatePen(PS_NULL, 1, RGB(0,0,0));
			    HPEN holdpen = (HPEN)SelectObject(hdc, hpen);
			    int ctrlId = GetDlgCtrlID(hwnd);
			    if(SearchResultPage.itemNum<ctrlId){
					safeSwitchColor(hdc,2,0,255,255,255);
					SelectObject(hdc,holdpen);
					DeleteObject(hpen);
				    ReleaseDC(hwnd, hdc);
				    EndPaint(hwnd, &ps);
				    break;
				}
			    if(SearchItemInfo[ctrlId-1].mouseHover){
					safeSwitchColor(hdc,2,0,242,242,243);
					SetBkColor(hdc,RGB(242,242,243));
				}else{
					if(ctrlId%2==0){
						safeSwitchColor(hdc,2,0,255,255,255);
						SetBkColor(hdc,RGB(255,255,255));
					}else{
						safeSwitchColor(hdc,2,0,250,250,250);
						SetBkColor(hdc,RGB(250,250,250));
					}
				}
			    Rectangle(hdc,0,0,ps.rcPaint.right,ps.rcPaint.bottom);
			    
			    HFONT hFont = CreateFont(DPI(18), 0, 0, 0, 500, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, TEXT("Microsoft YaHei"));
				DeleteObject((HFONT)SelectObject(hdc, hFont));
				SetTextColor(hdc, RGB(50,50,50));
				int nowLeft = 0;
				int ItemWidthArr[9]={SearchItemWidth.empty,SearchItemWidth.index,SearchItemWidth.love,SearchItemWidth.downlaod,SearchItemWidth.title,SearchItemWidth.artist,SearchItemWidth.album,SearchItemWidth.length,SearchItemWidth.heat};
				for(int i = 0;i<9;i++){
					RECT TextRc;
					TextRc.left = nowLeft;
					TextRc.top = 0;
					TextRc.right = nowLeft+ItemWidthArr[i]-DPI(10);
					TextRc.bottom = ps.rcPaint.bottom;
					switch (i) {
						case 1:{
								long long theid = SearchItemInfo[ctrlId-1].id;
								string idText = (theid<10?"0":"")+to_string(theid);
								SetTextColor(hdc, RGB(200,200,200));
								DrawText(hdc,idText.c_str(),-1,&TextRc,DT_VCENTER|DT_SINGLELINE);
								SetTextColor(hdc, RGB(50,50,50));
								break;
							}
						case 2:
							RECT heartRect;
							heartRect.left=TextRc.left - DPI(2);
							heartRect.top = TextRc.top + DPI(7);
							heartRect.right = TextRc.right - DPI(1);
							heartRect.bottom = TextRc.bottom - DPI(7);
							PlayEnhMetaFile(hdc,GetEnhMetaFileA(".\\res\\emf\\heart_grey.emf"),&heartRect);
							break;
						case 3:{
								safeSwitchColor(hdc,1,DPIW(1),179,179,179);
								MoveToEx(hdc, nowLeft+DPI(0), DPI(18), NULL);
								LineTo(hdc, nowLeft+DPI(0), DPI(23));
								LineTo(hdc, nowLeft+DPI(15), DPI(23));
								LineTo(hdc, nowLeft+DPI(15), DPI(18));
								MoveToEx(hdc, nowLeft+DPI(7), DPI(11), NULL);
								LineTo(hdc, nowLeft+DPI(7), DPI(19));
								LineTo(hdc, nowLeft+DPI(3), DPI(16));
								MoveToEx(hdc, nowLeft+DPI(7), DPI(19), NULL);
								LineTo(hdc, nowLeft+DPI(11), DPI(16));
								
								
								safeSwitchColor(hdc,3,0,0,0,0);
								break;
								}
							
						case 4:
							DrawText(hdc,SearchItemInfo[ctrlId-1].title.c_str(),-1,&TextRc,DT_VCENTER|DT_SINGLELINE|DT_END_ELLIPSIS);
							break;
						case 5:
							DrawText(hdc,SearchItemInfo[ctrlId-1].artist.c_str(),-1,&TextRc,DT_VCENTER|DT_SINGLELINE|DT_END_ELLIPSIS);
							break;
						case 6:
							DrawText(hdc,SearchItemInfo[ctrlId-1].album.c_str(),-1,&TextRc,DT_VCENTER|DT_SINGLELINE|DT_END_ELLIPSIS);
							break;
						case 7:
							SetTextColor(hdc, RGB(145,145,146));
							DrawText(hdc,SearchItemInfo[ctrlId-1].length.c_str(),-1,&TextRc,DT_VCENTER|DT_SINGLELINE);
							SetTextColor(hdc, RGB(50,50,50));
							break;
						case 8:
							//热度还没做好
							DrawText(hdc,"----------",-1,&TextRc,DT_VCENTER|DT_SINGLELINE);
							break;
						default:
							//TODO
							break;
					}
					
					nowLeft+=ItemWidthArr[i];
				}
			    
			    
				SelectObject(hdc,holdpen);
				DeleteObject(hpen);
			    ReleaseDC(hwnd, hdc);
			    EndPaint(hwnd, &ps);
			}
			break;
		case WM_LBUTTONDBLCLK:{
			int ctrlId = GetDlgCtrlID(hwnd);
			player.SetMusic(SearchItemInfo[ctrlId-1].songId);
			player.Play();
			cout<<ctrlId<<":"<<SearchItemInfo[ctrlId-1].songId<<endl;
			break;
			}
		case WM_DESTROY: {
			PostQuitMessage(0);
			break;
		}
		case WM_MOUSEMOVE:{
			int ctrlId = GetDlgCtrlID(hwnd);
			if(SearchItemInfo[ctrlId-1].mouseHover==0){
				SearchItemInfo[ctrlId-1].mouseHover = 1;
				InvalidateRect(hwnd, NULL, TRUE);
			}
			for(int i = 0;i<SearchItemInfo.size();i++){
				if((SearchItemInfo[i].mouseHover==1)&&(i!=ctrlId-1)){
					SearchItemInfo[i].mouseHover = 0;
					InvalidateRect(SearchItemInfo[i].hwnd, NULL, TRUE);
				}
			}
			break;
		}
		default:
			return DefWindowProc(hwnd, Message, wParam, lParam);
	}
	return 0;
}



//测试窗口标记矩形
LRESULT CALLBACK testWinProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam) {
	switch(Message) {
		case WM_PAINT:
			{
				PAINTSTRUCT ps;
				HDC hdc = BeginPaint(hwnd, &ps);
				HPEN hpen = CreatePen(PS_SOLID, 1, RGB(0,0,0));
			    HPEN holdpen = (HPEN)SelectObject(hdc, hpen);
			    Rectangle(hdc,0,0,ps.rcPaint.right,ps.rcPaint.bottom);
			    SelectObject(hdc,holdpen);
				DeleteObject(hpen);
			    ReleaseDC(hwnd, hdc);
			    EndPaint(hwnd, &ps);
			}
			break;
		case WM_DESTROY: {
			PostQuitMessage(0);
			break;
		}
		default:
			return DefWindowProc(hwnd, Message, wParam, lParam);
	}
	return 0;
}
