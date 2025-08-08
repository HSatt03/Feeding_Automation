#ifndef USER_HPP
#define USER_HPP
#include <iostream>
#include <string>
using namespace std;

class User
{
public:
    User(int = 0, string = "", string = "", string = "", string  = "");

    void setUserID(int);
    void setName(string);
    void setLastName(string);
    void setPassword(string);
    void setPhone(string);

    virtual void print()const;
    virtual string getType();
    
    int getUserID()const
    {
        return _user_id;
    }
    string getName()const
    {
        return _name;
    }
    string getLastName()const
    {
        return _last_name;
    }
    string getPasssword()const
    {
        return _hashed_password;
    }
    string getPhone()const
    {
        return _phone;
    }

private:
    int _user_id;
    string _name;
    string _last_name;
    string _hashed_password;
    string _phone;
};

#endif
