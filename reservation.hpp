#ifndef RESERVATION_H
#define RESERVATION_H
#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include "meal.hpp"
#include "diningHall.hpp"
class Stucent;

enum Enum2
{
    FAILED,
    CANCELLED,
    SUCCESSFULL,
};

class Reservation
{
public:
    Reservation(int = 0, Enum2 = FAILED, time_t = time(0)); 

    void setReservation_id(int);
    void setStudent(Student*);
    void setDhall(DiningHall);
    void setMeal(Meal);
    void setStatus(Enum2);
    void setTime(time_t);

    int getReservation_id()const
    {
        return _reservation_id;
    }
    Student getStudent()const
    {
        return *_student;
    }
    DiningHall getDhall()const
    {
        return _dHall;
    }
    Meal getMeal()const
    {
        return _meal;
    }
    Enum getStatus()const
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
    friend ostream& operator<<(ostream& ,const Enum2&);

private:
    int _reservation_id;
    Student *_student;
    DiningHall _dHall;
    Meal _meal;
    Enum2 _status;
    time_t _created_at;
};
#endif

