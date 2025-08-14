#include <iostream>
#include <string>
#include "../include/diningHall.hpp"
using namespace std;
ostream& operator<<(ostream& os, const Gender& gender)
{
    if(gender == Gender::MALE)
    {
        os << "Male";
    }
    else if(gender == Gender::FEMALE)
    {
        os << "Female";
    }
    else
    {
        os << "Female";
    }
    return os;
} 

DiningHall::DiningHall(int hall_id, string name, string address, int capacity)
{
    _hall_id = hall_id;
    _name = name;
    _address = address;
    _capacity = capacity;
}
void DiningHall::setHallId(int hall_id)
{
    if(hall_id == 1 && hall_id == 2)
    {
        _hall_id = hall_id;
    }
    else 
    {
        throw invalid_argument("Incorect value for hall_id!!!");
    }
}
void DiningHall::setName(string name)
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
void DiningHall::setGender(Gender g)
{
    if(g == Gender::MALE || g == Gender::FEMALE)
    {
        _gender = g;
    }
    else
    {
        throw invalid_argument("Incorrect value for gender!!!");
    }
}
void DiningHall::setAddress(string address)
{
    _address = address;
}
void DiningHall::setCapacity(int capacity)
{
    if(capacity > 0)
    {
        _capacity = capacity;
    }
}
void DiningHall::print()const
{
    cout << "Name: " << _name << 
                            "\nHall Id: " << _hall_id << 
                                                    "\nAddress: " << _address << 
                                                                            "\nCapacity: " << _capacity << "\nGender: " << _gender << endl;            
}

Gender stringToGender(const string& s) 
{
    if(s == "Male")
    { 
        return Gender::MALE;
    }
    if(s == "FEMALE")
    { 
        return Gender::FEMALE;
    }
    return Gender::FEMALE; // پیش‌فرض
}

Gender selectGender() 
{
    int choice;
    cout << "Select gender:\n1. Male\n2. Female\nChoice: ";
    cin >> choice;
    switch (choice) {
        case 1: return Gender::MALE;
        case 2: return Gender::FEMALE;
        default: 
            cout << "Invalid choice, default BREAKFAST selected.\n";
            return Gender::FEMALE;
    }
}

