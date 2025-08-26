#ifndef MEAL_H
#define MEAL_H
#include <iostream>
#include <string>
#include <vector>
#include <cctype>
#include "json.hpp"

using namespace std;
using json = nlohmann::json;

enum class MealType
{
    BREAKFAST,
    LUNCH,
    DINNER
};

enum class ReserveDay
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
    Meal(int = 0, string = "NAME", float = 0.0, MealType = MealType::BREAKFAST, ReserveDay = ReserveDay::SATURDAY, bool = 0);

    void setMeal_id(int);
    void setName(string);
    void setPrice(float);
    void setMeal_type(MealType);
    void setSide_item(vector<string>);
    void setIsActive(bool);
    void setReserveDay(ReserveDay);
    void inputMeals();

    void isActive(bool);
    void print()const;
    void update_price(float);
    void add_side_item(string);
    bool activate();
    bool deactivate();
    bool operator==(Meal);
    string to_string(MealType);
    string to_string(ReserveDay);
    friend ostream& operator<<(ostream&, const MealType&);
    friend ostream& operator<<(ostream&, const ReserveDay&);

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
        return _reserve_day;
    }

    static MealType stringToMealType(const string&);
    static string mealTypeToString(MealType);
    static ReserveDay stringToReserveDay(const string&); 
    static string reserveDayToString(ReserveDay);
    static MealType selectMealType();
    static ReserveDay selectReserveDay(); 
    // MealType stringToMealType(const string&);
    // ReserveDay stringToReserveDay(const string&);
    friend ostream& operator<<(ostream& os, const MealType& num);
    friend ostream& operator<<(ostream& os, const ReserveDay& num);

private:
    int _meal_id;
    string _name;
    float _price;
    MealType _meal_type;
    vector<string> _side_item;
    bool _isActive;
    ReserveDay _reserve_day;
};

namespace nlohmann
{
    template<>
    struct adl_serializer<Meal>
    {
        static void to_json(json& j, const Meal& m)
        {
            j = {
                {"mealID", m.getMeal_id()},
                {"name", m.getName()},
                {"price", m.getPrice()},
                {"mealtype", Meal::mealTypeToString(m.getMeal_type())},
                {"reserveday", Meal::reserveDayToString(m.getReserveDay())}
                // {"sideItems", m.getSide_item()}
                };
        }
        static void from_json(const json& j, Meal &m)
        {
            m.setMeal_id(j.at("mealID").get<int>());
            m.setName(j.at("name").get<string>());
            m.setPrice(j.at("price").get<float>());
            m.setMeal_type(Meal::stringToMealType(j.at("mealtype").get<string>()));
            m.setReserveDay(Meal::stringToReserveDay(j.at("reserveday").get<string>()));
            // m.setSide_item(j.at("sideItems").get<vector<string>>());
        }
    };
}

#endif

