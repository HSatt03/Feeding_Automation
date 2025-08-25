#include <iostream>
#include <windows.h>
#include "sessionManager2.hpp"
#include "adminPanel.hpp"

using namespace std;

void gotoxy(int x, int y)
{
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
} 

void drawBox(int x, int y, int width, int height)
{
    // گوشه‌ها
    gotoxy(x, y); cout << "+";
    gotoxy(x + width, y); cout << "+";
    gotoxy(x, y + height); cout << "+";
    gotoxy(x + width, y + height); cout << "+";

    // خطوط افقی
    for (int i = 1; i < width; ++i) {
        gotoxy(x + i, y); cout << "-";
        gotoxy(x + i, y + height); cout << "-";
    }

    // خطوط عمودی
    for (int i = 1; i < height; ++i) {
        gotoxy(x, y + i); cout << "|";
        gotoxy(x + width, y + i); cout << "|";
    }
}

int main()
{
    string password, studentNumber;
    drawBox(1, 1, 30, 10);
    gotoxy(12, 3);
    cout << "*Log in*";
    gotoxy(20, 20);
    gotoxy(4, 5);
    cout << "Password: ";
    cin >> password;
    gotoxy(4, 7);
    cout << "StudentID: ";
    cin >> studentNumber;
    gotoxy(20, 20);
    if(!Admin::isThereAnyAdmin())
    {
        AdminSession::SessionManager admin_session;
        admin_session.login(studentNumber, password);
        AdminPanel panel;
        panel.showMenu();
    }
    // else
    // {

    // }


    return 0;
}