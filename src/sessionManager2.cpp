#include <iostream>
#include <fstream>
#include <sstream>
#include <filesystem>
#include "sessionBase.hpp"
#include "sessionManager2.hpp"
#include "admin.hpp"
#include "logsystem.hpp"
#include "configPaths.hpp"
#include "json.hpp"
#include "../Bcrypt.cpp/include/bcrypt.h"
using namespace std;
using namespace AdminSession;
using json = nlohmann::json;

AdminSession::SessionManager::SessionManager(Admin a, int i)
{
    _currentAdmin = &a;
    _adminID = i;
}
Admin SessionManager::currentAdmin()
{
    return *_currentAdmin;
}
void AdminSession::SessionManager::setCurrentAdmin(Admin *a, int i)
{
    _currentAdmin = a;
    _adminID = i;
}

const string l_admins_log_file = "../logs/admin.log";

void SessionManager::load_session(string& studentNumber, const string& password)
{
    LogSystem logger(l_admins_log_file);

    fs::path sessionFile = ConfigPaths::instance().getAdminSessionsDir() / ("Admin_" + studentNumber + ".json");
    
    ifstream file(sessionFile);
    if (!file.is_open()) 
    {
        logger.addLog("Failed to open session file for admin " + studentNumber, "ERROR");
        throw runtime_error("Cannot open admin session file.");
    }

    json j;
    file >> j;
    file.close();

    string storedHashedPass = j["hashedPassword"];
    if (!bcrypt::validatePassword(password, storedHashedPass)) 
    {
        logger.addLog("Failed login attempt (incorrect password) for admin " + studentNumber, "WARNING");
        throw runtime_error("Incorrect admin password.");
    }

    int userID = j["userID"];
    string firstName = j["firstName"];
    string lastName = j["lastName"];
    string storedHashedPassword = j["hashedPassword"];
    string phone = j["phone"];

    _currentAdmin = new Admin(userID, firstName, lastName, password, phone);
    //Admin* _currentAdmin;
    _adminID = userID;
    logger.addLog("Session loaded successfully for admin " + studentNumber, "INFO");
    cout << "Session loaded successfully." << endl;
}

void SessionManager::save_session(string& studentNumber, const string& password)
{
    LogSystem logger(l_admins_log_file);

    fs::path path = ConfigPaths::instance().getAdminSessionsDir() / ("Admin_" + studentNumber + ".json");
    string hashedPassword = bcrypt::generateHash(_currentAdmin->getHashedPasssword());    
    json j;
    j["userID"] = _adminID;
    j["firstName"] = _currentAdmin->getName();
    j["lastName"] = _currentAdmin->getLastName();
    j["hashedPassword"] = hashedPassword;  
    j["phone"] = _currentAdmin->getPhone();
    
    ofstream out(path);
    if (!out.is_open()) 
    {
        logger.addLog("Cannot open admin session file for writing (ID: " + to_string(_adminID) + ")", "ERROR");
        throw std::runtime_error("Cannot open admin session file for writing.");
    }

    logger.addLog("Admin session saved (ID: " + to_string(_adminID) + ")", "INFO");
    out << j.dump(4); // 4 = فاصله برای خوانایی بیشتر
}

void SessionManager::login(string studentNumber, string password)
{
    LogSystem logger(l_admins_log_file);

    fs::path adminSessionsDir = ConfigPaths::instance().getAdminSessionsDir();
    fs::path existAdminSessionDir = ConfigPaths::instance().getAdminSessionsDir();
    if (!fs::exists(existAdminSessionDir)) 
    {
        try 
        {
            fs::create_directories(existAdminSessionDir);
            LogSystem logger(l_admins_log_file);
            cout << "Session directory created: " << existAdminSessionDir << endl;
        }
        catch (const fs::filesystem_error& e) 
        {
            logger.addLog("Error creating admin sessions directory: " + string(e.what()), "ERROR");
            cerr << "Error creating directory: " << e.what() << endl;
            throw;
        }
    }
    if (!Admin::isThereAnyAdmin()) 
    {
        cout << "No admin found. Registering first admin..." << endl;
        logger.addLog("No admin found, registering first admin (" + studentNumber + ")", "INFO");
        Admin::sign_in(studentNumber, password);
        logger.addLog("First admin registered successfully", "INFO");
        cout << "First admin registered successfully." << endl;
        return;
    }

    // اگر ادمین وجود داشت، مسیر فایل سشن ادمین مربوط به username
    fs::path sessionFile = adminSessionsDir / ("Admin_" + studentNumber + ".json");

    if (!fs::exists(sessionFile))
    {
        logger.addLog("Admin session file not found for " + studentNumber, "WARNING");
        throw std::runtime_error("Admin session file not found.");
    }

    // اگر فایل بود، بارگذاری سشن و چک کردن پسورد
    load_session(studentNumber, password);
    logger.addLog("Admin " + studentNumber + " logged in successfully", "INFO");
    std::cout << "Admin login successful." << std::endl;
}

void SessionManager::logout(string studentNumber, string password)
{
    LogSystem logger(l_admins_log_file);

    if (_currentAdmin == nullptr) 
    {
        logger.addLog("Logout attempt with no active admin session", "WARNING");
        cout << "No admin is currently logged in." << endl;
        return;
    }

    fs::path sessionFile = ConfigPaths::instance().getAdminSessionsDir() / ("Admin_" + studentNumber + ".json");
    if (fs::exists(sessionFile)) 
    {
        fs::remove(sessionFile);
    }
        
    logger.addLog("Admin " + studentNumber + " logged out", "INFO");

    delete _currentAdmin;
    _currentAdmin = nullptr;
    _adminID = 0;

    cout << "Admin logged out successfully." << endl;
}
