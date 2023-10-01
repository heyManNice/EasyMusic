#include "myhead.h"


int Loadfoot(HINSTANCE hInstance,HWND hwnd){
	RECT Mainrect;
	GetWindowRect(hwnd, &Mainrect);
	int height = Mainrect.bottom - Mainrect.top;
	int width = Mainrect.right - Mainrect.left;
	
	HWND H_PlayingInfo = CreateWindowW( L"STATIC",L"底部左侧播放中的歌曲信息",WS_VISIBLE | WS_CHILD,
									    DPI(12),height-DPI(55),DPI(250),
									    DPI(43),hwnd,NULL,
									    (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE),NULL);
	SetWindowLongPtr(H_PlayingInfo, GWLP_WNDPROC, (LONG_PTR)footLProc);
	HWNDM[H_PlayingInfo_m] = H_PlayingInfo;

	HWNDM[H_PlayingSet_m] = CreateWindowW( L"STATIC",L"底部右侧的播放设置",WS_VISIBLE | WS_CHILD,
										    width-DPI(250)-DPI(12),height-DPI(53),DPI(250),
										    DPI(39),hwnd,NULL,
										    (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE),NULL);
	SetWindowLongPtr(HWNDM[H_PlayingSet_m], GWLP_WNDPROC, (LONG_PTR)PlayingSetProc);
	
	int PcontrolWidth = DPI(420);
	
	HWNDM[H_PlayingControl] = CreateWindowW( L"STATIC",L"底部控制按钮组",WS_VISIBLE | WS_CHILD,
											    (width-PcontrolWidth)/2,height-DPI(67-10),PcontrolWidth,
											    DPI(67-10*2),hwnd,NULL,
											    (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE),NULL);
	
	SetWindowLongPtr(HWNDM[H_PlayingControl], GWLP_WNDPROC, (LONG_PTR)PlayingControlProc);
	
	//控制音量面板
	HWNDM[H_VolumePanel] = CreateWindowW( L"STATIC",L"控制音量面板",WS_CHILD|WS_CLIPSIBLINGS,
											    width-DPI(126),height-DPI(49+100),DPI(30),
											    DPI(100),hwnd,NULL,
											    (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE),NULL);							
										
	SetWindowLongPtr(HWNDM[H_VolumePanel], GWLP_WNDPROC, (LONG_PTR)VolumePanelProc);
	return 0;
};
void VolumePanel_show(){
	if(!IsWindowVisible(HWNDM[H_VolumePanel])){
		ShowWindow(HWNDM[H_VolumePanel],SW_SHOWNA);
	}
}
void VolumePanel_hide(){
	SetWindowPos(HWNDM[H_VolumePanel],HWND_TOP,0,0,0,0,SWP_HIDEWINDOW|SWP_NOSIZE|SWP_NOMOVE);
	InvalidateRect(HWNDM[H_SearchResultPage], NULL, TRUE);
}
