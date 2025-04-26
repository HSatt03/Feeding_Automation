#include <iostream>
#include <string>
#include <vector>
#include <cctype>
using namespace std;

enum Enum1
{
    FIRST_GROUP,
    SECOND_GROUP,
    THRID_GROUP,
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

    void print();
    void update_price(float);
    void add_side_item(string);
    bool operator==(Meal);
    friend ostream& operator<<(ostream&, const Enum1&);

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

private:
    int _meal_id;
    string _name;
    float _price;
    Enum1 _meal_type;
    vector<string> _side_item;
};
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
void Meal::print()
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
