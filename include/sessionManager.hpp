#ifndef SESSIONMANAGER_HPP
#define SESSTIONMANAGER_HPP
#include <iostream>
#include "../include/sessionBase.hpp"
#include "../include/student.hpp"
#include "../include/shoppingCart.hpp"
using namespace std;

class SessionManager : public SessionBase
{
public:
    static SessionManager instance();

    Student* getCurrentStudsent()const
    {
        return _currentStudent;
    }
    ShoppingCart* getShoppingCart()const
    {
        return _shopping_cart;
    }
    int getStudentID()const
    {
        return _studentID;
    }

    void logout()override;
    Student currentStudent();
    ShoppingCart shoppingCart();

private:
    Student *_currentStudent;
    ShoppingCart *_shopping_cart;
    int _studentID;
    void load_session()override;
    void save_session()override;
   
    
};

#endif