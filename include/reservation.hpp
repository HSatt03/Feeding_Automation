#ifndef RESERVATION_H
#define RESERVATION_H
#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include "meal.hpp"
#include "diningHall.hpp"
using namespace std;

enum class RStatus
{
    FAILED,
    CANCELLED,
    SUCCESSFULL,
    NOT_PAID
};

class Reservation
{
public:
    Reservation(DiningHall*, Meal*, int = 0, RStatus = RStatus::FAILED, time_t = time(0), time_t = time(0)); 

    void setReservation_id(int);
    void setDhall(DiningHall*);
    void setMeal(Meal*);
    void setStatus(RStatus);
    void setCreatedTime(time_t);
    void setRemovedTime(time_t);

    int getReservation_id()const
    {
        return _reservation_id;
    }
    DiningHall getDhall()const
    {
        return *_dHall;
    }
    Meal getMeal()const
    {
        return *_meal;
    }
    RStatus getStatus()const
    {
        return _status;
    }
    time_t getCreatedTime()const
    {
        return _created_at;
    }
    time_t getRemovedTime()const
    {
        return _removed_from;
    }
    void print()const;
    bool cancel();
    bool operator==(Reservation);
    friend ostream& operator<<(ostream& ,const RStatus&);

private:
    int _reservation_id;
    DiningHall *_dHall;
    Meal *_meal;
    RStatus _status;
    time_t _created_at, _removed_from;

};

#endif

