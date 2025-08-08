#include <iostream>
#include <fstream>
#include <filesystem>
#include <string>
#include "student.hpp"
#include "sessionBase.hpp"
#include "sessionManager.hpp"
#include <configPaths.hpp>
#include "json.hpp"
#include "../Bcrypt.cpp/include/bcrypt.h"
using namespace std;
namespace fs = std::filesystem;
using json = nlohmann::json;
using namespace StudentSession;

SessionManager::SessionManager()
{
   _currentStudent = nullptr;
   _shopping_cart = nullptr;
   _studentID = "";
}
void SessionManager::load_session(string& studentNumber, const string& password)
{
    //بررسی پسوورد
    string storedHashedPass = j["hashpassword"];
    if (!bcrypt::validatePassword(password, storedHashedPass))
    {
        throw runtime_error("Incorrect password.");
    }
    else
    {
        // فرض: _studentID و پسورد هش شده در این کلاس ست شده اند
        fs::path sessionFile = ConfigPaths::instance().getStudentSessionsDir() / ("Student_" + studentNumber + ".json");
        // باز کردن فایل و خواندن json
        ifstream file(sessionFile);
        if (!file.is_open())
        {
            throw runtime_error("Cannot open session file.");
        }
        json j;
        file >> j;
        file.close();
        // استخراج داده‌ها از JSON
        int userID = j["userID"];
        string firstName = j["firstName"];
        string lastName = j["lastName"];
        string storedHashedPassword = j["hashedPassword"];
        string email = j["email"];
        string phone = j["phone"];
        string studentID = j["studentID"];
        // ساخت شی Student و اختصاص به _currentStudent
        _currentStudent = new Student(userID, firstName, lastName, password, phone, studentID, email, 0, true);
        // ایجاد یک shopping cart جدید
        _shopping_cart = new ShoppingCart();
        _studentID = studentID;
        cout << "Session loaded successfully." << endl;
    }    
}
void SessionManager::save_session()
{
    fs::path path = ConfigPaths::instance().getStudentSessionsDir() / ( "Student_" + _studentID + ".json");
    json j;
    j["userID"] = to_string(_currentStudent->getUserID());
    j["studentID"] = _studentID;
    j["name"] = _currentStudent->getName();
    j["lastname"] = _currentStudent->getLastName();
    j["hashpassword"] = _currentStudent->getPasssword();
    j["email"] = _currentStudent->getEmail();
    j["phone"] = _currentStudent->getPhone();
    ofstream out(path);
    out << j.dump(4);
}

void SessionManager::login(string studentNumber, string password)
{
    // فرض: _studentID و پسورد هش شده در این کلاس ست شده اند
    fs::path sessionFile = ConfigPaths::instance().getStudentSessionsDir() / ("Student_" + studentNumber + ".json");

    if (fs::exists(sessionFile))
    {
        load_session(studentNumber, password);
    }
    else
    {
        fs::path csvPath = ConfigPaths::instance().getStudentsCsv();
        ifstream file(csvPath);
        if(!file.is_open()) 
        {
            throw runtime_error("Cannot open students CSV file.");
        }
        string line;
        bool found = false;
        while(getline(file, line))
        {
            stringstream ss(line);
            string userID, firstName, lastName, studentID, hashedPassword, email, phone;

            getline(ss, userID, ',');
            getline(ss, firstName, ',');
            getline(ss, lastName, ',');
            getline(ss, studentID, ',');
            getline(ss, hashedPassword, ',');
            getline(ss, email, ',');
            getline(ss, phone, ',');

            if (studentID == studentNumber)
            {
                found = true;
                string pass = password;
                if(!bcrypt::validatePassword(password, hashedPassword))
                {
                    throw runtime_error("Incorrect password.");
                }
                else
                {
                    int _userID = stoi(userID);
                    _studentID = studentID;
                    _currentStudent = new Student(_userID, firstName, lastName, password, phone, studentID, email, 0, true);
                    _shopping_cart = new ShoppingCart();


                    save_session();
                    cout << "Login successful." << endl;
                    break;
                }
            }
        }
        if(!found) 
        {
            throw runtime_error("Student ID not found.");
        }
    }
}
void SessionManager::logout()
{
    // پاک کردن شی دانشجو و سبد خرید (اگر داینامیک ساختی)
    delete _currentStudent;
    _currentStudent = nullptr;

    delete _shopping_cart;
    _shopping_cart = nullptr;

    _studentID = "";

    // حذف فایل سشن مربوط به این دانشجو
    fs::path path = ConfigPaths::instance().getStudentSessionsDir()
                    / ("Student_" + _studentID + ".json");

    if (fs::exists(path))
    {
        fs::remove(path);
    }
}

Student* SessionManager::currentStudent()
{
    return _currentStudent;
}
ShoppingCart* SessionManager::shoppingCart()
{
    return _shopping_cart;
}
SessionManager& SessionManager::instance()
{
    static SessionManager instance;
    return instance;
}