#pragma once
#include <Windows.h>
#include "kRender.h"
#include <dwmapi.h>
#include "kGame.h"
#pragma comment ( lib,"dwmapi.lib")
class kWindow
{
public:
	kWindow(const char* wndName);
	~kWindow();
	void msgLoop(kGame* game);
	void doCheat(kRender* render, kGame* game);
	RECT getRect();
	HWND hWnd = nullptr;
private:
	RECT m_rect;

};



