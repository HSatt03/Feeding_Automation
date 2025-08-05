#ifndef ADMINPANEL_HPP
#define ADMINPANEL_HPP
#include <iostream>
#include <filesystem>
using namespace std;
namespace fs = std::filesystem;
class AdminPanel
{
public:
    void chooseCsvFile(fs::path);
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