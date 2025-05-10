#ifndef USER_HPP
#define USER_HPP
#include <iostream>
#include <string>
using namespace std;
class User
{
public:
    User(int, string, string, string);
    void setUserID(int);
    void setName(string);
    void setLastName(string);
    void setHashed(string);
    int getUserID()const;
    string getName()const;
    string getLastName()const;
    string getHashed()const;
    virtual void print()const;
    virtual void getType();
private:
    int _userID;
    string _name;
    string _lastName;
    string _hashedPassword;
};
#endif
