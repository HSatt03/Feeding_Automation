#include <iostream>
#include <string>
#include <vector>
#include <cctype>
#include <algorithm>
#include "reservation.hpp"
#include "student.hpp"
#include "meal.hpp"
#include "transaction.hpp"

using namespace std;

Student::Student(int user_id, string name, string last_name, string password, string phone, string student_id, string email, float balance, bool is_active)
:User(user_id, name, last_name, password, phone)
{
    setStudentId(student_id);
    setEmail(email);
    setBalance(balance);
    setIsActive(is_active);
}

string Student::trim(const std::string& str)
{
    auto start = std::find_if_not(str.begin(), str.end(), ::isspace);
    auto end = std::find_if_not(str.rbegin(), str.rend(), ::isspace).base();
    if (start >= end) return "";
    return std::string(start, end);
}

void Student::setStudentId(string student_id)
{
    student_id = trim(student_id);
    if(student_id.length() == 10)
    {
        _student_id = student_id;
    }
    else
    {
        throw invalid_argument("Incorrect value for student_id!!!");
    }
}

void Student::setEmail(string email)
{
    bool flag = false;
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

void Student::setTransactions(const vector<Transaction>& transaction)
{
    _transactions = transaction;
}

void Student::print()const
{
    User::print();
    cout << "\nStudent Id: " << _student_id << 
                        "\nEmail: " << _email <<
                                "\nBalance: " << _balance << endl;
}

void Student::reserveMeal(Meal* meal)
{
    Reservation* reserve = new Reservation();
    reserve->setMeal(meal);
    _reservations.push_back(reserve);
}

void Student::view_recent_transactions()
{
    
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
            break;
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

bool Student::isActive()
{
    if(_is_active)
    {
        return true;
    }
    else
    {
        return false;
    }
}

void Student::activate()
{
    _is_active = true;
}

void Student::deactivate()
{
    _is_active = false;
}
string Student::getType()
{
    return "Student";
}

bool Student::operator==(Student ob)
{
    return(getUserID() == ob.getUserID()
          && getName() == ob.getName()
          && getLastName() == ob.getLastName()
          && getHashedPassword() == ob.getHashedPassword()
          && _student_id == ob._student_id
          && _email == ob._email
          && _balance == ob._balance
          && _is_active == ob._is_active);
}

void Student::addTransaction(const Transaction& t)
{
    _transactions.push_back(t);
}
