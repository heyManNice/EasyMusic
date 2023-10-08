#include "myhead.h"

std::map<int,MainIndexBTN> MainIndexList;

std::map<int,MainIndexBTN> MyMusicItemList;

std::map<int,MenuItem> MenuItemList;

int addMainIndexItem(std::wstring text){
	MainIndexBTN temp;
	temp.text = text;
	int num = MainIndexList.size()+1;
	temp.id = num;
	MainIndexList[num]=temp;
	return num;
};
int addMyMusicItem(std::wstring text,LPCSTR icon){
	MainIndexBTN temp;
	temp.text = text;
	temp.emf = GetEnhMetaFileA(icon);
	int num = MyMusicItemList.size()+1;
	temp.id = num;
	MyMusicItemList[num]=temp;
	return num;
};

int LoadLmenu(HINSTANCE hInstance,HWND hwnd){
	HWND myLMENU = CreateWindowW( L"Lmenu",L"左边的菜单",WS_VISIBLE | WS_CHILD,
							    0,DPI(60),DPI(200),
							    DPI(543),hwnd,NULL,
							    (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE),NULL);
	HWNDM[H_LMENU]=myLMENU;
	RECT myLMENU_rect;
	GetWindowRect(myLMENU, &myLMENU_rect);
	int LM_width = myLMENU_rect.right - myLMENU_rect.left;
	int LM_height = myLMENU_rect.bottom - myLMENU_rect.top;
	
	HWND H_L_menu_scroll_win = CreateWindowW( L"LMENU_scroll",L"左边的菜单滚动区域",WS_VISIBLE | WS_CHILD,
							    0,0,LM_width-DPI(10),
							    LM_height,myLMENU,NULL,
							    (HINSTANCE)GetWindowLongPtr(myLMENU, GWLP_HINSTANCE),NULL);
	RECT menu_scroll_rect;
	GetWindowRect(H_L_menu_scroll_win, &menu_scroll_rect);
	int LMS_width = menu_scroll_rect.right - menu_scroll_rect.left;
	int LMS_height = menu_scroll_rect.bottom - menu_scroll_rect.top;
	HWND H_MainIndex = CreateWindowW( L"STATIC",L"主功能菜单",WS_VISIBLE | WS_CHILD,
					    DPI(12),DPI(12),LMS_width-DPI(12),
					    0,H_L_menu_scroll_win,NULL,
					    (HINSTANCE)GetWindowLongPtr(H_L_menu_scroll_win, GWLP_HINSTANCE),NULL);
	SetWindowLongPtr(H_MainIndex, GWLP_WNDPROC, (LONG_PTR)L_MainIndexProc);
	MenuItemList[1].hwnd = H_MainIndex;
	MenuItemList[1].childItem = MainIndexList;

	addMainIndexItem(L"发现音乐");
	addMainIndexItem(L"博客");
	addMainIndexItem(L"视频");
	addMainIndexItem(L"关注");
	addMainIndexItem(L"私人FM");
	for(long long i=1;i<=MainIndexList.size();i++){
		MainIndexList[i].hwnd = CreateWindowW( L"MainIndex_Btn",L"主功能菜单按钮",WS_VISIBLE | WS_CHILD,
							    0,(i-1)*DPI(39),LMS_width-DPI(12),
							    DPI(37),H_MainIndex,(HMENU)i,
							    (HINSTANCE)GetWindowLongPtr(H_MainIndex, GWLP_HINSTANCE),NULL);
	}
	MenuItemList[1].height = MainIndexList.size()*DPI(39)+DPI(4);
	SetWindowPos(H_MainIndex,HWND_TOP,0,0,LMS_width-DPI(12),MenuItemList[1].height,SWP_NOMOVE);
	//第二个菜单在第一个菜单的高度上再加外边框12;
	MenuItemList[2].hwnd = CreateWindowW( L"STATIC",L"我的音乐功能菜单",WS_VISIBLE | WS_CHILD,
									    DPI(12),MenuItemList[1].height+DPI(12),LMS_width-DPI(12),
									    0,H_L_menu_scroll_win,NULL,
									    (HINSTANCE)GetWindowLongPtr(H_L_menu_scroll_win, GWLP_HINSTANCE),NULL);
	SetWindowLongPtr(MenuItemList[2].hwnd, GWLP_WNDPROC, (LONG_PTR)MyMusicIndexProc);
	HWND H_mymusic_title = CreateWindowW( L"STATIC",L"我的音乐标题",WS_VISIBLE | WS_CHILD,
							    0,0,LMS_width-DPI(12),
							    DPI(27),MenuItemList[2].hwnd,NULL,
							    (HINSTANCE)GetWindowLongPtr(MenuItemList[2].hwnd, GWLP_HINSTANCE),NULL);
	SetWindowLongPtr(H_mymusic_title, GWLP_WNDPROC, (LONG_PTR)IndexTitleProc);
	MenuItemList[2].childItem = MyMusicItemList;
	addMyMusicItem(L"我喜欢的音乐",".\\res\\emf\\heart.emf");
	addMyMusicItem(L"本地与下载",".\\res\\emf\\download.emf");
	addMyMusicItem(L"最近播放",".\\res\\emf\\clock.emf");
	addMyMusicItem(L"我的音乐云盘",".\\res\\emf\\cloud.emf");
	addMyMusicItem(L"我的播客",".\\res\\emf\\music.emf");
	addMyMusicItem(L"我的收藏",".\\res\\emf\\collect.emf");
	for(long long i=1;i<=MyMusicItemList.size();i++){
		MyMusicItemList[i].hwnd = CreateWindowW( L"myMusicItem_Btn",L"我的音乐功能按钮",WS_VISIBLE | WS_CHILD,
							    0,(i-1)*DPI(39)+DPI(27),LMS_width-DPI(12),
							    DPI(37),MenuItemList[2].hwnd,(HMENU)i,
							    (HINSTANCE)GetWindowLongPtr(MenuItemList[2].hwnd, GWLP_HINSTANCE),NULL);
	}
	MenuItemList[2].height = MyMusicItemList.size()*DPI(39)+DPI(27)+DPI(4);
	SetWindowPos(MenuItemList[2].hwnd,HWND_TOP,0,0,LMS_width-DPI(12),MenuItemList[2].height,SWP_NOMOVE);
	
	
	return 0;
}
