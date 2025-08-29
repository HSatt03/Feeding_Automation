#include <iostream>
#include <cstdlib>
#include <conio.h>
#include "sessionManager2.hpp"
#include "adminPanel.hpp"
#include "utils.hpp"
#include "waitForKey.hpp"
#include "consoleMessageBox.hpp"

using namespace std;

void gotoxy(int x, int y);

void drawBox(int x, int y, int width, int height);

void clearScreen() 
{
    system("cls"); // ویندوز
}

int main()
{
    string password, phoneOrNumber;
    auto& msgBox = ConsoleMessageBox::instance();
    msgBox.setPosition(7, 20, 100, 5);
    if(!Admin::isThereAnyAdmin())
    {
        drawBox(1, 1, 50, 10);
        gotoxy(22, 3);
        cout << "*Log in*";
        gotoxy(4, 5);
        cout << "Enter your phone: ";
        cin >> phoneOrNumber;
        bool validPassword = false;
        while (!validPassword)
        {
            try 
            {
                gotoxy(4, 7);
                cout << "Choose a password: ";
                gotoxy(4, 8);
                cout << "The maximum number of characters must be 10."; 
                gotoxy(23, 7);
                cin >> password;

                if (password.length() > 10)
                {
                    throw runtime_error("Password length must be at most 10 characters!");
                }
                validPassword = true; // اگه مشکل نبود، حلقه تموم می‌شه
            }
            catch (const runtime_error& e)
            {
                gotoxy(4, 9);
                msgBox.addMessage("Error: " + string(e.what()), MsgColor::RED);
                msgBox.showMessages();
                system("pause");
                msgBox.clear();
                // cout << "Error: " << e.what() << " Try again." << endl;
            }
        }
        gotoxy(20, 20);
        system("cls");
        AdminSession::SessionManager admin_session;
        admin_session.login(phoneOrNumber, password);
        while(1)
        {
            AdminPanel panel;
            system("cls");
            panel.showMenu();
            waitForKey();
        }
    }
    else
    {
        char option;
        drawBox(10, 3, 35, 10);
        gotoxy(23, 5);
        cout << "*Log in*";
        gotoxy(13, 7);
        cout << "1_ Admin";
        gotoxy(13, 9);
        cout << "2_ Student";
        gotoxy(13, 11);
        cout << "Choose your option: ";
        option = getch();
        gotoxy(20, 20);
        switch(option)
        {
            case '1':

            case '2':

            default:
                throw invalid_argument("Admin session file not found.");
        } 
    }
    return 0;
}