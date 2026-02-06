/*
 * Troy Gomme
 * Started on 29/01/2026
 * Version 0.0.0
 */

#ifndef WINDOZER_LIBRARY_H
#define WINDOZER_LIBRARY_H

#pragma once
#include <cstdint>
#include <windows.h>
#include <string>
#include <vector>

using namespace std;

class WinDozerApp {
public:
    WinDozerApp(string title, int width, int height);
    virtual ~WinDozerApp() = default;

    bool Run(HINSTANCE hInstance, int nCmdShow);

    HPEN hpen;
    HBRUSH hbrush;
    HPEN lhpen;
    HBRUSH lhbrush;
    void SETCOLOUR(HDC hdc, vector<uint8_t> outline, int width, vector<uint8_t> fill);
    void RESETCOLOUR(HDC hdc);
    void SETRESETCOLOUR(HDC hdc);

protected:
    virtual void OnUpdate() {}
    virtual void OnDraw(HDC hdc) {}
    virtual void OnDestroy() {PostQuitMessage(0); }

    HWND m_hwnd;
    const int m_width, m_height;

private:
    static LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

    string m_title;
};

#endif // WINDOZER_LIBRARY_H