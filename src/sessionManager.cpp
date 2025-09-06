#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#include <iostream>
#include <fstream>
#include <filesystem>
#include <string>
#include "student.hpp"
#include "sessionBase.hpp"
#include "sessionManager.hpp"
#include "logsystem.hpp"
#include "configPaths.hpp"
#include "json.hpp"
#include "windows.h"
#include "bcrypt.h"
#include "consoleMessageBox.hpp"

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

void StudentSession::SessionManager::setCurrentStudent(Student* student)
{
    _currentStudent = student;
}

void StudentSession::SessionManager::setShoppingCart(ShoppingCart* shopping_cart)
{
    _shopping_cart = shopping_cart;
}

void StudentSession::SessionManager::setStudentID(string studentID)
{
    _studentID = studentID;
}

void StudentSession::SessionManager::load_session(string& studentNumber, const string& password)
{
    auto& msgBox = ConsoleMessageBox::instance();
    msgBox.setPosition(7, 20, 100, 5);
    LogSystem logger(ConfigPaths::instance().getStudentsLogFile().string());
    fs::path sessionFile = ConfigPaths::instance().getStudentSessionsDir() / ("Student_" + studentNumber + ".json");
    if (!fs::exists(sessionFile))
    {
        logger.addLog("Session file not found for student " + studentNumber, "ERROR");
        throw runtime_error("Cannot open session file.");
    }
    ifstream file(sessionFile);
    if (!file.is_open())
    {
        logger.addLog("Failed to open session file for student " + studentNumber, "ERROR");
        throw runtime_error("Cannot open session file.");
    }
    json j;
    file >> j;
    file.close();
    string storedHashedPass = j["hashpassword"];
    if (!bcrypt::validatePassword(password, storedHashedPass))
    {
        logger.addLog("Failed login attempt (incorrect password) for student " + studentNumber, "WARNING");
        throw runtime_error("Incorrect password.");
    }
    // پاک کردن شی قبلی اگر وجود داشته باشه
    delete _currentStudent;
    _currentStudent = new Student();
    // بارگذاری از JSON با adl_serializer
    // nlohmann::adl_serializer<Student>::from_json(j, *_currentStudent);
    *_currentStudent = j;
    // پاک کردن shopping cart قبلی و ایجاد جدید
    delete _shopping_cart;
    _shopping_cart = new ShoppingCart();
    // ست کردن شناسه دانشجو
    _studentID = _currentStudent->getStudentId();

    logger.addLog("Session loaded successfully for student " + studentNumber, "INFO");
    msgBox.addMessage("Session loaded successfully.", MsgColor::GREEN);
    msgBox.showMessages();
    system("pause");
    msgBox.clear();
}

void StudentSession::SessionManager::save_session(string& studentNumber, const string& password )
{
    LogSystem logger(ConfigPaths::instance().getStudentsLogFile().string());
    fs::path path = ConfigPaths::instance().getStudentSessionsDir() / ( "Student_" + _studentID + ".json");
    json j = *_currentStudent;
    ofstream out(path);
    if (!out.is_open()) 
    {
        logger.addLog("Cannot open student session file for writing (ID: " + _studentID + ")", "ERROR");
        throw std::runtime_error("Cannot open student session file for writing.");
    }
    logger.addLog("Student session saved (ID: " + _studentID + ")", "INFO");
    out << j.dump(4);
    out.close();
}

void StudentSession::SessionManager::login(string studentNumber, string password)
{
    auto& msgBox = ConsoleMessageBox::instance();
    msgBox.setPosition(7, 20, 100, 5);
    LogSystem logger(ConfigPaths::instance().getStudentsLogFile().string());
    // فرض: _studentID و پسورد هش شده در این کلاس ست شده اند
    fs::path sessionFile = ConfigPaths::instance().getStudentSessionsDir() / ("Student_" + studentNumber + ".json");
    fs::path existStudentSessionDir = ConfigPaths::instance().getStudentSessionsDir();
    if (!fs::exists(existStudentSessionDir)) 
    {
        try 
        {
            fs::create_directories(existStudentSessionDir);
            msgBox.addMessage("Session directory created: ", MsgColor::GREEN);
            msgBox.showMessages();
            system("pause");
            msgBox.clear();
        }
        catch (const fs::filesystem_error& e) 
        {
            msgBox.addMessage("Error creating directory: " + string(e.what()), MsgColor::RED);
            msgBox.showMessages();
            system("pause");
            msgBox.clear();
            throw;
        }
    }
    if (fs::exists(sessionFile))
    {
        load_session(studentNumber, password);
        logger.addLog("Session loaded successfully for student " + studentNumber, "INFO");
        msgBox.addMessage("Student login successfully.", MsgColor::GREEN);
        msgBox.showMessages();
        system("pause");
        msgBox.clear();
    }
    else
    {
        fs::path csvPath = ConfigPaths::instance().getStudentsCsv();
        ifstream file(csvPath);
        if(!file.is_open()) 
        {
            logger.addLog("Cannot open students CSV file", "ERROR");
            throw runtime_error("Cannot open students CSV file.");
        }
        string line;
        bool found = false;
        while(getline(file, line))
        {
            stringstream ss(line);
            string userID, firstName, lastName, studentID, hashedPassword, email, phone;

            getline(ss, userID, ',');
            getline(ss, studentID, ',');
            getline(ss, firstName, ',');
            getline(ss, lastName, ',');
            getline(ss, hashedPassword, ',');
            getline(ss, email, ',');
            getline(ss, phone, ',');

            if (studentID == studentNumber)
            {
                found = true;
                // string pass = password;
                if(!bcrypt::validatePassword(password, hashedPassword))
                {
                    logger.addLog("Failed login attempt (incorrect password) for student " + studentNumber, "WARNING");
                    throw runtime_error("Incorrect password.");
                }
                else
                {
                    int _userID = stoi(userID);
                    _studentID = studentID;
                    _currentStudent = new Student(_userID, firstName, lastName, hashedPassword, phone, studentID, email, 0.0, true);
                    _shopping_cart = new ShoppingCart();


                    save_session(studentNumber, password);
                    logger.addLog("Student " + studentID + " logged in successfully", "INFO");
                    msgBox.addMessage("Login successful.", MsgColor::GREEN);
                    msgBox.showMessages();
                    system("pause");
                    msgBox.clear();
                    break;
                }
            }
        }
        if(!found) 
        {
            logger.addLog("Login attempt for non-existing student " + studentNumber, "WARNING");
            throw runtime_error("Student ID not found.");
        }
    }
}

void StudentSession::SessionManager::logout(string studentNumber, string password)
{
    auto& msgBox = ConsoleMessageBox::instance();
    msgBox.setPosition(7, 20, 100, 5);
    LogSystem logger(ConfigPaths::instance().getStudentsLogFile().string());
    // پاک کردن شی دانشجو و سبد خرید (اگر داینامیک ساختی)
    delete _currentStudent;
    _currentStudent = nullptr;

    delete _shopping_cart;
    _shopping_cart = nullptr;
    string studentID = _studentID;
    _studentID = "";
    // حذف فایل سشن مربوط به این دانشجو
    fs::path path = ConfigPaths::instance().getStudentSessionsDir()
                    / ("Student_" + studentID + ".json");
    if (fs::exists(path))
    {
        fs::remove(path);
    }
    logger.addLog("Student " + studentID + " logged out", "INFO");
    msgBox.addMessage("Admin logged out successfully.", MsgColor::GREEN);
    msgBox.showMessages();
    system("pause");
    msgBox.clear();

}

SessionManager& StudentSession::SessionManager::instance()
{
    static SessionManager instance;
    return instance;
}