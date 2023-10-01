#include "myhead.h"

char appName[] = "很容易音乐";
map<int,HWND> HWNDM;
map<int,HBITMAP> BITM;
double constDPI = 1;
//由于没有时间去弄网易云官方的api，这里先使用来自cloud-music.pl-fe.cn
string domainName = "cloud-music.pl-fe.cn";
PlayingSong player;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	SetProcessDPIAware();
	constDPI = GetScreenScale();
	
	if(0){
		AllocConsole();
		FILE* stream;
		freopen_s(&stream, "CON", "r", stdin);
		freopen_s(&stream, "CON", "w", stdout);
	}
	init_wc_Class(hInstance);
	init_gdiDevice();
	HWND hwnd = CreateWindowEx(WS_EX_OVERLAPPEDWINDOW,"Mainwin",appName,
								WS_VISIBLE | WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN,CW_USEDEFAULT,
								CW_USEDEFAULT,DPI(1022),DPI(670),
								NULL,NULL,hInstance,NULL);
	cheackWin(hwnd);
	
	//通过dwm的小技巧 保留无边框窗口的阴影，不知道什么原理，官方文档也没说
	const MARGINS shadow_on = { 0, 0, 0, 1 };
	DwmExtendFrameIntoClientArea(hwnd, &shadow_on);
	
	//初始化tooltip工具
	tooltip_tooltip(hInstance);
	
	HWNDM[H_MAIN_WIN]=hwnd;
	//加载head栏
	Loadhead(hInstance,hwnd);
	//加载foot栏
	Loadfoot(hInstance,hwnd);
	//加载左边的菜单
	LoadLmenu(hInstance,hwnd);
	
	UpdateWindow(hwnd);
	
	//player.SetMusic(2013478175);

	//消息循环
	MSG msg;
	while(GetMessage(&msg, NULL, 0, 0) > 0) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return msg.wParam;
}
