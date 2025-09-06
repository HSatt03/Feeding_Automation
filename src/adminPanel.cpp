#include <iostream>
#include <filesystem>
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
#include "utils.hpp"

using namespace std;
namespace fs = std::filesystem;

void gotoxy(int x, int y);

void drawBox(int x, int y, int width, int height);

fs::path AdminPanel::chooseCsvFile()
{
    fs::path csvPath = ConfigPaths::instance().getStudentsCsv();
    return csvPath;
}

void AdminPanel::displayAllMeals()
{
    string mealsFile = "meals.json"; // مسیر فایل CSV
    ifstream file(mealsFile);
    if (!file.is_open()) 
    {
        cerr << "Cannot open meals json file." << endl;
        return;
    }

    // string line;
    // vector<Meal> meals;

    // خواندن هدر
    // getline(file, line);

    // while (getline(file, line)) 
    // {
    //     stringstream ss(line);
    //     string field;
    //     int mealID;
    //     string name;
    //     float price;
    //     string mealtypeStr, reservedayStr;

    //     getline(ss, field, ',');
    //     mealID = stoi(field);

    //     getline(ss, name, ',');

    //     getline(ss, field, ',');
    //     price = stof(field);

    //     getline(ss, mealtypeStr, ',');

    //     getline(ss, reservedayStr, ',');

    //     MealType mealType = Meal::stringToMealType(mealtypeStr);
    //     ReserveDay reserveDay = Meal::stringToReserveDay(reservedayStr);

    //     Meal m(mealID, name, price, mealType, reserveDay);
    //     meals.push_back(m);
    // }
    nlohmann::json j;
    file >> j;
    file.close();
    vector<Meal> meals = j.get<std::vector<Meal>>();  // دی‌سریالایز کل لیست
    // چاپ همه غذاها
    cout << "=== All Meals ===" << endl << endl;
    int line = 2; // خط شروع
    for (const auto& m : meals) 
    {
        m.print(line);  // فرض می‌کنیم متد print() داخل کلاس Meal چاپ مناسب انجام میده
        line += 8; // هر سالن حدود 7 خط طول میکشه
    }
}

void AdminPanel::displayAllDininigHalls()
{
    string diningHallsFile = "diningHalls.json"; // مسیر فایل CSV
    ifstream file(diningHallsFile);

    if (!file.is_open()) 
    {
        cerr << "Cannot open dining halls json file." << endl;
        return;
    }

    // vector<DiningHall> halls;
    // string line;

    // // خواندن هدر
    // getline(file, line);

    // // خواندن هر خط و ساخت آبجکت DiningHall
    // while (getline(file, line)) 
    // {
    //     stringstream ss(line);
    //     string field;
    //     int hallID, capacity;
    //     string name, genderStr, address;

    //     getline(ss, field, ',');
    //     hallID = stoi(field);

    //     getline(ss, name, ',');

    //     getline(ss, genderStr, ','); // اینجا می‌تونیم بعداً استفاده کنیم یا نادیده بگیریم

    //     getline(ss, address, ',');

    //     getline(ss, field, ',');
    //     capacity = stoi(field);

    //     Gender gender = DiningHall::stringToGender(genderStr);

    //     DiningHall hall(hallID, name, address, capacity);
    //     halls.push_back(hall);
    // }

    nlohmann::json j;
    file >> j;
    file.close();
    vector<DiningHall> halls = j.get<std::vector<DiningHall>>();
    // نمایش همه سالن‌ها با متد print
    cout << "=== All Dining Halls ===" << endl << endl;
    int line = 2; // خط شروع
    for (const auto& hall : halls) 
    {
        hall.print(line);
        line += 7; // هر سالن حدود 7 خط طول میکشه
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
    cout << "\nMeals added to json file successfully!\n";
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
    inFile.close();
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
    cout << "Dining hall added to json file successfully!\n";
}

void AdminPanel::removeMeal(int mealIDToRemove)
{
    // string csvFile = "mealsCsvFile.json";
    // string tempFile = "temp.json";

    // ifstream inFile(csvFile);
    // ofstream outFile(tempFile);

    // if(!inFile.is_open() || !outFile.is_open())
    // {
    //     cerr << "Cannot open meals CSV file." << endl;
    //     return;
    // }

    // string line;
    // bool removed = false;

    // // خواندن هدر و نوشتن در فایل موقت
    // if(getline(inFile, line)) 
    // {
    //     outFile << line << endl;
    // }

    // // خواندن هر خط و فیلتر کردن
    // while(getline(inFile, line))
    // {
    //     stringstream ss(line);
    //     string field;
    //     getline(ss, field, ',');
    //     int id = stoi(field);

    //     if (id != mealIDToRemove) 
    //     {
    //         outFile << line << endl; // فقط غذاهای غیر از mealID مورد نظر ذخیره میشن
    //     }   else {
    //         removed = true;
    //     }
    // }

    // inFile.close();
    // outFile.close();

    // // جایگزینی فایل اصلی با فایل موقت
    // if(removed)
    // {
    //     remove(csvFile.c_str());
    //     rename(tempFile.c_str(), csvFile.c_str());
    //     cout << "Meal with ID " << mealIDToRemove << " removed successfully.\n";
    // } 
    // else
    // {
    //     remove(tempFile.c_str());
    //     cout << "Meal with ID " << mealIDToRemove << " not found.\n";
    // }
    string mealsFile = "meals.json";

    // خواندن لیست غذاها از فایل JSON
    ifstream inFile(mealsFile);
    if (!inFile.is_open())
    {
        cerr << "Cannot open meals.json file." << endl;
        return;
    }

    json j;
    inFile >> j;
    inFile.close();

    vector<Meal> meals = j.get<vector<Meal>>();

    // پیدا کردن و حذف غذا
    auto it = remove_if(meals.begin(), meals.end(),
                        [mealIDToRemove](const Meal& m) { return m.getMeal_id() == mealIDToRemove; });

    if (it != meals.end())
    {
        meals.erase(it, meals.end());

        // ذخیره لیست جدید در فایل
        ofstream outFile(mealsFile);
        outFile << json(meals).dump(4);  // دوباره serialize
        outFile.close();

        cout << "Meal with ID " << mealIDToRemove << " removed successfully.\n";
    }
    else
    {
        cout << "Meal with ID " << mealIDToRemove << " not found.\n";
    }
}

void AdminPanel::removeDiningHall(int hallIDToRemove)
{
    // string csvFile = "../diningHallsCsvFile.csv";
    // string tempFile = "../temp.csv";

    // ifstream inFile(csvFile);
    // ofstream outFile(tempFile);

    // if(!inFile.is_open() || !outFile.is_open()) 
    // {
    //     cerr << "Cannot open dining halls CSV file." << endl;
    //     return;
    // }

    // string line;
    // bool removed = false;

    // // خواندن هدر و نوشتن در فایل موقت
    // if(getline(inFile, line))
    // {
    //     outFile << line << endl;
    // }

    // // خواندن هر خط و فیلتر کردن بر اساس hallID
    // while(getline(inFile, line))
    // {
    //     stringstream ss(line);
    //     string field;
    //     getline(ss, field, ',');
    //     int id = stoi(field);

    //     if (id != hallIDToRemove) 
    //     {
    //         outFile << line << endl; // فقط سالن‌های غیر از hallID مورد نظر ذخیره میشن
    //     } 
    //     else 
    //     {
    //         removed = true;
    //     }
    // }

    // inFile.close();
    // outFile.close();

    // // جایگزینی فایل اصلی با فایل موقت
    // if(removed)
    // {
    //     remove(csvFile.c_str());
    //     rename(tempFile.c_str(), csvFile.c_str());
    //     cout << "Dining hall with ID " << hallIDToRemove << " removed successfully.\n";
    // } 
    // else 
    // {
    //     remove(tempFile.c_str());
    //     cout << "Dining hall with ID " << hallIDToRemove << " not found.\n";
    // }
    string DiningHallsjson = "diningHalls.json";

    // خواندن لیست سالن‌ها از فایل JSON
    ifstream inFile(DiningHallsjson);
    if (!inFile.is_open())
    {
        cerr << "Cannot open diningHalls.json file." << endl;
        return;
    }

    json j;
    inFile >> j;
    inFile.close();

    vector<DiningHall> halls = j.get<vector<DiningHall>>();

    // پیدا کردن و حذف سالن
    auto it = remove_if(halls.begin(), halls.end(),
                        [hallIDToRemove](const DiningHall& h) { return h.getHallId() == hallIDToRemove; });

    if (it != halls.end())
    {
        halls.erase(it, halls.end());

        // ذخیره لیست جدید در فایل
        ofstream outFile(DiningHallsjson);
        outFile << json(halls).dump(4);  // serialize دوباره
        outFile.close();

        cout << "Dining hall with ID " << hallIDToRemove << " removed successfully.\n";
    }
    else
    {
        cout << "Dining hall with ID " << hallIDToRemove << " not found.\n";
    }
}

bool AdminPanel::showMenu()
{
    const int startX = 10;   // شروع ستون منو
    const int startY = 2;    // شروع سطر منو
    const int width = 40;    // عرض منو
    const int height = 20;   // ارتفاع منو
    // bool sw_MainMenu = false;
    char choice;

    // رسم بالای منو
    gotoxy(startX, startY);
    cout << "+"; 
    for(int i=0; i<width; i++) cout << "-";
    cout << "+";

    // فضای داخلی منو
    for(int i=1; i<height-1; i++)
    {
        gotoxy(startX, startY+i);
        cout << "|";
        for(int j=0; j<width; j++) cout << " ";
        cout << "|";
    }

    // رسم پایین منو
    gotoxy(startX, startY+height-1);
    cout << "+";
    for(int i=0; i<width; i++) cout << "-";
    cout << "+";

    // عنوان منو
    gotoxy(startX+5, startY+1);
    cout << "Admin Menu --- Feeding Automation";

    // گزینه‌ها
    gotoxy(startX+5, startY+3);  cout << "1 - Display all meals";
    gotoxy(startX+5, startY+5);  cout << "2 - Display all diningHalls";
    gotoxy(startX+5, startY+7);  cout << "3 - Add meal";
    gotoxy(startX+5, startY+9);  cout << "4 - Add diningHall";
    gotoxy(startX+5, startY+11); cout << "5 - Remove meal";
    gotoxy(startX+5, startY+13); cout << "6 - Remove diningHall";
    gotoxy(startX+5, startY+15); cout << "7 - Exit";

    gotoxy(startX+5, startY+17);
    cout << "Enter your choice (1-7): ";

    while(true)
    {
        if(kbhit())
        {
            choice = getch();
            if(choice >= '1' && choice <= '7')
            {
                system("cls");
                if(choice == '7') // یعنی Exit
                {
                    return false;  // 🔙 برگرد به منوی اصلی
                }
                else
                {
                    action(choice);
                    drawBox(83, 22, 35, 3);
                    gotoxy(85, 23);
                    cout << "Press Enter to return to menu...";
                    getch();
                    // if (cin.peek() == '\n') 
                    // {  
                    //     cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    // }
                    // cin.get();
                    return true; // ادامه بده (منو رو دوباره نشون بده)
                    // sw_MainMenu = true;
                }
            }
            else
            {
                gotoxy(startX+5, startY+19);
                cout << "Invalid input! Please enter 1-7.";
            }
        }
    }
}

void AdminPanel::action(char character)
{
    switch(character)
    {
        case '1':
            displayAllMeals();
            break;
        case '2':
            displayAllDininigHalls();
            break;
        case '3':
            addNewMealIntractive();
            break;
        case '4':
            addNewDiningHallIntractive();
            break;
        case '5':
            int ID1;
            cout << "Which meal do you want to remove? please enter its ID: ";
            cin >> ID1;
            removeMeal(ID1);
            break;
        case '6':
            int ID2;
            cout << "Which diningHall do you want to remove? please enter its ID: ";
            cin >> ID2;
            removeDiningHall(ID2);
            break;
        case '7':
            cout << "Bye Bye!!!  ";
            break;
        default:
            cout << "You have selected an out-of-range option.";
    }
}
