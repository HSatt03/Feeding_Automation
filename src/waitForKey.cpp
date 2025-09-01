#include <iostream>
#include <conio.h>
// #include <windows.h>
// #include <limits>
#include "waitForKey.hpp"
#include "utils.hpp"

using namespace std;

void waitForKey()
{
    // drawBox(7, 20, 100, 5);
    // gotoxy(22, 22);
    // SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN | FOREGROUND_INTENSITY); // رنگ سبز پررنگ
    // cout << ">>> PRESS ENTER TO RETURN TO MENU <<<";
    // SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE); // بازگشت به رنگ معمول
    // cin.ignore(numeric_limits<streamsize>::max(), '\n');
    // cin.get();

    drawBox(7, 20, 100, 5);
    gotoxy(22, 22);
    cout << "Press Enter to return to menu...";
    _getch();  // صبر می‌کنه تا کاربر یه کلید بزنه
    cout << endl;
}