#include <iostream>
#include "storage.hpp"
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