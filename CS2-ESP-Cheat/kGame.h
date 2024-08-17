#pragma once
#include "kPlayerPawn.h"
#include "mem.h"
#include <iostream>
#include "kWindow.h"
#include "output/client.dll.hpp"
#include "output/offsets.hpp"




class kGame
{
public:
	kGame(const TCHAR* proc_name, RECT rect);
	~kGame();
	bool refreshData();
	void showAllPlayer();
	Matrix4x4 getMatrix();
	point3D getPlayerPawnPos(int indexPlayer);
	point2D world2screen(const point3D& point, const Matrix4x4& matrix);
	kPlayerPawn m_playPawn[10];
private:
	
	mem::Process* cs2;
	Matrix4x4 m_mViewMatrix = { 0 };
	RECT m_rect;
};

