#include <iostream>
#include <windows.h>
#include "utils.hpp"

using namespace std;

void gotoxy(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void drawBox(int x, int y, int width, int height) {
    gotoxy(x, y); cout << "+";
    gotoxy(x + width, y); cout << "+";
    gotoxy(x, y + height); cout << "+";
    gotoxy(x + width, y + height); cout << "+";

    for (int i = 1; i < width; ++i) {
        gotoxy(x + i, y); cout << "-";
        gotoxy(x + i, y + height); cout << "-";
    }
    for (int i = 1; i < height; ++i) {
        gotoxy(x, y + i); cout << "|";
        gotoxy(x + width, y + i); cout << "|";
    }
}
