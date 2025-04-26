#ifndef STUDENT_H
#define STUDENT_H
#include <iostream>
#include <string>
#include <vector>
#include <cctype>
#include "meal.hpp"
using namespace std;
class Reservation;
class Student
{
public:
    Student(int user_id = 12, string student_id = "4022559082", string name = "name", string email = "name20002001@gmail.com", float balance = 100000, bool is_active = false);

    void setUserId(int);
    void setStudentId(string);
    void setName(string);
    void setEmail(string);
    void setBalance(float);
    void setIsActive(bool);
    void setReservations(vector<Reservation>);

    void print()const;
    void reserveMeal(Meal);
    bool cancelReservation(Reservation);
    bool operator==(Student);
    int getUserId()const
    {
        return _user_id;
    }
    string getStudentId()const
    {
        return _student_id;
    }
    string getName()const
    {
        return _name;
    }
    string getEmail()const
    {
        return _email;
    }
    float getBalance()const
    {
        return _balance;
    }
    bool getIsActive()const
    {
        return _is_active;
    }
    const vector<string>& getReservations()const
    {
        return _reservations;
    }

private:
    int _user_id;
    string _student_id;
    string _name;
    string _email;
    float _balance;
    bool _is_active;
    vector<Reservation*>_reservations;
};
#endif