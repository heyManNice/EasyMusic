#include "myhead.h"


int init_wc_Class(HINSTANCE hInstance){
	//主窗口类
	WNDCLASSEX Mainwin;
	memset(&Mainwin,0,sizeof(Mainwin));
	Mainwin.cbSize		 = sizeof(WNDCLASSEX);
	Mainwin.lpfnWndProc	 = WndProc;
	Mainwin.hInstance	 = hInstance;
	Mainwin.hCursor		 = LoadCursor(NULL, IDC_ARROW);
	Mainwin.style		 = CS_HREDRAW | CS_VREDRAW | CS_PARENTDC;
	Mainwin.hbrBackground = CreateSolidBrush(RGB(255,255,255));
	Mainwin.lpszClassName = TEXT("Mainwin");
	Mainwin.hIcon		 = (HICON)LoadImage(NULL, TEXT(".\\res\\ico\\netmusic_logoS.ico"), IMAGE_ICON, 0, 0, LR_LOADFROMFILE);
	Mainwin.hIconSm		 = (HICON)LoadImage(NULL, TEXT(".\\res\\ico\\netmusic_logoS.ico"), IMAGE_ICON, 0, 0, LR_LOADFROMFILE);
	cheackClass(Mainwin);
	
	//head栏类
	WNDCLASSEX myhead;
	memset(&myhead,0,sizeof(myhead));
	myhead.cbSize		 = sizeof(WNDCLASSEX);
	myhead.lpfnWndProc	 = mytitleProc;
	myhead.hInstance	 = hInstance;
	myhead.hCursor		 = LoadCursor(NULL, IDC_ARROW);	
	myhead.hbrBackground = CreateSolidBrush(RGB(236,65,65));
	myhead.lpszClassName = TEXT("myhead");
	cheackClass(myhead);
	
	//foot栏类
	WNDCLASSEX myfoot;
	memset(&myfoot,0,sizeof(myfoot));
	myfoot.cbSize		 = sizeof(WNDCLASSEX);
	myfoot.lpfnWndProc	 = myfootProc;
	myfoot.hInstance	 = hInstance;
	myfoot.hCursor		 = LoadCursor(NULL, IDC_ARROW);	
	myfoot.hbrBackground = CreateSolidBrush(RGB(49,193,228));
	myfoot.lpszClassName = TEXT("myfoot");
	cheackClass(myfoot);
	
	//左边的菜单类
	WNDCLASSEX LMENU;
	memset(&LMENU,0,sizeof(LMENU));
	LMENU.cbSize		 = sizeof(WNDCLASSEX);
	LMENU.lpfnWndProc	 = L_menuProc;
	LMENU.hInstance	 = hInstance;
	LMENU.hCursor		 = LoadCursor(NULL, IDC_ARROW);	
	LMENU.hbrBackground = CreateSolidBrush(RGB(255,255,255));
	LMENU.lpszClassName = TEXT("Lmenu");
	cheackClass(LMENU);
	
	//主功能菜单按钮
	WNDCLASSEX MainIndex_Btn;
	memset(&MainIndex_Btn,0,sizeof(MainIndex_Btn));
	MainIndex_Btn.cbSize		 = sizeof(WNDCLASSEX);
	MainIndex_Btn.lpfnWndProc	 = L_MainIndex_btnProc;
	MainIndex_Btn.hInstance	 = hInstance;
	MainIndex_Btn.hCursor		 = LoadCursor(NULL, IDC_ARROW);
	MainIndex_Btn.hbrBackground = CreateSolidBrush(RGB(255,255,255));
	MainIndex_Btn.lpszClassName = TEXT("MainIndex_Btn");
	cheackClass(MainIndex_Btn);
	
	//我的音乐功能菜单按钮
	WNDCLASSEX myMusicItem_Btn;
	memset(&myMusicItem_Btn,0,sizeof(myMusicItem_Btn));
	myMusicItem_Btn.cbSize		 = sizeof(WNDCLASSEX);
	myMusicItem_Btn.lpfnWndProc	 = L_Mymusic_btnProc;
	myMusicItem_Btn.hInstance	 = hInstance;
	myMusicItem_Btn.hCursor		 = LoadCursor(NULL, IDC_ARROW);
	myMusicItem_Btn.hbrBackground = CreateSolidBrush(RGB(255,255,255));
	myMusicItem_Btn.lpszClassName = TEXT("myMusicItem_Btn");
	cheackClass(myMusicItem_Btn);
	
	//左边的菜单类滚动区域
	WNDCLASSEX LMENU_scroll;
	memset(&LMENU_scroll,0,sizeof(LMENU_scroll));
	LMENU_scroll.cbSize		 = sizeof(WNDCLASSEX);
	LMENU_scroll.lpfnWndProc	 = DefWindowProc;
	LMENU_scroll.hInstance	 = hInstance;
	LMENU_scroll.hCursor		 = LoadCursor(NULL, IDC_ARROW);	
	//LMENU_scroll.hbrBackground = CreateSolidBrush(RGB(33,52,65));
	LMENU_scroll.lpszClassName = TEXT("LMENU_scroll");
	cheackClass(LMENU_scroll);
	
	//编辑框的外边框
	WNDCLASSEX Edit_out_class;
	memset(&Edit_out_class,0,sizeof(Edit_out_class));
	Edit_out_class.cbSize		 = sizeof(WNDCLASSEX);
	Edit_out_class.lpfnWndProc	 = Edit_out_Proc;
	Edit_out_class.hInstance	 = hInstance;
	Edit_out_class.hCursor		 = LoadCursor(NULL, IDC_ARROW);	
	Edit_out_class.hbrBackground = CreateSolidBrush(RGB(227, 62, 62));
	Edit_out_class.lpszClassName = TEXT("Edit_out_class");
	cheackClass(Edit_out_class);
	
	//右上角按钮组类
	WNDCLASSEX myOP_Btn_Class;
	memset(&myOP_Btn_Class,0,sizeof(myOP_Btn_Class));
	myOP_Btn_Class.cbSize		 = sizeof(WNDCLASSEX);
	myOP_Btn_Class.lpfnWndProc	 = myOP_BtnProc;
	myOP_Btn_Class.hInstance	 = hInstance;
	myOP_Btn_Class.hCursor		 = LoadCursor(NULL, IDC_ARROW);	
	myOP_Btn_Class.hbrBackground = CreateSolidBrush(RGB(236,65,65));
	myOP_Btn_Class.lpszClassName = TEXT("myOP_Btn_Class");
	cheackClass(myOP_Btn_Class);
	
	//白色背景类
	WNDCLASSEX WhiteBackgroundClass;
	memset(&WhiteBackgroundClass,0,sizeof(WhiteBackgroundClass));
	WhiteBackgroundClass.cbSize		   = sizeof(WNDCLASSEX);
	WhiteBackgroundClass.lpfnWndProc   = SearchResultPageProc;
	WhiteBackgroundClass.hInstance	   = hInstance;
	WhiteBackgroundClass.hCursor	   = LoadCursor(NULL, IDC_ARROW);	
	WhiteBackgroundClass.hbrBackground = CreateSolidBrush(RGB(255,255,255));
	WhiteBackgroundClass.lpszClassName = TEXT("WhiteBackgroundClass");
	cheackClass(WhiteBackgroundClass);
	
	return 0;
}
