#include <iostream>
#include <string>
#include "../include/diningHall.hpp"
using namespace std;
DiningHall::DiningHall(int hall_id = 2, string name = "Sadaf", string address = "Next to the Central Library", int capacity = 100)
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
                                                                            "\nCapacity: " << _capacity << endl;            
}