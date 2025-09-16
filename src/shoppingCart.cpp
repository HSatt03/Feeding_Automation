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
#include "logsystem.hpp"

using namespace std;

void gotoxy(int x, int y);

time_t specialTime = 123456;

ShoppingCart::ShoppingCart()
{
    
}

Transaction ShoppingCart::confirm()
{
    float totalAmount = 0;
    time_t now = time(0);
    Student* student = StudentSession::SessionManager::instance().currentStudent();
    string studentID = student->getStudentId();
    // تغییر وضعیت رزروها به SUCCESSFULL و محاسبه مجموع قیمت‌ها
    for (auto& reservation : _reservations)
    {
        //reservation.setStatus(RStatus::SUCCESSFULL);
        totalAmount += reservation.getMeal().getPrice();
    }
    if (!student || student->getBalance() < totalAmount)
    {
        studentLogger.addLog("Student " + studentID + " failed to confirm shopping cart. " , "ERROR");
        gotoxy(2, 15);
        cout << "Insufficient balance. Please recharge your account." << endl;

        // failed transaction
        static int transactionCounter = 1;
        int transactionID = transactionCounter++;
        string trackingCode = to_string(rand() % 90000 + 10000);

        Transaction t(transactionID, trackingCode, totalAmount,
                    TransactionType::PAYMENT,
                    TransactionStatus::FIALED,
                    now);
        if (student)
        { 
           student->addTransaction(t);
        }
        return t;
    }
    student->setBalance(student->getBalance() - totalAmount);
    for (auto& reservation : _reservations)
    {
        reservation.setStatus(RStatus::SUCCESSFULL);
        Reservation* confirmed = new Reservation(
            reservation.getDhallPtr(),
            reservation.getMealPtr(),
            reservation.getReservation_id(),
            reservation.getStatus(),
            reservation.getCreatedTime(),
            reservation.getRemovedTime()
        );
        student->addReservation(confirmed);
        studentLogger.addLog("Student " + studentID + " confirmed shopping cart: " , "INFO");
        gotoxy(2, 15);
        cout << "Shopping cart confirmed successfully.\n";
   } 
    
    static int transactionCounter = 0;
    int transactionID = ++transactionCounter;
    // تولید یک trackingCode 5 رقمی به صورت رشته
    string trackingCode = to_string(rand() % 90000 + 10000);
    // ایجاد Transaction با مقدارهای مناسب
    Transaction t(transactionID, trackingCode, totalAmount,
                  TransactionType::PAYMENT,
                  TransactionStatus::COMPLETED,
                  now);
    if (student)
    { 
        student->addTransaction(t);
    }  // دخیره کردن در کلاس student
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
bool ShoppingCart::removeReservation(int ID)
{
    for(auto add = _reservations.begin(); add != _reservations.end(); add++)
    {
        if((*add).getReservation_id() == ID)
        {
            _reservations.erase(add);
            (*add).setRemovedTime(time(0));
            return true;
        }
    }
    return false;
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
        j += rowSpacing; // فاصله به رزرو بعدی
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