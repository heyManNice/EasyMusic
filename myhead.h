
#ifndef MYHEAD_H
#define MYHEAD_H
#include <iostream>

#include<string>
#include<assert.h>
#include<fstream>

#include <format>
#include "yyjson/yyjson.h"

#include <windows.h>
#include <windowsx.h>
#include <map>
#include <winuser.h>
#include <string>
#include <windef.h>
//#include <unistd.h>


//#include "FreeImage.h"
//#pragma comment(lib, "FreeImage.lib")

#include <dwmapi.h>
#pragma comment(lib, "Dwmapi.lib")

#include <mmsystem.h>
#pragma comment(lib, "WinMM.lib")

//#include <gdiplus.h>
//#pragma comment (lib,"gdiplus.lib")

#include <wininet.h>
#pragma comment(lib, "wininet.lib")

//using namespace Gdiplus;

using namespace std;

//主窗口事件
LRESULT CALLBACK WndProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam);
//head栏事件
LRESULT CALLBACK mytitleProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam);
//右上角操作按钮组事件
LRESULT CALLBACK myOP_BtnProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam);
//关闭按钮事件
LRESULT CALLBACK closeProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam);
//输入框事件
LRESULT CALLBACK Edit_out_Proc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam);
//foot栏事件
LRESULT CALLBACK myfootProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam);

//最大化还原按钮
LRESULT CALLBACK tofullSProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam);
//最小化按钮
LRESULT CALLBACK tosmallSProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam);
//mini模式按钮
LRESULT CALLBACK tominiProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam);
//搜索栏搜索图标
LRESULT CALLBACK searchProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam);
//logo过程
LRESULT CALLBACK logoProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam);
//左边菜单事件
LRESULT CALLBACK L_menuProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam);
//主功能菜单
LRESULT CALLBACK L_MainIndexProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam);
//主功能菜单按钮
LRESULT CALLBACK L_MainIndex_btnProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam);
//我的音乐功能菜单
LRESULT CALLBACK MyMusicIndexProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam);
//功能菜单小标题
LRESULT CALLBACK IndexTitleProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam);
//我的音乐菜单按钮
LRESULT CALLBACK L_Mymusic_btnProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam);
//测试窗口标记矩形
LRESULT CALLBACK testWinProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam);
//底部左侧播放中的歌曲信息
LRESULT CALLBACK footLProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam);
//底部控制按钮组
LRESULT CALLBACK PlayingControlProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam);
//底部右侧的播放设置
LRESULT CALLBACK PlayingSetProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam);
//控制音量面板
LRESULT CALLBACK VolumePanelProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam);
//搜索框事件
LRESULT CALLBACK searchEditProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam);
//搜索结果页
LRESULT CALLBACK SearchResultPageProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam);
//音乐搜索结果项目
LRESULT CALLBACK SearchItemInfoProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam);



//加载head栏
int Loadhead(HINSTANCE hInstance,HWND hwnd);
//加载foot栏
int Loadfoot(HINSTANCE hInstance,HWND hwnd);
//初始化窗口类
int init_wc_Class(HINSTANCE hInstance);
//检测窗口是否创建成功
int cheackWin(HWND hwnd);
//检测窗口类是否注册成功
int cheackClass(WNDCLASSEX wc);
//加载左边的菜单
int LoadLmenu(HINSTANCE hInstance,HWND hwnd);
//获取屏幕缩放比例
double GetScreenScale();
//dpi转换数值
int DPI(int num);
int DDPI(double num);
int DPIW(double num);
double DPIP(double num);

//tooltip工具
int tooltip_tooltip(HINSTANCE hInstance);
int tooltip_show(std::string str,int x, int y);
int tooltip_hide();


//初始化绘图设备
int init_gdiDevice();

//字符集转换
string Utf8ToGbk(const char *src_str);
string GbkToUtf8(const char *src_str);
//url编码解码
std::string UrlEncode(const std::string& str);
std::string UrlDecode(const std::string& str);
//http get请求
int net_GET(string url,char *result);

//调音量面板的显示与隐藏
void VolumePanel_show();
void VolumePanel_hide();

//安全切换绘图设备
int safeSwitchColor(HDC hdc,int type,int w,int r,int g,int b);

struct MainIndexBTN{
	HWND hwnd;
	int id;
	int mouseHover = 0;
	int checked = 0;
	string text = "";
	HENHMETAFILE emf;
};



struct MenuItem{
	HWND hwnd;
	int height;
	map<int,MainIndexBTN> childItem; 
};


//正在播放类
class PlayingSong{
	public:
		int id;
		string name;
		string artist;
		string album;
		string url;
		string cover;
		string lrc;
		string totalTime_str;
		string position_str;
		long totalTime;
		long position;
		int time;
		int playing;
		int newVolume;
		int theVolumeBeforeMute;
		void SetMusic(int id);
		void Play();
		void Pause();
		void getTotalTime_str();
		void getPosition_str();
		void ProgressLoop();
		void PlayFromPosition(long position);
		void setVolume(int Vnum);
		int getVolume();
};

struct SearchResultPage_struct{
	string keyword;
	int PlayALL = 0;
	int DownloadALL = 0;
	int itemNum = 0;
};
struct SearchItemWidth_struct{
	int empty = DPI(40);
	int index = DPI(40);
	int love = DPI(40);
	int downlaod = DPI(40);
	int title;
	int artist;
	int album;
	int length = DPI(80);
	int heat = DPI(130);
};

struct SearchItemInfo__struct{
	HWND hwnd;
	long long id;
	int songId;
	int mouseHover = 0;
	int checked = 0;
	int isLove = 0;
	int isDownload = 0;
	string title;
	string artist;
	string album;
	string length;
	int heat;
	RECT itemRect;
};


//导出的全局变量
extern map<int,HWND> HWNDM;
extern map<int,HBITMAP> BITM;
extern double constDPI;
extern char appName[];
extern map<int,MainIndexBTN> MainIndexList;
extern map<string,HPEN> myPEN;
extern map<string,HBRUSH> myBRUSH;
extern map<int,MenuItem> MenuItemList;
extern map<int,MainIndexBTN> MyMusicItemList;
extern string domainName;
extern PlayingSong player;
extern SearchResultPage_struct SearchResultPage;
extern SearchItemWidth_struct SearchItemWidth;
extern map<int,SearchItemInfo__struct> SearchItemInfo;

//定义窗口管理常量
#define H_MAIN_WIN  	1
#define H_MYHEAD		2
#define H_OPBTN			3
#define H_MYFOOT		4
#define H_LMENU			5
#define H_tooltip		6
#define H_PlayingInfo_m	7
#define H_PlayingSet_m	8
#define H_PlayingControl 9
#define H_VolumePanel	10
#define H_SearchResultPage 11

//定义位图常量
#define BIT_CLOSE		1



#endif
