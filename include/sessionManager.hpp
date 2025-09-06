#ifndef SESSIONMANAGER_HPP
#define SESSTIONMANAGER_HPP
#pragma once

#include <iostream>
#include "sessionBase.hpp"
#include "student.hpp"
#include "shoppingCart.hpp"

using namespace std;

namespace StudentSession
{
class SessionManager : public SessionBase
{
public:
    static SessionManager& instance();

    void setCurrentStudent(Student*);
    void setShoppingCart(ShoppingCart*);
    void setStudentID(string);

    Student* currentStudent()const
    {
        return _currentStudent;
    }
    ShoppingCart* shoppingCart()const
    {
        return _shopping_cart;
    }
    string getStudentID()const
    {
        return _studentID;
    }

    void login(string, string)override;
    void logout(string, string)override;

private:
    Student* _currentStudent;
    ShoppingCart* _shopping_cart;
    string _studentID;

    SessionManager();
    SessionManager(const SessionManager&) = delete;
    SessionManager& operator=(const SessionManager&) = delete;
    void load_session(string&, const string&)override;
    void save_session(string&, const string&)override;
   
};
}

#endif