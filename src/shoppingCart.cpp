#include <iostream>
#include <windows.h>
#include <conio.h>
#include <ctime>
#include <vector>
#include "../include/shoppingCart.hpp"
#include "../include/reservation.hpp"
#include "../include/transaction.hpp"
using namespace std;
time_t Stime, Ftime;
Transaction ShoppingCart::confirm()
{

}
void ShoppingCart::addReservation(Reservation reservation)
{
    reservation.setStatus(NOT_PAID);
    Stime = time(0);
    _reservations.push_back(reservation);
}
void ShoppingCart::removeReservation(int ID)
{
    for(auto add = _reservations.begin(); add != _reservations.end(); add++)
    {
        if((*add).getReservation_id() == ID)
        {
            _reservations.erase(add);
            Ftime = time(0);
            break;
        }
    }
}
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
void ShoppingCart::viewShoppingCartItems()
{
    drawBox(0, 0, 40, 15);   
    gotoxy(20, 17);
    tm* localTime = localtime(&Stime);
    char buffer1[80];
    strftime(buffer1, sizeof(buffer1), "%H:%M:%S" , localTime);
    gotoxy(2,2);
    cout << "The reservation was added to the shopping cart at " << buffer1 << endl;
    tm* localTime = localtime(&Ftime);
    char buffer2[80];
    strftime(buffer2, sizeof(buffer2), "%H:%M:%S" , localTime);
    gotoxy(2,4);
    cout << "The reservation was deleted from the shopping cart at " << buffer2 << endl;
}
