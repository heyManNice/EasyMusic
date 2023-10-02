#include "myhead.h"

map<string,HPEN> myPEN;
map<string,HBRUSH> myBRUSH;

//常用的笔刷老是创建和删除感觉总不好，试试保存这些笔刷
//千万要删除创建的资源，我曾经因为忘记删除，导致gdi崩溃了

int init_gdiDevice(){
	myPEN["1_black"] = CreatePen(PS_SOLID, 1, RGB(0,0,0));
	myPEN["W1_white"] = CreatePen(PS_SOLID, DPIW(1), RGB(255,255,255));
	myPEN["1_white"] = CreatePen(PS_SOLID, 1, RGB(255,255,255));
	myPEN["1_gray_153"] = CreatePen(PS_SOLID, 1, RGB(153,153,153));
	myBRUSH["red_1"] = CreateSolidBrush(RGB(236,65,65));
	myBRUSH["red_1_hover"] = CreateSolidBrush(RGB(205,50,50));
	myBRUSH["white_1"] = CreateSolidBrush(RGB(255,255,255));
	myBRUSH["white_1_hover"] = CreateSolidBrush(RGB(242,242,242));
	return 0;
};

int safeSwitchColor(HDC hdc,int type,int w,int r,int g,int b){
	switch (type) {
		case 1:
			//笔
			return DeleteObject((HPEN)SelectObject(hdc, CreatePen(PS_SOLID, w, RGB(r,g,b))));
			break;
		case 2:
			//刷子
			return DeleteObject((HBRUSH)SelectObject(hdc, CreateSolidBrush(RGB(r,g,b))));
			break;
		case 3:
			//空笔
			return DeleteObject((HPEN)SelectObject(hdc, CreatePen(PS_NULL, 0, 0)));
			break;
		default:
			//TODO
			break;
	}
	return 0;
}
