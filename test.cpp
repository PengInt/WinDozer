#include "WinDozer.h"
#include <iostream>
#include <vector>

using namespace std;

struct Vector2 {
    float X, Y;
};

class GameObject {
public:
    Vector2 Position;
private:
    vector<Vector2> VERTICES;
    vector<vector<int>> FACES;

public:
    GameObject(Vector2 POS, vector<Vector2> V, vector<vector<int>> F, vector<vector<int>> C) {
        Position = POS;
        VERTICES = V;
        FACES = {};
        for (int i = 0; i < F.size(); i++) {
            FACES.push_back({F[i][0], F[i][1], F[i][2], C[i][0], C[i][1], C[i][2]});
        }
    }
};


GameObject CustomObject = GameObject(Vector2(0, 0), {Vector2(1, 1), Vector2(-1, 0.5), Vector2(0,5. -1)}, {{0, 1, 2}}, {{255, 0, 0}});


class Game : public WinDozerApp {
public:
    using WinDozerApp::WinDozerApp;
    float RectangleX = 15;
    float RectangleY = 29;
    float RectangleVX = 1;
    float RectangleVY = 2;
    float RectangleSX = 8;
    float RectangleSY = 3;

protected:
    void OnDraw(HDC hdc) override {
        SETRESETCOLOUR(hdc);

        SETCOLOUR(hdc, {255, 255, 255}, 0, {255, 255, 255});

        Rectangle(hdc, 0, 0, m_width, m_height);

        SETCOLOUR(hdc, {0, 0, 255}, 5, {0, 0, 255});

        Rectangle(hdc, RectangleX, RectangleY, RectangleX + RectangleSX, RectangleY + RectangleSY);

        RESETCOLOUR(hdc);
    }
    void OnUpdate() override {
        RectangleX += RectangleVX/180;
        RectangleY += RectangleVY/180;
        InvalidateRect(m_hwnd, NULL, FALSE);
    }
};


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrev, LPSTR pCmd, int nCmdShow) {
    Game game("WinDozer Example Application", 500, 500);
    game.Run(hInstance, nCmdShow);

    return 0;
}