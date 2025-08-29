#include <iostream>
#include <conio.h>
#include <ctime>
#include <cstdlib>
#include <vector>
#include "shoppingCart.hpp"
#include "reservation.hpp"
#include "transaction.hpp"
#include "student.hpp"
#include "sessionManager.hpp"
#include "utils.hpp"

using namespace std;

time_t specialTime = 123456;
ShoppingCart::ShoppingCart()
{
    
}
Transaction ShoppingCart::confirm()
{
    float totalAmount = 0;
    time_t now = time(0);

    // تغییر وضعیت رزروها به SUCCESSFULL و محاسبه مجموع قیمت‌ها
    for (auto& reservation : _reservations)
    {
        reservation.setStatus(RStatus::SUCCESSFULL);
        totalAmount += reservation.getMeal().getPrice();
    }

    // تولید یک transactionID تصادفی (مثلا عددی بین 1 تا 10000)
    static int transactionCounter = 1;
    int transactionID = transactionCounter++;

    // تولید یک trackingCode 5 رقمی به صورت رشته
    string trackingCode = to_string(rand() % 90000 + 10000);

    // ایجاد Transaction با مقدارهای مناسب
    Transaction t(transactionID, trackingCode, totalAmount,
                  TransactionType::PAYMENT,
                  TransactionStatus::COMPLETED,
                  now);

    Student* student = StudentSession::SessionManager::instance().currentStudent();
    if (student)
    {
        student->addTransaction(t);  // دخیره کردن در کلاس student
    }             

    // پاک کردن سبد خرید بعد از تایید تراکنش
    clear();

    return t;
}

void ShoppingCart::addReservation(Reservation reservation)
{
    reservation.setStatus(RStatus::NOT_PAID);
    reservation.setCreatedTime(time(0));
    _reservations.push_back(reservation);
}
void ShoppingCart::removeReservation(int ID)
{
    for(auto add = _reservations.begin(); add != _reservations.end(); add++)
    {
        if((*add).getReservation_id() == ID)
        {
            _reservations.erase(add);
            (*add).setRemovedTime(time(0));
            break;
        }
        else 
        {
            (*add).setRemovedTime(specialTime);
        }
    }
}
// void gotoxy(int x, int y)
// {
//     COORD coord;
//     coord.X = x;
//     coord.Y = y;
//     SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
// }
// void drawBox(int x, int y, int width, int height)
// {
//     // گوشه‌ها
//     gotoxy(x, y); cout << "+";
//     gotoxy(x + width, y); cout << "+";
//     gotoxy(x, y + height); cout << "+";
//     gotoxy(x + width, y + height); cout << "+";

//     // خطوط افقی
//     for (int i = 1; i < width; ++i) {
//         gotoxy(x + i, y); cout << "-";
//         gotoxy(x + i, y + height); cout << "-";
//     }

//     // خطوط عمودی
//     for (int i = 1; i < height; ++i) {
//         gotoxy(x, y + i); cout << "|";
//         gotoxy(x + width, y + i); cout << "|";
//     }
// }
void ShoppingCart::viewShoppingCartItems()
{
    for(auto add = _reservations.begin(); add != _reservations.end(); add++)
    {
        add->print();
        time_t created = add->getCreatedTime();
        tm* localTime = localtime(&created);
        char buffer1[80];
        strftime(buffer1, sizeof(buffer1), "%H:%M:%S" , localTime);
        cout << "The reservation was added to the shopping cart at " << buffer1 << endl;
        if(add->getRemovedTime() == specialTime)
        {
            time_t removed = add->getCreatedTime();            
            tm* localTime = localtime(&removed);
            char buffer2[80];
            strftime(buffer2, sizeof(buffer2), "%H:%M:%S" , localTime);
            cout << "The reservation was deleted from the shopping cart at " << buffer2 << endl;
        }
    }
}
void ShoppingCart::clear()
{
    _reservations.clear();
}
vector<Reservation> ShoppingCart::getReservations()const
{
    return _reservations;
}