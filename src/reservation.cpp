#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include "meal.hpp"
#include "diningHall.hpp"
#include "reservation.hpp"

using namespace std;
void gotoxy(int x, int y);

Reservation::Reservation(DiningHall* d, Meal* m, int r,
            RStatus s, time_t t_c, time_t t_r)
{
    _reservation_id = ++_next_id; // هر بار که شی ساخته میشه، آی‌دی یکتا می‌گیره
    setDhall(d);
    setMeal(m);
    setStatus(s);
    setCreatedTime(t_c);
    setRemovedTime(t_r);
}

/*void Reservation::setReservation_id(int r)
{
    if(r >= 0)
    {
        _reservation_id = r;
    }
    else
    {
        throw invalid_argument("Incorrect value for reservation_id");
    }
}*/

void Reservation::setDhall(DiningHall *d)
{
    _dHall = d;
}

void Reservation::setMeal(Meal *m)
{
    _meal = m;
}

void Reservation::setStatus(RStatus s)
{
    if(s == RStatus::FAILED || s == RStatus::CANCELLED || s == RStatus::SUCCESSFULL || s == RStatus::NOT_PAID || s == RStatus::PENDING) 
    {
        _status = s;
    }
    else
    {
        throw invalid_argument("Incorrect value for reservation_status!!!");
    }
}

void Reservation::setCreatedTime(time_t t)
{
    if(t > 0)
    {
        _created_at = t;
    }
    else
    {
        throw invalid_argument("Incorrect value for time!!!");
    }
}

void Reservation::setRemovedTime(time_t t)
{
    if(t >= 0)
    {
        _removed_from = t;
    }
    else
    {
        throw invalid_argument("Incorrect value for time!!!");
    }
}  

bool Reservation::operator==(Reservation ob)
{
    return(_reservation_id == ob._reservation_id
           && _dHall == ob._dHall
           && _meal == ob._meal
           && _status == ob._status
           && _created_at == ob._created_at);
}
ostream& operator<<(ostream& os, const RStatus& num)
{
    switch(num)
    {
        case RStatus::FAILED:
            os << "FAILED";
            break;
        case RStatus::CANCELLED:
            os << "CANCELLED";
            break;
        case RStatus::SUCCESSFULL:
            os << "SUCCESSFULL";
            break;
        case RStatus::PENDING:
            os << "PENDING";
            break;
        case RStatus::NOT_PAID:
            os << "NOT_PAID";
            break;
        default:
            os << "Unkown!!!";
    }
    return os;
}

void Reservation::print(int startX, int startY) const
{
    int i = startX;
    int j = startY;

    gotoxy(i, j++);
    cout << "Reservation id: " << _reservation_id;

    // چاپ DiningHall با موقعیت مشخص
    _dHall->print_panel(i, j);

    // چاپ Meal با موقعیت مشخص، کمی فاصله بعد از DiningHall
    _meal->print_panel(i + 22, j);
}


bool Reservation::cancel()
{
    if(_status == RStatus::CANCELLED)
    return true;
    else
    return false;
}
int Reservation::_next_id = 0;
