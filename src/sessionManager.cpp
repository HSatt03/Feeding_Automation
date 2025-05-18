#include <iostream>
#include "sessionBase.hpp"
#include "sessionManager.hpp"
using namespace std;
using namespace StudentSession;

SessionManager& SessionManager::instance()
{
    static StudentSession::SessionManager instance;
    return instance;
}
void SessionManager::load_session()
{

}
void SessionManager::save_session()
{

}
void SessionManager::login(string s1, string s2)
{

}
void SessionManager::logout()
{

}
Student* SessionManager::currentStudent()
{
    return _currentStudent;
}
ShoppingCart* SessionManager::shoppingCart()
{
    return _shopping_cart;
}
