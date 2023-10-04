#ifndef TOOLTIP_H
#define TOOLTIP_H

#include <Windows.h>
#include <string>
#include "../running_info/running_info.h"
#include "../myhead.h"
class Tooltip
{
private:
    std::wstring Text_;
public:
    HWND hwnd_;
    int Show_(std::wstring str,int x, int y);
    int Hide_();
    int OnPaint_(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam);
    Tooltip();
    ~Tooltip();
};
extern Tooltip tooltip;
#endif