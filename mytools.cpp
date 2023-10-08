#include "myhead.h"


int cheackWin(HWND hwnd){
	if(hwnd == NULL) {
		MessageBoxW(NULL, L"窗口创建失败!",L"错误!",MB_ICONEXCLAMATION|MB_OK);
		PostQuitMessage(0);
		return 1;
	}
	return 0;
};
int cheackClass(WNDCLASSEX wc){
	if(!RegisterClassEx(&wc)) {
		MessageBoxW(NULL, L"窗口类注册失败!",L"错误!",MB_ICONEXCLAMATION|MB_OK);
		PostQuitMessage(0);
	}
	return 0;
};

double GetScreenScale() {
    HDC hdc = GetDC(NULL);
	int dpiX = GetDeviceCaps(hdc, LOGPIXELSX);
	ReleaseDC(NULL, hdc);
	
    return dpiX/96.0;
}
int DPI(int num){
	return (int)(num*constDPI);
}
int DDPI(double num){
	return (int)(num*constDPI);
}
int DPIW(double num){
	return (int)(num*(constDPI+0.7));
}
double DPIP(double num){
	return num*constDPI;
}