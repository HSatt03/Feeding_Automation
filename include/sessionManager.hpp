#ifndef SESSIONMANAGER_HPP
#define SESSTIONMANAGER_HPP
#include <iostream>
#include "../include/sessionBase.hpp"
#include "../include/student.hpp"
#include "../include/shoppingCart.hpp"
using namespace std;

namespace StudentSession
{
class SessionManager : public SessionBase
{
public:
    static SessionManager& instance();

    int getStudentID()const
    {
        return _studentID;
    }

    void login(string, string)override;
    void logout()override;
    Student* currentStudent();
    ShoppingCart* shoppingCart();

private:
    Student* _currentStudent;
    ShoppingCart* _shopping_cart;
    int _studentID;

    SessionManager();
    SessionManager(const SessionManager&) = delete;
    SessionManager& operator=(const SessionManager&) = delete;
    void load_session()override;
    void save_session()override;
   
};
}

#endif