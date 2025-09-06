#include <iostream>
#include <string>
#include <algorithm>
#include <stdexcept>
#include "diningHall.hpp"

using namespace std;
void gotoxy(int x, int y);

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
    if(hall_id >= 0)
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

void DiningHall::inputHalls()
{
    cout << "DiningHall ID: ";
    cin >> _hall_id;
    cin.ignore();
    cout << "DiningHall Name: ";
    getline(cin, _name);
    _gender = selectGender();
    cin.ignore();
    cout << "DiningHall Address: ";
    getline(cin, _address);
    cout << "DiningHall Capacity: ";
    cin >> _capacity;
}

void DiningHall::print(int startLine) const
{
    int i = 2;
    int j = startLine;

    gotoxy(i, j++);
    cout << "Name: " << _name;

    gotoxy(i, j++);
    cout << "Hall Id: " << _hall_id;

    gotoxy(i, j++);
    cout << "Address: " << _address;

    gotoxy(i, j++);
    cout << "Capacity: " << _capacity;

    gotoxy(i, j++);
    cout << "Gender: " << _gender;

    gotoxy(i, j++);
    cout << "********************" << endl;
}

void DiningHall::print_panel(int startX, int startY) const
{
    int i = startX;
    int j = startY;
    
    gotoxy(i, j++);
    cout << "Hall information:";
    gotoxy(i, j++);
    cout << "Name: " << _name;
    gotoxy(i, j++);
    cout << "Hall Id: " << _hall_id;
    gotoxy(i, j++);
    cout << "Address: " << _address;
    gotoxy(i, j++);
    cout << "Capacity: " << _capacity;
    gotoxy(i, j++);
    cout << "Gender: " << _gender;
}

Gender DiningHall::stringToGender(const string& s) 
{
    if(s == "Male")
    { 
        return Gender::MALE;
    }
    else if(s == "Female")
    { 
        return Gender::FEMALE;
    }
    else
    {
        return Gender::FEMALE; // پیش‌فرض
    }
}

string DiningHall::genderToString(Gender g) 
{
    switch (g) 
    {
        case Gender::FEMALE:
            return "FEMALE";
        case Gender::MALE:
            return "MALE";
    }
    return "UNKNOWN";
} 

Gender DiningHall::selectGender() 
{
    int choice;
    cout << "Select gender:\n1. Male\n2. Female\nChoice: ";
    cin >> choice;
    switch (choice) 
    {
        case 1: 
            return Gender::MALE;
        case 2: 
            return Gender::FEMALE;
        default: 
            cout << "Invalid choice, default BREAKFAST selected.\n";
            return Gender::FEMALE;
    }
}

