#include <iostream>
#include <string>
#include <vector>
#include <cctype>
#include "../include/meal.hpp"
using namespace std;

Meal::Meal(int m, string n, float p, MealType mt, ReserveDay r, bool b)
{
    setMeal_id(m);
    setName(n);
    setPrice(p);
    setMeal_type(mt);
    setReserveDay(r);
    setIsActive(b);
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

void Meal::setMeal_type(MealType e)
{ 
    if(e == MealType::BREAKFAST || e == MealType::LUNCH || e == MealType::DINNER)
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

void Meal::setReserveDay(ReserveDay e)
{
    if(e == ReserveDay::SATURDAY || e == ReserveDay::SUNDAY || e == ReserveDay::MONDAY || e == ReserveDay::TUESDAY || e ==  ReserveDay::WEDNESDAY || e == ReserveDay::THURSDAY) 
    {
        _reserve_day = e;
    }
    else
    {
        throw invalid_argument("Incorrect value for reservation_day!!!");
    }
}

void Meal::inputMeals()
{
    cout << "Meal ID: ";
    cin >> _meal_id;
    cout << "Meal Name: ";
    getline(cin, _name);
    cout << "Meal Price: ";
    cin >> _price;
    cout << "Meal Type: ";
    _meal_type = selectMealType();
    cout << "Reserve Dat: ";
    _reserve_day = selectReserveDay();
}
void Meal::print()const
{
    cout << "Meal id : " << _meal_id;
    cout << "\nMeal name : " << _name;
    cout << "\nMeal price : " << _price;
    cout << "\nMeal type : " << _meal_type;
    cout << "\nSide item : ";
    for (int i=0 ; i < _side_item.size() ; ++i)
    {
            cout << _side_item[i] << " , ";
    } 
    cout << "\nReserve Day:" << _reserve_day;
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

string to_string(MealType type) 
{
    switch(type) 
    {
        case MealType::BREAKFAST: 
            return "BREAKFAST";
        case MealType::LUNCH: 
            return "LUNCH";
        case MealType::DINNER: 
            return "DINNER";
    }
    return "UNKNOWN";
} 

string to_string(ReserveDay day) 
{
    switch(day) 
    {
        case ReserveDay::SATURDAY: 
            return "SATURDAY";
        case ReserveDay::SUNDAY: 
            return "SUNDAY";
        case ReserveDay::MONDAY: 
            return "MONDAY";
        case ReserveDay::TUESDAY: 
            return "TUESDAY";
        case ReserveDay::WEDNESDAY: 
            return "WEDNESDAY";
        case ReserveDay::THURSDAY: 
            return "THURSDAY";
    }
    return "UNKNOWN";
}

ostream& operator<<(ostream& os, const MealType& num)
{
    switch(num)
    {
        case MealType::BREAKFAST:
            os << "BREAKFAST";
            break;
        case MealType::LUNCH:
            os << "LUNCH";
            break;
        case MealType::DINNER:
            os << "DINNER";
            break;
        default:
            os << "Unknown!!!";
    }
    return os;
}

ostream& operator<<(ostream& os, const ReserveDay& num)
{
    switch(num)
    {
        case ReserveDay::SATURDAY:
            os << "SATURDAY";
            break;
        case ReserveDay::SUNDAY:
            os << "SUNDAY";
            break;
        case ReserveDay::MONDAY:
            os << "MONDAY";
            break;
        case ReserveDay::TUESDAY:
            os << "TUESDAY";
            break;
        case ReserveDay::WEDNESDAY:
            os << "WEDNESDAY";
            break;
        case ReserveDay::THURSDAY:
            os << "THURSDAY";
            break;
        default:
            os << "Unknown!!!";
    }
    return os;
}

void Meal::isActive(bool b)
{
    _isActive = b;
}
bool Meal::activate()
{
    isActive(1);
    return true;
}

bool Meal::deactivate()
{
    isActive(0);
    return true;
}

MealType stringToMealType(const string& s) 
{
    if(s == "BREAKFAST")
    { 
        return MealType::BREAKFAST;
    }
    if(s == "LUNCH")
    { 
        return MealType::LUNCH;
    }
    if(s == "DINNER") 
    { 
        return MealType::DINNER;
    }
    return MealType::BREAKFAST; // پیش‌فرض
}

ReserveDay stringToReserveDay(const string& s) 
{
    if(s == "SATURDAY")
    { 
        return ReserveDay::SATURDAY;
    }
    if(s == "SUNDAY")
    {
        return ReserveDay::SUNDAY;
    }
    if(s == "MONDAY")
    {
        return ReserveDay::MONDAY;
    }
    if(s == "TUESDAY")
    { 
        return ReserveDay::TUESDAY;
    }
    if(s == "WEDNESDAY")
    { 
        return ReserveDay::WEDNESDAY;
    }
    if(s == "THURSDAY")
    { 
        return ReserveDay::THURSDAY;
    }
    return ReserveDay::SATURDAY; // پیش‌فرض
}

MealType selectMealType() 
{
    int choice;
    cout << "Select meal type:\n1. BREAKFAST\n2. LUNCH\n3. DINNER\nChoice: ";
    cin >> choice;
    switch (choice) {
        case 1: return MealType::BREAKFAST;
        case 2: return MealType::LUNCH;
        case 3: return MealType::DINNER;
        default: 
            cout << "Invalid choice, default BREAKFAST selected.\n";
            return MealType::BREAKFAST;
    }
}

ReserveDay selectReserveDay() 
{
    int choice;
    cout << "Select reserve day:\n1. SATURDAY\n2. SUNDAY\n3. MONDAY\n4. TUESDAY\n5. WEDNESDAY\n6. THURSDAY\nChoice: ";
    cin >> choice;
    switch(choice) {
        case 1: return ReserveDay::SATURDAY;
        case 2: return ReserveDay::SUNDAY;
        case 3: return ReserveDay::MONDAY;
        case 4: return ReserveDay::TUESDAY;
        case 5: return ReserveDay::WEDNESDAY;
        case 6: return ReserveDay::THURSDAY;
        default:
            cout << "Invalid choice, default SATURDAY selected.\n";
            return ReserveDay::SATURDAY;
    }
}
