#include <windows.h>
#include <winuser.h>
#include "myhead.h"
#include <commctrl.h>

std::map<int,SearchItemInfo__struct> SearchItemInfo;

void ToSearchMusic(std::string keyword){
	int padding = DPI(28);
	int margin_top = DPI(4);
	
	
	if(!HWNDM[H_SearchResultPage]){
		RECT MainRect;
		GetWindowRect(HWNDM[H_MAIN_WIN], &MainRect);
		int width = MainRect.right - MainRect.left;
		int height = MainRect.bottom - MainRect.top;
		HWNDM[H_SearchResultPage] = CreateWindowW( L"WhiteBackgroundClass",L"搜索结果页",WS_VISIBLE | WS_CHILD,
									    DPI(200),DPI(60),width-DPI(200),
									    height-DPI(60)-DPI(67),HWNDM[H_MAIN_WIN],NULL,
									    (HINSTANCE)GetWindowLongPtr(HWNDM[H_MAIN_WIN], GWLP_HINSTANCE),NULL);
	}
	SearchResultPage.keyword = keyword;
	
	RECT SearchResultPageRect;
	GetWindowRect(HWNDM[H_SearchResultPage], &SearchResultPageRect);
	int height = SearchResultPageRect.bottom - SearchResultPageRect.top;
	int width = SearchResultPageRect.right - SearchResultPageRect.left;
	std::string url = "/search?limit=12&keywords=" + UrlEncode(GbkToUtf8(keyword.c_str()));
	auto[code, data] = net_GET(url);
	//cout<<Utf8ToGbk(search_result)<<endl;
	
	yyjson_doc *doc = yyjson_read(data.c_str(), data.size(), 0);
	yyjson_val *root = yyjson_doc_get_root(doc);
	yyjson_val *temp = yyjson_obj_get(root, "result");
	temp = yyjson_obj_get(temp, "songs");
	size_t idx, max;
	yyjson_val *song;
	yyjson_arr_foreach(temp, idx, max, song) {
		SearchItemInfo[idx].itemRect.left = padding;
		SearchItemInfo[idx].itemRect.top = padding+DPI(124)+idx*DPI(34);
		SearchItemInfo[idx].itemRect.right = width - padding;
		SearchItemInfo[idx].itemRect.bottom = padding+DPI(158)+idx*DPI(34);
		
		SearchItemInfo[idx].id = idx+1;
		SearchItemInfo[idx].title = Utf8ToGbk(yyjson_get_str(yyjson_obj_get(song,"name")));
		SearchItemInfo[idx].songId = yyjson_get_int(yyjson_obj_get(song,"id"));
		SearchItemInfo[idx].artist = Utf8ToGbk(yyjson_get_str(yyjson_obj_get(yyjson_arr_get(yyjson_obj_get(song,"artists"),0),"name")));
		SearchItemInfo[idx].album = Utf8ToGbk(yyjson_get_str(yyjson_obj_get(yyjson_obj_get(song,"album"),"name")));
		
		int mm = 0;
		int ss;
		int duration = yyjson_get_int(yyjson_obj_get(song,"duration"))/1000;
		while(duration>59){
			duration-=60;
			mm++;
		}
		ss=duration;
		SearchItemInfo[idx].length = (mm<10?"0":"") + std::to_string(mm)+":" + (ss<10?"0":"") + std::to_string(ss);
		
	}
	SearchResultPage.itemNum=idx;
	for(int i = 0;i<SearchItemInfo.size();i++){
		if(i>30){
			//防止意外出现死循环，手动退出
			PostQuitMessage(20);
			break;
		}
		if(!SearchItemInfo[i].hwnd){
			SearchItemInfo[i].hwnd = CreateWindowW( L"STATIC",L"搜索结果项目",WS_VISIBLE | WS_CHILD,
										    SearchItemInfo[i].itemRect.left,SearchItemInfo[i].itemRect.top,SearchItemInfo[i].itemRect.right-SearchItemInfo[i].itemRect.left,
										    SearchItemInfo[i].itemRect.bottom-SearchItemInfo[i].itemRect.top,HWNDM[H_SearchResultPage],(HMENU)SearchItemInfo[i].id,
										    (HINSTANCE)GetWindowLongPtr(HWNDM[H_SearchResultPage], GWLP_HINSTANCE),NULL);
			SetWindowLongPtr(SearchItemInfo[i].hwnd, GWLP_WNDPROC, (LONG_PTR)SearchItemInfoProc);
		}
		
		
		//cout<<"test:"<<SearchItemInfo[i].id<<SearchItemInfo[i].title<<SearchItemInfo[i].songId<<SearchItemInfo[i].artist<<i<<endl;
	}
	InvalidateRect(HWNDM[H_SearchResultPage], NULL, TRUE);
	//cout<<1;
}

LONG_PTR OldEditProc;
//搜索框事件
LRESULT CALLBACK searchEditProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam) {
	switch(Message) {
		case WM_CHAR:{
			if(wParam == VK_RETURN){
				int len = GetWindowTextLengthA(hwnd);
				if(len!=0){
					char Text[255];
					memset(Text,0,255);
					GetWindowTextA(hwnd,Text,len+1);
					//cout<<"接收到:"<<len<<"->"<<Text<<endl;
					ToSearchMusic(Text);
	                return 0;
				}
			}
			return CallWindowProc((WNDPROC)OldEditProc, hwnd, Message, wParam, lParam);
		}
		case WM_DESTROY: {
			PostQuitMessage(0);
			break;
		}
		default:
			return CallWindowProc((WNDPROC)OldEditProc, hwnd, Message, wParam, lParam);
	}
	return 0;
}

int Loadhead(HINSTANCE hInstance,HWND hwnd){
	
//	RECT MainRect;
//	GetWindowRect(HWNDM[H_MAIN_WIN], &MainRect);
//	int width = MainRect.right - MainRect.left;
//	int height = MainRect.bottom - MainRect.top;
//	HWNDM[H_SearchResultPage] = CreateWindowW( L"WhiteBackgroundClass",L"搜索结果页",WS_VISIBLE | WS_CHILD,
//								    DPI(200),DPI(60),width-DPI(200),
//								    height-DPI(60)-DPI(67),HWNDM[H_MAIN_WIN],NULL,
//								    (HINSTANCE)GetWindowLongPtr(HWNDM[H_MAIN_WIN], GWLP_HINSTANCE),NULL);
	
	
	
	
	
	HWND MainTitle = CreateWindowW( L"myhead",L"head栏",WS_VISIBLE | WS_CHILD,
								    0,0,DPI(1022),
								    DPI(60),hwnd,NULL,
								    (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE),NULL);
	HWNDM[H_MYHEAD]=MainTitle;
	
	//输入框外边框
	HWND Edit_out_hwnm = CreateWindowExA(0, "Edit_out_class",NULL,
										WS_CHILD | WS_VISIBLE,DDPI(296.66), DDPI(12.33),
										DPI(200), DDPI(33.33),MainTitle,
										NULL,(HINSTANCE)GetWindowLongPtr(MainTitle, GWLP_HINSTANCE),NULL);
	
	HRGN hRgn = CreateRoundRectRgn(0, 0, DDPI(163.33), DDPI(33.33), DPI(30), DDPI(26.66));
	SetWindowRgn(Edit_out_hwnm, hRgn, TRUE);
	UpdateWindow(Edit_out_hwnm);
	
	HWND hwnd_search = CreateWindowExA(0, "STATIC", "clsoe_btn", WS_CHILD | WS_VISIBLE, DDPI(6.66), DDPI(4.5), DDPI(23.33), DDPI(23.33), Edit_out_hwnm, NULL, (HINSTANCE)GetWindowLongPtr(Edit_out_hwnm, GWLP_HINSTANCE), NULL);
	SetWindowLongPtr(hwnd_search, GWLP_WNDPROC, (LONG_PTR)searchProc);
	//输入框
	
	HWND Edit = CreateWindowExA(0, "EDIT",NULL,
								WS_CHILD | WS_VISIBLE | ES_LEFT | ES_AUTOHSCROLL | ES_WANTRETURN,DDPI(30.66), DDPI(8),
								DPI(120), DDPI(23),Edit_out_hwnm,
								(HMENU)23,(HINSTANCE)GetWindowLongPtr(Edit_out_hwnm, GWLP_HINSTANCE),NULL);
	LOGFONT lf;
	memset(&lf, 0, sizeof(LOGFONT));
	lf.lfHeight = DDPI(17); 
	lf.lfWeight = 550;
	lstrcpy(lf.lfFaceName, TEXT("Microsoft YaHei"));
	HFONT hFont = CreateFontIndirect(&lf);

	SendMessage(Edit, WM_SETFONT, (WPARAM)hFont, TRUE);
	
	OldEditProc = SetWindowLongPtr(Edit, GWLP_WNDPROC, (LONG_PTR)searchEditProc);


	
	//logo
	HWND hWndLogo = CreateWindowExA(0, "STATIC", "myLogo", WS_CHILD | WS_VISIBLE, DPI(15), DPI(15), DDPI(133), DPI(33), MainTitle, NULL, (HINSTANCE)GetWindowLongPtr(MainTitle, GWLP_HINSTANCE), NULL);
	SetWindowLongPtr(hWndLogo, GWLP_WNDPROC, (LONG_PTR)logoProc);
	
	
	//按钮组
	HWND hwnd_myOP_Btn = CreateWindowW( L"myOP_Btn_Class",L"右上角操作按钮组",WS_VISIBLE | WS_CHILD,
									    DPI(1022-190),DPI(15),DPI(173),
									    DPI(37),MainTitle,NULL,
									    (HINSTANCE)GetWindowLongPtr(MainTitle, GWLP_HINSTANCE),NULL);
	HWNDM[H_OPBTN] = hwnd_myOP_Btn;
	
	
	//这种方法感觉非常不好，我觉得像是底部控制音乐按钮那种绘制方式更优美
	HWND hwnd_close = CreateWindowExA(0, "STATIC", "clsoe_btn", WS_CHILD | WS_VISIBLE, DPI(140), 0, DPI(37), DPI(37), hwnd_myOP_Btn, NULL, (HINSTANCE)GetWindowLongPtr(hwnd_myOP_Btn, GWLP_HINSTANCE), NULL);
	SetWindowLongPtr(hwnd_close, GWLP_WNDPROC, (LONG_PTR)closeProc);
	
	HWND hwnd_tofullS = CreateWindowExA(0, "STATIC", "clsoe_btn", WS_CHILD | WS_VISIBLE, DDPI(106.33), 0, DPI(37), DPI(37), hwnd_myOP_Btn, NULL, (HINSTANCE)GetWindowLongPtr(hwnd_myOP_Btn, GWLP_HINSTANCE), NULL);
	SetWindowLongPtr(hwnd_tofullS, GWLP_WNDPROC, (LONG_PTR)tofullSProc);
	
	HWND hwnd_tosmallS = CreateWindowExA(0, "STATIC", "clsoe_btn", WS_CHILD | WS_VISIBLE, DPI(70), 0, DPI(37), DPI(37), hwnd_myOP_Btn, NULL, (HINSTANCE)GetWindowLongPtr(hwnd_myOP_Btn, GWLP_HINSTANCE), NULL);
	SetWindowLongPtr(hwnd_tosmallS, GWLP_WNDPROC, (LONG_PTR)tosmallSProc);
	
	HWND hwnd_tomini = CreateWindowExA(0, "STATIC", "clsoe_btn", WS_CHILD | WS_VISIBLE, DDPI(35.33), 0, DPI(37), DPI(37), hwnd_myOP_Btn, NULL, (HINSTANCE)GetWindowLongPtr(hwnd_myOP_Btn, GWLP_HINSTANCE), NULL);
	SetWindowLongPtr(hwnd_tomini, GWLP_WNDPROC, (LONG_PTR)tominiProc);
	return 0;
}
