#ifndef MEAL_H
#define MEAL_H
#include <iostream>
#include <string>
#include <vector>
#include <cctype>
using namespace std;

enum MealType
{
    FIRST_GROUP,
    SECOND_GROUP,
    THRID_GROUP
};

enum ReserveDay
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
    Meal(int = 0, string = "NAME", float = 0.0, MealType = FIRST_GROUP, ReserveDay = SATURDAY, bool = 0);

    void setMeal_id(int);
    void setName(string);
    void setPrice(float);
    void setMeal_type(EnuMealTypem1);
    void setSide_item(vector<string>);
    bool isActive(bool);
    void setIsActive(bool);
    void setReserveDay(ReserveDay);

    void print()const;
    void update_price(float);
    void add_side_item(string);
    bool operator==(Meal);
    friend ostream& operator<<(ostream&, const MealType&);
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
    MealType getMeal_type()const
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
    ReserveDay getReserveDay()const
    {
        return _reservation_day;
    }

private:
    int _meal_id;
    string _name;
    float _price;
    MealType _meal_type;
    vector<string> _side_item;
    bool _isActive;
    ReserveDay _reserve_day;
};
#endif

