#ifndef MEAL_H
#define MEAL_H
#include <iostream>
#include <string>
#include <vector>
#include <cctype>
using namespace std;

enum Enum1
{
    FIRST_GROUP,
    SECOND_GROUP,
    THRID_GROUP
};

enum Enum3
{
    SATURDAY,
    SUNDAY,
    MONDAY,
    TUESDAY, 
    WEDNESDAY,
    THURSDAY
};

class Meal
{
public:
    Meal(int = 0, string = "NAME", float = 0.0, Enum1 = FIRST_GROUP);

    void setMeal_id(int);
    void setName(string);
    void setPrice(float);
    void setMeal_type(Enum1);
    void setSide_item(vector<string>);
    void setIsActive(bool);
    void setReservationDay(Enum3);

    void print()const;
    void update_price(float);
    void add_side_item(string);
    bool operator==(Meal);
    friend ostream& operator<<(ostream&, const Enum1&);
    bool activate();
    bool deactivate();

    int getMeal_id()const 
    {
        return _meal_id;
    }
    string getName()const 
    {
        return _name;
    }
    float getPrice()const
    {
        return _price;
    }
    Enum1 getMeal_type()const
    {
        return _meal_type;
    }
    vector<string> getSide_item()const
    {
        return _side_item;
    }
    bool getIsActive()const
    {
        return _isActive;
    }
    Enum3 getReservationDay()const
    {
        return _reservation_day;
    }

private:
    int _meal_id;
    string _name;
    float _price;
    Enum1 _meal_type;
    vector<string> _side_item;
    bool _isActive;
    Enum3 _reservation_day;
};
#endif

