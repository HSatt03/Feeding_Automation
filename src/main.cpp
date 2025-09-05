#include <iostream>
#include <cstdlib>
#include <conio.h>
#include "sessionManager2.hpp"
#include "sessionManager.hpp"
#include "adminPanel.hpp"
#include "panel.hpp"
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
    string admin_password, admin_phone, student_number, student_password;
    auto& msgBox = ConsoleMessageBox::instance();
    msgBox.setPosition(7, 20, 100, 5);
    if(!Admin::isThereAnyAdmin())
    {
        drawBox(1, 1, 50, 10);
        gotoxy(18, 3);
        cout << "*First Log in*";
        gotoxy(4, 5);
        cout << "Enter your phone: ";
        cin >> admin_phone;
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
                cin >> admin_password;

                if (admin_password.length() > 10)
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
        auto& admin_session = AdminSession::SessionManager::instance();
        admin_session.login(admin_phone, admin_password);
        while(1)
        {
            AdminPanel panel;
            system("cls");
            if (!panel.showMenu()) // ❌ اگر false برگردونه، یعنی Exit زده
            {
                break; // از حلقه منوی ادمین بیا بیرون → برگرد به منوی اصلی
            }            
            // waitForKey();
        }
    }
    else
    {
        char option;
        while(1)
        {
            drawBox(10, 3, 35, 13);
            gotoxy(23, 5);
            cout << "*Log in*";
            gotoxy(13, 7);
            cout << "1_ Admin";
            gotoxy(13, 9);
            cout << "2_ Student";
            gotoxy(13, 11);
            cout << "3_ Exit";
            gotoxy(13, 13);
            cout << "Choose your option: ";
            option = getch();
            gotoxy(20, 20);
            system("cls");
            switch(option)
            {
                case '1':
                {
                    drawBox(1, 1, 50, 10);
                    gotoxy(19, 3);
                    cout << "*Admin Log in*";
                    gotoxy(4, 5);
                    cout << "Phone: ";
                    cin >> admin_phone;
                    gotoxy(4, 7);
                    cout << "Password: ";
                    cin >> admin_password;
                    gotoxy(20, 20);
                    system("cls");
                    auto& admin_session = AdminSession::SessionManager::instance();
                    admin_session.login(admin_phone, admin_password);
                    while(1)
                    {
                        AdminPanel panel;
                        system("cls");
                        // panel.showMenu();
                        if (!panel.showMenu()) // ❌ اگر false برگردونه، یعنی Exit زده
                        {
                            break; // از حلقه منوی ادمین بیا بیرون → برگرد به منوی اصلی
                        }
                        // waitForKey();
                    }
                    break;
                }
                case '2':
                {
                    drawBox(1, 1, 50, 10);
                    gotoxy(19, 3);
                    cout << "*Student Log in*";
                    gotoxy(4, 5);
                    cout << "Student Number: ";
                    cin >> student_number;
                    gotoxy(4, 7);
                    cout << "Password: ";
                    cin >> student_password;
                    gotoxy(20, 20);
                    system("cls");
                    auto& student_session = StudentSession::SessionManager::instance();
                    student_session.login(student_number, student_password);
                    while(1)
                    {
                        Panel panel;
                        system("cls");
                        if(!panel.showMenu(&student_session))
                        {
                            break;
                        }
                        // waitForKey();
                    }
                    break;
                }
                case '3':
                    system("cls");
                    cout << "BYE BYE !!! ";
                    exit(1);
                default:
                    throw invalid_argument("Admin session file not found.");
            } 
        }
    }
    return 0;
}