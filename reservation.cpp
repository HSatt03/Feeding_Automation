#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include "meal.hpp"
#include "diningHall.hpp"
#include "reservation.hpp"
using namespace std;
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
    Reservation(int = 0, Enum2 = FAILED, time_t = time(0), Stucent*, DiningHall, Meal); 

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
Reservation::Reservation(int r, Enum2 s, time_t c, Student* S, DiningHall d, Meal m)
{
    setReservation_id(r);
    setStudent(*S);
    setDhall(d);
    setMeal(m);
    setStatus(s);
    setTime(c);
}

void Reservation::setReservation_id(int r)
{
    if(r > 0)
    {
        reservation_id = r;
    }
    else
    {
        throw invalid_argument("Incorrect value for reservations");
    }
}

void Reservation::setStudent(Student* s)
{
    s->setUserId(s->getUserId());
    s->setStudentId(s->getStudentId());
    s->setName(s->getName());
    s->setEmail(s->getEmail());
    s->setBalance(s->getBalance());
    s->setIsActive(s->getIsActive());
}

void Reservation::setDhall(DiningHall d)
{
    d.setHallId(d.getHallId());
    d.setName(d.getName());
    d.setAddress(d.getAddress());
    d.setCapacity(d.getCapacity());
}

void Reservation::setMeal(Meal m)
{
    m.setMeal_id(m.getMeal_id());
    m.setName(m.getName());
    m.setPrice(m.getPrice());
    m.setMeal_type(m.getMeal_type());
}

void Reservation::setStatus(Enum2 s)
{
    _status = s;
}

void Reservation::setTime(time_t t)
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
void Reservation::print()const
{
    cout << "reservation id : " << _reservation_id;
    cout << endl;
    _student->print();
    cout << endl;
    _dHall.print();
    cout << "endl";
    _meal.print();
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
    if(_status == CANCELLED)
    return true;
    else
    return false;
}

bool Reservation::operator==(Reservation ob)
{
    return(_reservation_id == ob._reservation_id
           && _student == ob._student
           && _dHall == ob._dHall
           && _meal == ob._meal
           && _status == ob._status
           && _created_at == ob._created_at);
}
ostream& operator<<(ostream& os, const Enum2& num)
{
    switch(num)
    {
        case FAILED:
            os << "FAILED";
            break;
        case CANCELLED:
            os << "CANCELLED";
            break;
        case SUCCESSFULL:
            os << "SUCCESSFULL";
            break;
        default:
            os << "Unkown!!!";
    }
    return os;
}
