#include <iostream>
#include "sessionBase.hpp"

using namespace std;

void SessionBase::setCreatedAt(time_t createdAt)
{
    if(createdAt > 0)
    {
        _createdAt = createdAt;
    }
    else 
    {
        throw invalid_argument("Incorrect value for time!!!");
    }
}
void SessionBase::setLasttimeLogin(time_t lasttimeLogin)
{
    if(lasttimeLogin > 0)
    {
        _lasttimeLogin = lasttimeLogin;
    }
    else 
    {
        throw invalid_argument("Incorrect value for time!!!");
    }
}
void SessionBase::setSessionStatus(SessionStatus status)
{
    if(status == SessionStatus::ANONYMOUS || status == SessionStatus::AUTHENTICATED)
    {
        status = _status;
    }
    else
    {
        throw invalid_argument("Incorrect value for status!!!");
    }
}
