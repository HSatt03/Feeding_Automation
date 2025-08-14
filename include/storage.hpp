#ifndef STORAGE_H
#define STORAGE_H
#include <iostream>
#include <vector>
using namespace std;

class Meal;
class DiningHall;

class Storage
{
public:
    void setMealIDCounter(int);
    void setDiningHallIDCounter(int);

    vector<Meal*> allMeals;
    vector<DiningHall*> allDiningHall;
    static Storage& instance();
    int getMealIDCounter()const
    {
        return _mealIDCounter;
    }
    int getDiningHallIDCounter()const
    {
        return _diningHallIDCounter;
    }
    void addMeal(Meal*);
    void addDiningHall(DiningHall*);
    void removeMeal(int);
    void removeDiningHall(int);
    void MealActivation(int, bool);
    vector<Meal*>::iterator findMeal(int);
    vector <DiningHall*>::iterator findDiningHall(int);


private:
    int _mealIDCounter;
    int _diningHallIDCounter;
    Storage(int = 0, int = 0);
    Storage(const Storage&) = delete;
    Storage operator=(const Storage&) = delete;
};

#endif4