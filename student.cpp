#include <iostream>
#include <string>
#include <vector>
#include <cctype>
#include "reservation.hpp"
#include "student.hpp"
#include "meal.hpp"
using namespace std;
Student::Student(int user_id, string name, string last_name, string password, string student_id, string email, float balance, bool is_active)
:User(user_id, name, last_name, password)
{
    setStudentId(student_id);
    setEmail(email);
    setBalance(balance);
    setIsActive(is_active);
}

void Student::setStudentId(string student_id)
{
    if(student_id.length() == 10)
    {
        _student_id = student_id;
    }
    else
    {
        throw invalid_argument("Incorrect value for strudent_id!!!");
    }
}

void Student::setEmail(string email)
{
    bool flag;
    string s1;
    int value = email.length();
    for(int i = 0; i < value; i++)
    {
        if(email[i] == '@')
        {
            flag = true;
            s1 = email.substr(i, 10);
            if(s1 == "@gmail.com")
            {
                _email = email;
            } 
            else
            {
                throw invalid_argument("Incorrect email!!!");
            }
        }
        else if(flag == false && i == value - 1)
        {
            throw invalid_argument("Incorrect email!!!");
        }
    }
}

void Student::setBalance(float balance)
{
    if(balance >= 0)
    {
        _balance = balance;
    }
    else 
    {
        throw invalid_argument("Incorrect value for balance!!!");
    }
}

void Student::setIsActive(bool is_active)
{
    _is_active = is_active;
}

void Student::setReservations(vector<Reservation*>reserve)
{
    _reservations = reserve;
}

void Student::print()const
{
    cout << "Name: " << getName() << 
                            "\nLast Name: " << getLastName() <<
                                             "\nUser Id: " << getUserID() << 
                                                                "\nStudent Id: " << _student_id << 
                                                                                     "\nEmail: " << _email <<
                                                                                            "\nBalance: " << _balance << endl;
}

void Student::reserveMeal(Meal meal)
{
    Reservation* reserve;
    reserve->setMeal(meal);
    _reservations.push_back(reserve);
}

bool Student::cancelReservation(Reservation* reserve)
{
    bool success = false;
    for(auto add = _reservations.begin(); add != _reservations.end(); add++)
    {
        if(*add == reserve)
        {
            _reservations.erase(add);
            success = true;
        }
    }
    if(success)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool Student::operator==(Student ob)
{
    return(getUserID() == ob.getUserID()
          && getName() == ob.getName()
          && getLastName() == ob.getLastName()
          && getPasssword() == ob.getPasssword()
          && _student_id == ob._student_id
          && _email == ob._email
          && _balance == ob._balance
          && _is_active == ob._is_active);
}
