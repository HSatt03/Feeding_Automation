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
    PENDING,
    NOT_PAID
};

class Reservation
{
public:
    Reservation(DiningHall* d = nullptr, Meal* m = nullptr, int r = 0,
            RStatus s = RStatus::PENDING, time_t t_c = time(0), time_t t_r = 0); 

    //void setReservation_id(int);
    void setDhall(DiningHall*);
    void setMeal(Meal*);
    void setStatus(RStatus);
    void setCreatedTime(time_t);
    void setRemovedTime(time_t);

   int getReservation_id() const 
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
    DiningHall* getDhallPtr() const { return _dHall; }
    Meal* getMealPtr() const { return _meal; }

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
    static int _next_id;     // شمارنده‌ی سراسری
    int _reservation_id;
    DiningHall *_dHall;
    Meal *_meal;
    RStatus _status;
    time_t _created_at, _removed_from;

};

#endif

