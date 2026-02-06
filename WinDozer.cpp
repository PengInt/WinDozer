#include "WinDozer.h"

#include <windows.h>
#include <iostream>

using namespace std;

WinDozerApp::WinDozerApp(string title, int width, int height) : m_title(title), m_width(width), m_height(height), m_hwnd(nullptr) {}

bool WinDozerApp::Run(HINSTANCE hInstance, int nCmdShow) {
    const string CLASSNAME = "WinDozer Window";

    WNDCLASS wc = {};
    wc.lpfnWndProc = WinDozerApp::WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = CLASSNAME.c_str();
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);

    RegisterClass(&wc);

    m_hwnd = CreateWindowEx( 0,
                                CLASSNAME.c_str(),
                                m_title.c_str(),
                                WS_OVERLAPPEDWINDOW,
                                CW_USEDEFAULT,
                                CW_USEDEFAULT,
                                m_width,
                                m_height,
                                NULL,
                                NULL,
                                hInstance,
                                this                    );

    if (!m_hwnd) {
        return false;
    }

    ShowWindow(m_hwnd, nCmdShow);

    MSG msg = {};
    while (msg.message != WM_QUIT) {
        if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        } else {
            OnUpdate();
        }
    }

    return true;
}

void WinDozerApp::SETCOLOUR(HDC hdc, vector<uint8_t> outline, int width, vector<uint8_t> fill) {
    SelectObject(hdc, GetStockObject(BLACK_PEN));
    SelectObject(hdc, GetStockObject(NULL_BRUSH));

    DeleteObject(hpen);
    DeleteObject(hbrush);

    hpen = CreatePen(PS_SOLID, width, RGB(outline[0], outline[1], outline[2]));
    hbrush = CreateSolidBrush(RGB(fill[0], fill[1], fill[2]));

    SelectObject(hdc, hpen);
    SelectObject(hdc, hbrush);
}

void WinDozerApp::RESETCOLOUR(HDC hdc) {
    SelectObject(hdc, lhpen);
    SelectObject(hdc, lhbrush);
    DeleteObject(hpen);
    DeleteObject(hbrush);
}

void WinDozerApp::SETRESETCOLOUR(HDC hdc) {
    HPEN hbpen = CreatePen(PS_SOLID, 0, RGB(0, 0, 0));
    HBRUSH hbbrush = CreateSolidBrush(RGB(0, 0, 0));

    lhpen = (HPEN) SelectObject(hdc, hbpen);
    lhbrush = (HBRUSH) SelectObject(hdc, hbbrush);

    DeleteObject(hbpen);
    DeleteObject(hbbrush);
}




LRESULT CALLBACK WinDozerApp::WindowProc(HWND hwnd,
                            UINT uMsg,
                            WPARAM wParam,
                            LPARAM lParam   ) {
    WinDozerApp* pApp = nullptr;

    if (uMsg == WM_NCCREATE) {
        CREATESTRUCT* pCreate = (CREATESTRUCT*) lParam;
        pApp = (WinDozerApp*) pCreate -> lpCreateParams;
        SetWindowLongPtr(hwnd, GWLP_USERDATA, (LONG_PTR) pApp);
    } else {
        pApp = (WinDozerApp*) GetWindowLongPtr(hwnd, GWLP_USERDATA);
    }

    if (pApp) {
        switch (uMsg) {
            case WM_DESTROY:
                pApp -> OnDestroy();
                return 0;
            case WM_PAINT: {
                PAINTSTRUCT ps;
                HDC hdc = BeginPaint(hwnd, &ps);

                //FillRect(hdc, &ps.rcPaint, (HBRUSH) (COLOR_WINDOW + 1));

                pApp -> OnDraw(hdc);

                EndPaint(hwnd, &ps);
                return 0;
            }
            case WM_ERASEBKGND:
                return 1;
        }
    }

    return DefWindowProc(hwnd, uMsg, wParam, lParam);
};
