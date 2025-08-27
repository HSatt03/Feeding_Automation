#include <iostream>
#include <cstdlib>
#include "sessionManager2.hpp"
#include "adminPanel.hpp"
#include "utils.hpp"

using namespace std;

void gotoxy(int x, int y);

void drawBox(int x, int y, int width, int height);

void clearScreen() 
{
    system("cls"); // ویندوز
}

int main()
{
    if(!Admin::isThereAnyAdmin())
    {
        string Name, LastName, Password, Phone;
        drawBox(1, 1, 40, 10);
        gotoxy(12, 3);
        cout << "*Log in*";
        gotoxy(20, 20);
        gotoxy(4, 5);
        cout << "Name: ";
        cin >> Name;
        gotoxy(4, 6);
        cout << "Last Name: ";
        cin >> LastName;
        gotoxy(4, 7);
        cout << "Phone: ";
        cin >> Phone;
        gotoxy(4, 8);
        cout << "Choose a password:";
        cin >> Password;
        gotoxy(20, 20);
        system("cls");
        AdminSession::SessionManager admin_session;
        admin_session.login(Phone, Password);
        AdminPanel panel;
        panel.showMenu();
        // system("cls");
    }

    return 0;
}