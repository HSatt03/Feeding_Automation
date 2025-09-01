#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include "meal.hpp"
#include "diningHall.hpp"
#include "reservation.hpp"

using namespace std;

Reservation::Reservation(DiningHall* d, Meal* m, int r,
            RStatus s, time_t t_c, time_t t_r)
{
    setReservation_id(r);
    setDhall(d);
    setMeal(m);
    setStatus(s);
    setCreatedTime(t_c);
    setRemovedTime(t_r);
}

void Reservation::setReservation_id(int r)
{
    if(r >= 0)
    {
        _reservation_id = r;
    }
    else
    {
        throw invalid_argument("Incorrect value for reservation_id");
    }
}

void Reservation::setDhall(DiningHall *d)
{
    d->setHallId(d->getHallId());
    d->setName(d->getName());
    d->setAddress(d->getAddress());
    d->setCapacity(d->getCapacity());
}

void Reservation::setMeal(Meal *m)
{
    m->setMeal_id(m->getMeal_id());
    m->setName(m->getName());
    m->setPrice(m->getPrice());
    m->setMeal_type(m->getMeal_type());
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
        default:
            os << "Unkown!!!";
    }
    return os;
}

void Reservation::print()const
{
    cout << "reservation id : " << _reservation_id;
    cout << endl;
    _dHall->print();
    cout << endl;
    _meal->print();
    cout << "\nstatus : " << _status;
    cout << "\ncreaded at : ";
    tm* localTime = localtime(&_created_at);
    char buffer1[80];
    char buffer2[80];
    strftime(buffer1, sizeof(buffer1), "%H:%M" , localTime);
    strftime(buffer2, sizeof(buffer2), "%Y-%m-%d" , localTime);
    cout << buffer1 <<" " << buffer2 << endl;
}

bool Reservation::cancel()
{
    if(_status == RStatus::CANCELLED)
    return true;
    else
    return false;
}
