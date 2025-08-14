#ifndef STUDENT_HPP
#define STUDENT_HPP
#include <iostream>
#include <string>
#include <vector>
#include <cctype>
#include "meal.hpp"
#include "user.hpp"
using namespace std;

class User;
class Reservation;

class Student : public User
{
public:
    Student(int = 0, string = "", string = "", string = "", string = "", string = "", string = "", float = 0, bool = 0);

    void setStudentId(string);
    void setEmail(string);
    void setBalance(float);
    void setIsActive(bool);
    void setReservations(vector<Reservation*>);

    void print()const;
    void reserveMeal(Meal*);
    void view_recent_transactions();
    bool cancelReservation(Reservation*);
    bool isActive();
    void activate();
    void deactivate();
    string getType();
    bool operator==(Student);
    void addTransaction(const Transaction&);

    string getStudentId()const
    {
        return _student_id;
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
    vector<Reservation*>& getReserves()
    {
        return _reservations;
    }
    const vector<Transaction>& getTransactions() const
    {
        return _transactions;
    }

private:
    string _student_id;
    string _email;
    float _balance;
    bool _is_active;
    vector<Reservation*>_reservations;
    vector<Transaction> _transactions;
};

#endif