#include "kWindow.h"


LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
    switch (message) {
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    }
    return DefWindowProc(hWnd, message, wParam, lParam);
}

kWindow::kWindow(const char* wndName)
{
    HINSTANCE hInstance = GetModuleHandle(NULL);
    HWND targetWnd = FindWindow(NULL, wndName);
    if (!targetWnd)
    {
        std::cout << "FindWindow failed!\n";
        system("pause");
    }
    GetWindowRect(targetWnd, &m_rect);
    WNDCLASSEX wc;
    ZeroMemory(&wc, sizeof(WNDCLASSEX));
    wc.cbSize = sizeof(WNDCLASSEX);
    wc.style = CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.lpszClassName = "kWindowClass";

    RegisterClassEx(&wc);

    HWND hWnd = CreateWindowEx(
        WS_EX_LAYERED | WS_EX_TRANSPARENT | WS_EX_TOPMOST, // 设置窗口扩展样式为分层和透明
        "kWindowClass", "KvancyCs2Cheat", WS_POPUP | WS_VISIBLE,
        m_rect.left, m_rect.top, m_rect.right - m_rect.left, m_rect.bottom - m_rect.top,
        NULL, NULL, hInstance, NULL
    );
    //DwmExtendFrameIntoClientArea创建无边框的窗口
    MARGINS margins = { m_rect.left,m_rect.right,m_rect.top,m_rect.bottom };
    DwmExtendFrameIntoClientArea(hWnd, &margins);
    //设置窗口过滤黑色,使黑色变得透明
    SetLayeredWindowAttributes(hWnd, RGB(0, 0, 0), 0, LWA_COLORKEY);

    this->hWnd = hWnd;
    ShowWindow(hWnd, SW_SHOWDEFAULT);
    UpdateWindow(hWnd);
}

kWindow::~kWindow()
{
}
void kWindow::doCheat(kRender* render, kGame* game)
{
    game->refreshData();
    game->showAllPlayer();
    render->beginRender();
    for (size_t i = 0; i < 10; i++)
    {
        if (game->m_playPawn[i].getTeamNum() == game->m_playPawn[0].getTeamNum())
            continue;
        if (!game->m_playPawn[i].isAlive())
            continue;
        point2D pos = game->world2screen(game->getPlayerPawnPos(i), game->getMatrix());
        point2D posHead = game->world2screen(game->m_playPawn[i].getPosHead(), game->getMatrix());
        render->drawRectangle(pos.x, (pos.y + posHead.y) / 2, 60, posHead.y - pos.y);
    }
    render->endRender();
}

void kWindow::msgLoop(kGame* game)
{
    kRender* render = new kRender(hWnd);
    MSG msg;
    ZeroMemory(&msg, sizeof(msg));
    while (msg.message != WM_QUIT) {
        if (PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE)) {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        else {
            doCheat(render,game);
        }
    }
}



RECT kWindow::getRect()
{
    return m_rect;
}

