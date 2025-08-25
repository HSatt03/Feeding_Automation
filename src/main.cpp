#include <iostream>
#include <windows.h>
#include "sessionManager2.hpp"
#include "adminPanel.hpp"

using namespace std;

void gotoxy(int x, int y);

void drawBox(int x, int y, int width, int height);

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