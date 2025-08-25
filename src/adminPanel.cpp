#include <iostream>
#include <filesystem>
#include <windows.h>
#include <conio.h>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <iomanip>
#include "adminPanel.hpp"
#include "meal.hpp"
#include "diningHall.hpp"
#include "configPaths.hpp"
using namespace std;
namespace fs = std::filesystem;

void gotoxy(int x, int y)
{
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void drawBox(int x, int y, int width, int height)
{
    // گوشه‌ها
    gotoxy(x, y); cout << "+";
    gotoxy(x + width, y); cout << "+";
    gotoxy(x, y + height); cout << "+";
    gotoxy(x + width, y + height); cout << "+";

    // خطوط افقی
    for (int i = 1; i < width; ++i) {
        gotoxy(x + i, y); cout << "-";
        gotoxy(x + i, y + height); cout << "-";
    }

    // خطوط عمودی
    for (int i = 1; i < height; ++i) {
        gotoxy(x, y + i); cout << "|";
        gotoxy(x + width, y + i); cout << "|";
    }
}

fs::path AdminPanel::chooseCsvFile()
{
    fs::path csvPath = ConfigPaths::instance().getStudentsCsv();
    return csvPath;
}

void AdminPanel::displayAllMeals()
{
    string csvFile = "../meals.json"; // مسیر فایل CSV
    ifstream file(csvFile);
    if (!file.is_open()) 
    {
        cerr << "Cannot open meals CSV file." << endl;
        return;
    }

    string line;
    vector<Meal> meals;

    // خواندن هدر
    getline(file, line);

    while (getline(file, line)) 
    {
        stringstream ss(line);
        string field;
        int mealID;
        string name;
        float price;
        string mealtypeStr, reservedayStr;

        getline(ss, field, ',');
        mealID = stoi(field);

        getline(ss, name, ',');

        getline(ss, field, ',');
        price = stof(field);

        getline(ss, mealtypeStr, ',');

        getline(ss, reservedayStr, ',');

        MealType mealType = Meal::stringToMealType(mealtypeStr);
        ReserveDay reserveDay = Meal::stringToReserveDay(reservedayStr);

        Meal m(mealID, name, price, mealType, reserveDay);
        meals.push_back(m);
    }

    file.close();

    // چاپ همه غذاها
    cout << "=== All Meals ===" << endl;
    for (const auto& m : meals) {
        m.print();  // فرض می‌کنیم متد print() داخل کلاس Meal چاپ مناسب انجام میده
    }
}

void AdminPanel::displayAllDininigHalls()
{
    string csvFile = "../dining_halls.csv"; // مسیر فایل CSV
    ifstream file(csvFile);

    if (!file.is_open()) 
    {
        cerr << "Cannot open dining halls CSV file." << endl;
        return;
    }

    vector<DiningHall> halls;
    string line;

    // خواندن هدر
    getline(file, line);

    // خواندن هر خط و ساخت آبجکت DiningHall
    while (getline(file, line)) 
    {
        stringstream ss(line);
        string field;
        int hallID, capacity;
        string name, genderStr, address;

        getline(ss, field, ',');
        hallID = stoi(field);

        getline(ss, name, ',');

        getline(ss, genderStr, ','); // اینجا می‌تونیم بعداً استفاده کنیم یا نادیده بگیریم

        getline(ss, address, ',');

        getline(ss, field, ',');
        capacity = stoi(field);

        Gender gender = DiningHall::stringToGender(genderStr);

        DiningHall hall(hallID, name, address, capacity);
        halls.push_back(hall);
    }

    file.close();

    // نمایش همه سالن‌ها با متد print
    cout << "=== All Dining Halls ===" << endl;
    for (const auto& hall : halls) 
    {
        hall.print();
    }
}

void AdminPanel::addNewMealIntractive()
{
    int n;
    cout << "How many meals do you want to add to the list?";
    cin >> n;
    cin.ignore();
    json jArray = json::array();
     // اگه فایل قبلی موجوده، اول بخونیم تا داده‌ها حفظ بشن
    ifstream inFile("meals.json");
    if (inFile.is_open() && inFile.peek() != EOF) 
    {
        inFile >> jArray;
    }
    for(int i = 0;  i < n; i++)
    {
        Meal meal;
        cout << i + 1 << ". \n";
        meal.inputMeals();
        jArray.push_back(meal);
    }
    ofstream outFile("meals.json");
    if(!outFile)
    {
        cerr << "The file does not open!!!";
        exit(0);
    }
    outFile << setw(4) << jArray << endl; // نوشتن JSON مرتب
    outFile.close();
    cout << "\nMeal added to json file successfully!\n";
}

void AdminPanel::addNewDiningHallIntractive()
{
    int n;
    cout << "How many diningHalls do you want to add to the list?";
    cin >> n;
    cin.ignore();
    json jArray = json::array();
     // اگه فایل قبلی موجوده، اول بخونیم تا داده‌ها حفظ بشن
    ifstream inFile("diningHalls.json");
    if (inFile.is_open() && inFile.peek() != EOF) 
    {
        inFile >> jArray;
    }
    for(int i = 0;  i < n; i++)
    {
        DiningHall hall;
        cout << i + 1 << ". \n";
        hall.inputHalls();
        jArray.push_back(hall);
    }
    ofstream outFile("diningHalls.json");
    if(!outFile)
    {
        cerr << "The file does not open!!!";
        exit(0);
    }
    outFile << setw(4) << jArray << endl; // نوشتن JSON مرتب
    outFile.close();
    cout << "Dining hall added to CSV file successfully!\n";
}

void AdminPanel::removeMeal(int mealIDToRemove)
{
    string csvFile = "../mealsCsvFile.csv";
    string tempFile = "../temp.csv";

    ifstream inFile(csvFile);
    ofstream outFile(tempFile);

    if(!inFile.is_open() || !outFile.is_open())
    {
        cerr << "Cannot open meals CSV file." << endl;
        return;
    }

    string line;
    bool removed = false;

    // خواندن هدر و نوشتن در فایل موقت
    if(getline(inFile, line)) 
    {
        outFile << line << endl;
    }

    // خواندن هر خط و فیلتر کردن
    while(getline(inFile, line))
    {
        stringstream ss(line);
        string field;
        getline(ss, field, ',');
        int id = stoi(field);

        if (id != mealIDToRemove) 
        {
            outFile << line << endl; // فقط غذاهای غیر از mealID مورد نظر ذخیره میشن
        }   else {
            removed = true;
        }
    }

    inFile.close();
    outFile.close();

    // جایگزینی فایل اصلی با فایل موقت
    if(removed)
    {
        remove(csvFile.c_str());
        rename(tempFile.c_str(), csvFile.c_str());
        cout << "Meal with ID " << mealIDToRemove << " removed successfully.\n";
    } 
    else
    {
        remove(tempFile.c_str());
        cout << "Meal with ID " << mealIDToRemove << " not found.\n";
    }
}

void AdminPanel::removeDiningHall(int hallIDToRemove)
{
    string csvFile = "../diningHallsCsvFile.csv";
    string tempFile = "../temp.csv";

    ifstream inFile(csvFile);
    ofstream outFile(tempFile);

    if(!inFile.is_open() || !outFile.is_open()) 
    {
        cerr << "Cannot open dining halls CSV file." << endl;
        return;
    }

    string line;
    bool removed = false;

    // خواندن هدر و نوشتن در فایل موقت
    if(getline(inFile, line))
    {
        outFile << line << endl;
    }

    // خواندن هر خط و فیلتر کردن بر اساس hallID
    while(getline(inFile, line))
    {
        stringstream ss(line);
        string field;
        getline(ss, field, ',');
        int id = stoi(field);

        if (id != hallIDToRemove) 
        {
            outFile << line << endl; // فقط سالن‌های غیر از hallID مورد نظر ذخیره میشن
        } 
        else 
        {
            removed = true;
        }
    }

    inFile.close();
    outFile.close();

    // جایگزینی فایل اصلی با فایل موقت
    if(removed)
    {
        remove(csvFile.c_str());
        rename(tempFile.c_str(), csvFile.c_str());
        cout << "Dining hall with ID " << hallIDToRemove << " removed successfully.\n";
    } 
    else 
    {
        remove(tempFile.c_str());
        cout << "Dining hall with ID " << hallIDToRemove << " not found.\n";
    }
}

void AdminPanel::showMenu()
{
    int hightMM, widthMM;
    int n,i,j,y_start;
    bool sw_MainMenu;
    char ch;
    sw_MainMenu = false;
    hightMM = 33;
    widthMM = 28;
    y_start = 3;
    gotoxy(5,y_start);
    for(int i=0 ; i<=widthMM-1 ; i++)
    {
        if(i%2==0)
        {
            cout<<"* ";
        }
        else
        {
            cout <<"* ";
        }
    }
    for(int i=1 ; i<hightMM-1 ; i++)
    {
        gotoxy(5,y_start+i);
        cout<<"* ";
        for(int j=1 ; j<widthMM-1 ; j++)
            cout<<"  ";
        cout<<"*";
    }
    gotoxy(5,y_start+i);
    for(int i=0 ; i<=widthMM-1 ; i++)
    {
        if(i%2==0)
        {
            cout <<"* ";
        }
        else
        {
            cout <<"* ";
        }
    }
    gotoxy(12,y_start+2);
    cout <<"Admin Menu    ---  <<Feeding atuomation>>";
    gotoxy(12, y_start+5);
    cout <<"1 _ Display all meals";

    gotoxy(12, y_start+7);
    cout <<"2 _ Display all diningHalls";

    gotoxy(12, y_start+9);
    cout <<"3 _ Add meal";

    gotoxy(12, y_start+11);
    cout << "4 _ Add diningHall";

    gotoxy(12, y_start+13);
    cout <<"5 _ Remove meal";

    gotoxy(12, y_start+15);
    cout << "6 _ Remove diningHall";

    gotoxy(12, y_start+17);
    cout << "7 _ exit";

    gotoxy(12, y_start+19);
    cout<<"Enter Keys : ( 1 to 7 ) ";

    while (!sw_MainMenu)
    {
      if (kbhit())
      {
          n = getch();
          if(n >= 1 && n <= 7)
            action(n);
        else
            gotoxy(12,y_start+31);
            cout << "The number is not valid!";

      }
    }
}
void AdminPanel::action(int number)
{
    switch(number)
    {
        case 1:
            displayAllMeals();
            break;
        case 2:
            displayAllDininigHalls();
            break;
        case 3:
            addNewMealIntractive();
            break;
        case 4:
            addNewDiningHallIntractive();
            break;
        case 5:
            int ID1;
            cout << "Which meal do you want to remove? please enter its ID: ";
            cin >> ID1;
            removeMeal(ID1);
            break;
        case 6:
            int ID2;
            cout << "Which diningHall do you want to remove? please enter its ID: ";
            cin >> ID2;
            removeDiningHall(ID2);
            break;
        case 7:
            exit(0);
            break;
        default:
            cout << "You have selected an out-of-range option.";
    }
}
