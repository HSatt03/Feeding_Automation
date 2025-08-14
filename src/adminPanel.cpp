#include <iostream>
#include <filesystem>
#include "adminPanel.hpp"
#include "configPaths.hpp"
using namespace std;
namespace fs = std::filesystem;

fs::path AdminPanel::chooseCsvFile()
{
    fs::path csvPath = ConfigPaths::instance().getStudentsCsv();
    return csvPath;
}
void displayAllMeals()
{

}
void displayAllDininigHalls()
{

}
void addNewMealIntractive()
{

}
void addNewDiningHallIntractive()
{

}
void removeMeal(int)
{

}
void removeDiningHall(int)
{

}
void showMenu()
{

}
void action(int)
{
    
}