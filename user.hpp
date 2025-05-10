#ifndef USER_HPP
#define USER_HPP
#include <iostream>
#include <string>
using namespace std;
class User
{
public:
    User(int = 0, string = "", string = "", string = "");
    void setUserID(int);
    void setName(string);
    void setLastName(string);
    void setPassword(string);
    int getUserID()const;
    string getName()const;
    string getLastName()const;
    string getPasssword()const;
    virtual void print()const;
    virtual void getType();
private:
    int _user_id;
    string _name;
    string _last_name;
    string _hashed_password;
};
#endif
