#ifndef ADMINPANEL_HPP
#define ADMINPANEL_HPP
#include <iostream>
using namespace std;
class AdminPanel
{
public:
    fs::path chooseCsvFile();
    void displayAllMeals();
    void displayAllDininigHalls();
    void addNewMealIntractive();
    void addNewDiningHallIntractive();
    void removeMeal(int);
    void mealAcitvation(int, bool);
    void removeDiningHall(int);
    void showMenu();
    void action(int);
};
#endif 