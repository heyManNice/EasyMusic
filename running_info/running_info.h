#ifndef RUNNINGINFO_H
#define RUNNINGINFO_H
#include <Windows.h>

//记录当前程序的重要参数和句柄供给后面其他代码使用
struct RunningInfo
{
    HINSTANCE hInstance;
    HINSTANCE hPrevInstance;
    LPSTR lpCmdLine;
    int nCmdShow;
    HWND hMainWin;
};

extern RunningInfo running_info;
#endif