#ifndef RESERVATION_H
#define RESERVATION_H
#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include "meal.hpp"
#include "diningHall.hpp"

enum RStatus
{
    FAILED,
    CANCELLED,
    SUCCESSFULL,
    NOT_PAID
};

class Reservation
{
public:
    Reservation(DiningHall*, Meal*, int = 0, RStatus = FAILED, time_t = time(0)); 

    void setReservation_id(int);
    void setDhall(DiningHall*);
    void setMeal(Meal*);
    void setStatus(RStatus);
    void setTime(time_t);

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
    time_t getTime()const
    {
        return _created_at;
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
    time_t _created_at;

};
#endif

