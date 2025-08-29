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
#include "consoleMessageBox.hpp"

using namespace std;
using namespace AdminSession;
using json = nlohmann::json;

AdminSession::SessionManager::SessionManager()
{
    _currentAdmin = nullptr;
    _adminID = 0;
}
SessionManager& AdminSession::SessionManager::instance()
{
    static SessionManager instance;
    return instance;
}
Admin* AdminSession::SessionManager::currentAdmin()
{
    return _currentAdmin;
}
void AdminSession::SessionManager::setCurrentAdmin(Admin *a, int i)
{
    _currentAdmin = a;
    _adminID = i;
}

void AdminSession::SessionManager::load_session(string& adminPho, const string& password)
{
    auto& msgBox = ConsoleMessageBox::instance();
    msgBox.setPosition(7, 20, 100, 5);
    LogSystem logger(ConfigPaths::instance().getAdminsLogFile().string());
    fs::path sessionFile = ConfigPaths::instance().getAdminSessionsDir() / ("Admin_" + adminPho + ".json");
    
    ifstream file(sessionFile);
    if (!file.is_open()) 
    {
        logger.addLog("Failed to open session file for admin " + adminPho, "ERROR");
        throw runtime_error("Cannot open admin session file.");
    }

    json j;
    file >> j;
    file.close();

    string storedHashedPass = j["hashpassword"];
    if (!bcrypt::validatePassword(password, storedHashedPass)) 
    {
        logger.addLog("Failed login attempt (incorrect password) for admin " + adminPho, "WARNING");
        throw runtime_error("Incorrect admin password.");
    }

    // int userID = j["userID"];
    // string firstName = j["firstName"];
    // string lastName = j["lastName"];
    // string storedHashedPassword = j["hashedPassword"];
    // string phone = j["phone"];
    // _currentAdmin = new Admin(userID, firstName, lastName, password, phone);
    //Admin* _currentAdmin;
    if (_currentAdmin == nullptr)
    {
        _currentAdmin = new Admin();  // یا هر سازنده مناسب
    }

    *_currentAdmin = j;
    _adminID = _currentAdmin->getUserID();
    logger.addLog("Session loaded successfully for admin " + adminPho, "INFO");
    msgBox.addMessage("Session loaded successfully.", MsgColor::GREEN);
    msgBox.showMessages();
    system("pause");
    msgBox.clear();
    // cout << "Session loaded successfully." << endl;
}

void AdminSession::SessionManager::save_session(string& adminPho, const string& password)
{
    LogSystem logger(ConfigPaths::instance().getAdminsLogFile().string());

    fs::path path = ConfigPaths::instance().getAdminSessionsDir() / ("Admin_" + adminPho + ".json");
    // string hashedPassword = bcrypt::generateHash(_currentAdmin->getHashedPasssword());    
    // json j;
    // j["userID"] = _adminID;
    // j["firstName"] = _currentAdmin->getName();
    // j["lastName"] = _currentAdmin->getLastName();
    // j["hashedPassword"] = hashedPassword;  
    // j["phone"] = _currentAdmin->getPhone();
    json j = *_currentAdmin;
    ofstream out(path);
    if (!out.is_open()) 
    {
        logger.addLog("Cannot open admin session file for writing (ID: " + to_string(_adminID) + ")", "ERROR");
        throw std::runtime_error("Cannot open admin session file for writing.");
    }

    logger.addLog("Admin session saved (ID: " + to_string(_adminID) + ")", "INFO");
    out << j.dump(4); // 4 = فاصله برای خوانایی بیشتر
}

void AdminSession::SessionManager::login(string adminPho, string password)
{
    auto& msgBox = ConsoleMessageBox::instance();
    msgBox.setPosition(7, 20, 100, 5);
    LogSystem logger(ConfigPaths::instance().getAdminsLogFile().string());
    fs::path adminSessionsDir = ConfigPaths::instance().getAdminSessionsDir();
    // fs::path existAdminSessionDir = ConfigPaths::instance().getAdminSessionsDir();
    if (!Admin::isThereAnyAdmin()) 
    {
        try 
        {
            fs::create_directories(adminSessionsDir);
            logger.addLog("Session directory created successfully for admin: " + adminPho, "INFO");
            // cout << "Session directory created!!!" << adminSessionsDir << endl;
        }
        catch (const fs::filesystem_error& e) 
        {
            logger.addLog("Error creating admin sessions directory: " + string(e.what()), "ERROR");
            msgBox.addMessage("Error creating directory: " + string(e.what()), MsgColor::RED);
            msgBox.showMessages();
            system("pause");
            msgBox.clear();
            // cerr << "Error creating directory: " << e.what() << endl;
            throw;
        }
        msgBox.addMessage("No admin found. Registering first admin...", MsgColor::GREEN);
        msgBox.showMessages();
        system("pause");
        msgBox.clear();
        // cout << "No admin found. Registering first admin..." << endl;
        logger.addLog("No admin found, registering first admin (" + adminPho + ")", "INFO");
        Admin::sign_in(adminPho, password);
        logger.addLog("First admin registered successfully", "INFO");
        msgBox.addMessage("First admin registered successfully.", MsgColor::GREEN);
        msgBox.showMessages();
        system("pause");
        msgBox.clear();
        // cout << "First admin registered successfully." << endl;
        // return;
    }
    // if (!Admin::isThereAnyAdmin()) 
    // {
    //     cout << "No admin found. Registering first admin..." << endl;
    //     logger.addLog("No admin found, registering first admin (" + studentNumber + ")", "INFO");
    //     Admin::sign_in(studentNumber, password);
    //     logger.addLog("First admin registered successfully", "INFO");
    //     cout << "First admin registered successfully." << endl;
    //     return;
    // }

    else
    {
    // اگر ادمین وجود داشت، مسیر فایل سشن ادمین مربوط به username
        fs::path sessionFile = adminSessionsDir / ("Admin_" + adminPho + ".json");

        if (!fs::exists(sessionFile))
        {
            logger.addLog("Admin session file not found for " + adminPho, "WARNING");
            throw std::runtime_error("Admin session file not found.");
        }

        // اگر فایل بود، بارگذاری سشن و چک کردن پسورد
        load_session(adminPho, password);
        logger.addLog("Admin " + adminPho + " logged in successfully", "INFO");
        msgBox.addMessage("Admin login successfully.", MsgColor::GREEN);
        msgBox.showMessages();
        system("pause");
        msgBox.clear();
        // cout << "Admin login successful." << endl;
    }
}

void AdminSession::SessionManager::logout(string adminPho, string password)
{
    auto& msgBox = ConsoleMessageBox::instance();
    msgBox.setPosition(7, 20, 100, 5);
    LogSystem logger(ConfigPaths::instance().getAdminsLogFile().string());

    if (_currentAdmin == nullptr) 
    {
        logger.addLog("Logout attempt with no active admin session", "WARNING");
        msgBox.addMessage("No admin is currently logged in.", MsgColor::GREEN);
        msgBox.showMessages();
        system("pause");
        msgBox.clear();
        // cout << "No admin is currently logged in." << endl;
        return;
    }

    fs::path sessionFile = ConfigPaths::instance().getAdminSessionsDir() / ("Admin_" + adminPho + ".json");
    if (fs::exists(sessionFile)) 
    {
        fs::remove(sessionFile);
    }
        
    logger.addLog("Admin " + adminPho + " logged out", "INFO");

    delete _currentAdmin;
    _currentAdmin = nullptr;
    _adminID = 0;
    msgBox.addMessage("Admin logged out successfully.", MsgColor::GREEN);
    msgBox.showMessages();
    system("pause");
    msgBox.clear();
    // cout << "Admin logged out successfully." << endl;
}
