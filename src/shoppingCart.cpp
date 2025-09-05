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
    Reservation r = reservation;
    r.setStatus(RStatus::NOT_PAID);
    r.setCreatedTime(time(0));
    _reservations.push_back(r);
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

void ShoppingCart::viewShoppingCartItems()
{
    int i = 2;          // ستون شروع
    int j = 3;         // سطر شروع
    int rowSpacing = 10; // فاصله بین رزروها

    for(auto add = _reservations.begin(); add != _reservations.end(); add++)
    {
        add->print(i, j);
        time_t created = add->getCreatedTime();
        tm* localTime = localtime(&created);
        char buffer1[80];
        strftime(buffer1, sizeof(buffer1), "%H:%M:%S" , localTime);
        gotoxy(i, j+8);
        cout << "The reservation was added to the shopping cart at " << buffer1 << endl;
        if(add->getRemovedTime() == specialTime)
        {
            time_t removed = add->getCreatedTime();            
            tm* localTime = localtime(&removed);
            char buffer2[80];
            strftime(buffer2, sizeof(buffer2), "%H:%M:%S" , localTime);
            gotoxy(i, j+9);
            cout << "The reservation was deleted from the shopping cart at " << buffer2 << endl;
        }
        j += rowSpacing; // فاصله به رزرو بعدی
    }
}
// void ShoppingCart::viewShoppingCartItems()
// {
//     int i = 2;          // ستون شروع
//     int j = 3;         // سطر شروع
//     int rowSpacing = 10; // فاصله بین رزروها

//     for(auto& add : _reservations)
//     {
//         add.print(i, j);  // print حالا باید پارامتر بگیرد

//         time_t created = add.getCreatedTime();
//         tm* localTime = localtime(&created);
//         char buffer1[80];
//         strftime(buffer1, sizeof(buffer1), "%H:%M:%S" , localTime);

//         gotoxy(i, j+5); // چاپ زمان اضافه شدن کمی پایین‌تر
//         cout << "Added to shopping cart at " << buffer1 << endl;

//         if(add.getRemovedTime() != specialTime)
//         {
//             time_t removed = add.getRemovedTime();            
//             tm* localTime = localtime(&removed);
//             char buffer2[80];
//             strftime(buffer2, sizeof(buffer2), "%H:%M:%S" , localTime);
//             gotoxy(i, j+6);
//             cout << "Deleted from shopping cart at " << buffer2 << endl;
//         }

//         j += rowSpacing; // فاصله به رزرو بعدی
//     }
// }

void ShoppingCart::clear()
{
    _reservations.clear();
}
vector<Reservation> ShoppingCart::getReservations()const
{
    return _reservations;
}