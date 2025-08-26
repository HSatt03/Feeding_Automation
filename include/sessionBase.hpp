#ifndef SESSIOSBASE_HPP
#define SESSTIONBASE_HPP
#pragma once
#include <iostream>
#include <ctime>

using namespace std;

enum class SessionStatus
{
    AUTHENTICATED,
    ANONYMOUS
};
class SessionBase
{
public:
    
    virtual void login(string, string) = 0;
    virtual void logout(string, string) = 0; 

    void setCreatedAt(time_t);
    void setLasttimeLogin(time_t);
    void setSessionStatus(SessionStatus);

    time_t getCreatedAt()const
    {
        return _createdAt;
    }
    time_t getLasttimeLogin()const
    {
        return _lasttimeLogin;
    }
    SessionStatus getSessionStstus()const
    {
        return _status;
    }

protected:
    time_t _createdAt;
    time_t _lasttimeLogin;
    SessionStatus _status;
    virtual void load_session(string& studentID, const string& password) = 0;
    virtual void save_session(string& studentID, const string& password) = 0;
    
};

#endif