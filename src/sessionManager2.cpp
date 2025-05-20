#include <iostream>
#include "../include/sessionBase.hpp"
#include "../include/SessionManager2.hpp"
#include "../include/admin.hpp"
using namespace std;
using namespace AdminSession;

SessionManager::SessionManager(Admin *a, int i)
{
    _currentAdmin = a;
    _adminID = i;
}
Admin SessionManager::currentAdmin()
{
    return *_currentAdmin;
}