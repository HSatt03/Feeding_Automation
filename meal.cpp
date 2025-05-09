#include <iostream>
#include <string>
#include <vector>
#include <cctype>
#include "meal.hpp"
using namespace std;

Meal::Meal(int m, string n, float p, Enum1 mt)
{
    setMeal_id(m);
    setName(n);
    setPrice(p);
    setMeal_type(mt);
}

void Meal::setMeal_id(int m) 
{
    if(m > 0)
    {
        _meal_id = m;
    }
    else
    {
        throw invalid_argument("Incorrect value for meal_id!!!");
    }
}

void Meal::setName(string name)
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

void Meal::setPrice(float p)
{
    if(p > 0.0)
    {
        _price = p;
    }
    else
    {
        throw invalid_argument("Incorrect value for price!!!");
    }
}

void Meal::setMeal_type(Enum1 e)
{ 
    if(e == FIRST_GROUP || e == SECOND_GROUP || e == THRID_GROUP)
    {
        _meal_type = e;
    }
    else
    {
        throw invalid_argument("Incorrect value for meal_type!!!");
    }
}

void Meal::setSide_item(vector<string> si)
{
    _side_item = si;
}

void Meal::setIsActive(bool b)
{
    _isActive = b;
}

void Meal::setReservationDay(Enum3 e)
{
    if(e == SATURDAY || e == SUNDAY || e == MONDAY || e == TUESDAY || e ==  WEDNESDAY || e == THURSDAY) 
    {
        _reservation_day = e;
    }
    else
    {
        throw invalid_argument("Incorrect value for reservation_day!!!");
    }
}

void Meal::print()const
{
    cout << "meal id : " << _meal_id;
    cout << "\nmeal name : " << _name;
    cout << "\nmeal price : " << _price;
    cout << "\nmeal type : " << _meal_type;
    cout << "\nside item : ";
    for (int i=0 ; i < _side_item.size() ; ++i)
    {
            cout << _side_item[i] << " , ";
    } 
}

void Meal::update_price(float new_price)
{
    setPrice(new_price);
}

void Meal::add_side_item(string item)
{
    _side_item.push_back(item);
}

bool Meal::operator==(Meal ob)
{
    return(_meal_id == ob._meal_id
            && _name == ob._name
            && _price == ob._price
            && _meal_type == ob._meal_type
            && _side_item == ob._side_item);
}
ostream& operator<<(ostream& os, const Enum1& num)
{
    switch(num)
    {
        case FIRST_GROUP:
            os << "FIRST_GROUP";
            break;
        case SECOND_GROUP:
            os << "SECOND_GROUP";
            break;
        case THRID_GROUP:
            os << "THRID_GROUP";
            break;
        default:
            os << "Unknown!!!";
    }
    return os;
}

bool Meal::activate()
{
    _isActive = 1;
}

bool Meal::deactivate()
{
    _isActive = 0;
}
