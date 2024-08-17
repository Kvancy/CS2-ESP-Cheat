#pragma once
#define D3DFVF_CUSTOMVERTEX (D3DFVF_XYZRHW | D3DFVF_DIFFUSE)
#include <d3d9.h>
#include <iostream>

#pragma comment(lib,"d3d9.lib")


class kRender
{
public:
	kRender(HWND hWnd);
	~kRender();
	void cleanUp();
	HRESULT drawRectangle(float x, float y, int width, int height);
	HRESULT drawLine(float x1, float y1, float x2, float y2);
	void drawText(const std::string& text, int x, int y, D3DCOLOR color);
	void beginRender();
	void endRender();
private:
	LPDIRECT3D9 m_pD3D = nullptr;
	LPDIRECT3DDEVICE9 m_pd3dDevice = nullptr;
	LPDIRECT3DVERTEXBUFFER9 m_pVB = nullptr;
	LPDIRECT3DSURFACE9 m_pBackBuffer = nullptr;
};






