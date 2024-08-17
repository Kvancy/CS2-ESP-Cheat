#include "kRender.h"

struct CUSTOMVERTEX {
    FLOAT x, y, z;
    FLOAT rhw;
    DWORD color;
};
kRender::kRender(HWND hWnd)
{
    if ((m_pD3D = Direct3DCreate9(D3D_SDK_VERSION)) == NULL)
    {
        std::cout << "Direct3DCreate9 faild" << std::endl;
    }

    D3DPRESENT_PARAMETERS d3dpp;
    ZeroMemory(&d3dpp, sizeof(d3dpp));
    d3dpp.Windowed = TRUE;
    d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
    d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;

    if (FAILED(m_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd,
        D3DCREATE_SOFTWARE_VERTEXPROCESSING,
        &d3dpp, &m_pd3dDevice))) {
        std::cout << "CreateDevice faild" << std::endl;
    }
    /*m_pd3dDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
    m_pd3dDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
    m_pd3dDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);*/
    if (FAILED(m_pd3dDevice->CreateVertexBuffer(4 * sizeof(CUSTOMVERTEX),
        0, D3DFVF_CUSTOMVERTEX,
        D3DPOOL_DEFAULT, &m_pVB, NULL))) {
        std::cout << "CreateVertexBuffer faild" << std::endl;
    }
}

kRender::~kRender()
{

}

void kRender::cleanUp()
{
    if (m_pVB != NULL)
        m_pVB->Release();

    if (m_pd3dDevice != NULL)
        m_pd3dDevice->Release();

    if (m_pD3D != NULL)
        m_pD3D->Release();
}

HRESULT kRender::drawRectangle(float x,float y,int width,int height)
{
    CUSTOMVERTEX vertices[] = {
        // 上边线
        { x - width / 2, y - height / 2, 0.0f, 1.0f, D3DCOLOR_XRGB(255, 0, 0), },
        { x + width / 2, y - height / 2, 0.0f, 1.0f, D3DCOLOR_XRGB(255, 0, 0), },
        // 右边线
        { x + width / 2, y - height / 2, 0.0f, 1.0f, D3DCOLOR_XRGB(255, 0, 0), },
        { x + width / 2, y + height / 2, 0.0f, 1.0f, D3DCOLOR_XRGB(255, 0, 0), },
        // 下边线
        { x + width / 2, y + height / 2, 0.0f, 1.0f, D3DCOLOR_XRGB(255, 0, 0), },
        { x - width / 2, y + height / 2, 0.0f, 1.0f, D3DCOLOR_XRGB(255, 0, 0), },
        // 左边线
        { x - width / 2, y + height / 2, 0.0f, 1.0f, D3DCOLOR_XRGB(255, 0, 0), },
        { x - width / 2, y - height / 2, 0.0f, 1.0f, D3DCOLOR_XRGB(255, 0, 0), },
    };
    

    VOID* pVertices;
    if (FAILED(m_pVB->Lock(0, sizeof(vertices), (void**)&pVertices, 0)))
        return E_FAIL;
    memcpy(pVertices, vertices, sizeof(vertices));
    m_pVB->Unlock();

    if (SUCCEEDED(m_pd3dDevice->BeginScene())) {
        m_pd3dDevice->SetStreamSource(0, m_pVB, 0, sizeof(CUSTOMVERTEX));
        m_pd3dDevice->SetFVF(D3DFVF_CUSTOMVERTEX);
        m_pd3dDevice->DrawPrimitive(D3DPT_LINESTRIP, 0, 7);
        m_pd3dDevice->EndScene();
    }
    return S_OK;

}

HRESULT kRender::drawLine(float x1,float y1,float x2,float y2)
{
    CUSTOMVERTEX vertices[] = {
        { x1, y1, 0.0f, 1.0f, D3DCOLOR_XRGB(0, 0, 255), },
        { x2, y2, 0.0f, 1.0f, D3DCOLOR_XRGB(0, 255, 0), },
    };   
    VOID* pVertices;
    if (FAILED(m_pVB->Lock(0, sizeof(vertices), (void**)&pVertices, 0)))
        return E_FAIL;
    memcpy(pVertices, vertices, sizeof(vertices));
    m_pVB->Unlock();

    if (SUCCEEDED(m_pd3dDevice->BeginScene())) {
        m_pd3dDevice->SetStreamSource(0, m_pVB, 0, sizeof(CUSTOMVERTEX));
        m_pd3dDevice->SetFVF(D3DFVF_CUSTOMVERTEX);
        m_pd3dDevice->DrawPrimitive(D3DPT_LINELIST, 0, 1);
        m_pd3dDevice->EndScene();
    }
    return S_OK;
}

void kRender::drawText(const std::string& text, int x, int y, D3DCOLOR color)
{
    
}

void kRender::beginRender()
{
    m_pd3dDevice->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_ARGB(0, 0, 0, 0), 1.0f, 0);
}
void kRender::endRender()
{
    m_pd3dDevice->Present(NULL, NULL, NULL, NULL);
}

