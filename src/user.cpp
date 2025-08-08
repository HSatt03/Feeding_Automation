#include <iostream>
#include <string>
#include "../include/user.hpp"
using namespace std;

User::User(int user_id, string name, string last_name, string password, string phone)
{
    setUserID(user_id);
    setName(name);
    setLastName(last_name);
    setPassword(password);
    setPhone(phone);
}

void User::setUserID(int user_id)
{
    if(user_id > 0)
    {
        _user_id = user_id;
    }
    else 
    {
        throw invalid_argument("Incorrect value for userID!!!");
    }
}

void User::setName(string name)
{
    int value = name.length();
    for(int i = 0; i < value; i++)
    {
        if(!isalpha(name[i]))
        {
            throw invalid_argument("Incorrect name!!!");
        }
    }
    _name = name;
}

void User::setLastName(string last_name)
{
    int value = last_name.length();
    for(int i = 0; i < value; i++)
    {
        if(!isalpha(last_name[i]))
        {
            throw invalid_argument("Incorrect name!!!");
        }
    }
    _last_name = last_name;
}

void User::setPassword(string password)
{
    _hashed_password = password;
}

void User::setPhone(string phone)
{
    _phone = phone;
}
void User::print()const
{
    cout << "Name: " << _name << 
                            "\nLast Name: " << _last_name <<
                                                "\nUser Id: " << _user_id << 
                                                                "\nHashed Password: " << _hashed_password;
}

string User::getType()
{
    return "User";
}