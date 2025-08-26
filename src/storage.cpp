#include <iostream>
#include <algorithm>
#include "storage.hpp"
#include "meal.hpp"
#include "diningHall.hpp"

using namespace std; 

Storage::Storage(int mealIDCounter, int diningHallIDCounter)
{
    setMealIDCounter(mealIDCounter);
    setDiningHallIDCounter(diningHallIDCounter);
}
void Storage::setMealIDCounter(int m)
{
    _mealIDCounter = (m > 0) ? m : 0;
}
void Storage::setDiningHallIDCounter(int d)
{
    _diningHallIDCounter = (d > 0) ? d : 0;
}
Storage& Storage::instance()
{
    static Storage instance;
    return instance;
}

void Storage::addMeal(Meal* meal)
{
    allMeals.push_back(meal);
}

void Storage::addDiningHall(DiningHall* hall)
{
    allDiningHall.push_back(hall);
}

void Storage::removeMeal(int mealId)
{
    auto it = findMeal(mealId);
    if (it != allMeals.end())
    {
        allMeals.erase(it);
    }
}


void Storage::removeDiningHall(int hallId)
{
    auto it = findDiningHall(hallId);
    if (it != allDiningHall.end())
    {
        allDiningHall.erase(it);
    }
}

void Storage::MealActivation(int mealId, bool active)
{
    auto it = findMeal(mealId);
    if (it != allMeals.end() && *it != nullptr)
    {
        (*it)->setIsActive(active);
    }
}

vector<Meal*>::iterator Storage::findMeal(int mealId)
{
    return find_if(allMeals.begin(), allMeals.end(),
                   [mealId](Meal* m) { return m->getMeal_id() == mealId; });
}

vector<DiningHall*>::iterator Storage::findDiningHall(int hallId)
{
    return find_if(allDiningHall.begin(), allDiningHall.end(),
                   [hallId](DiningHall* d) { return d->getHallId() == hallId; });
}
