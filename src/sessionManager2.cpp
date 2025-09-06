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
#include "bcrypt.h"
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
    fs::path sessionFile = ConfigPaths::instance().getAdminSessionsDir() / ("Admin_" + adminPho + ".json");
    ifstream file(sessionFile);
    if (!file.is_open()) 
    {
        adminLogger.addLog("Failed to open session file for admin " + adminPho, "ERROR");
        throw runtime_error("Cannot open admin session file.");
    }
    json j;
    file >> j;
    file.close();
    string storedHashedPass = j["hashpassword"];
    if (!bcrypt::validatePassword(password, storedHashedPass)) 
    {
        adminLogger.addLog("Failed login attempt (incorrect password) for admin " + adminPho, "WARNING");
        throw runtime_error("Incorrect admin password.");
    }
    if (_currentAdmin == nullptr)
    {
        _currentAdmin = new Admin();  // یا هر سازنده مناسب
    }
    *_currentAdmin = j;
    _adminID = _currentAdmin->getUserID();
    adminLogger.addLog("Session loaded successfully for admin " + adminPho, "INFO");
    msgBox.addMessage("Session loaded successfully.", MsgColor::GREEN);
    msgBox.showMessages();
    system("pause");
    msgBox.clear();
}

void AdminSession::SessionManager::save_session(string& adminPho, const string& password)
{
    fs::path path = ConfigPaths::instance().getAdminSessionsDir() / ("Admin_" + adminPho + ".json");
    json j = *_currentAdmin;
    ofstream out(path);
    if (!out.is_open()) 
    {
        adminLogger.addLog("Cannot open admin session file for writing (ID: " + to_string(_adminID) + ")", "ERROR");
        throw std::runtime_error("Cannot open admin session file for writing.");
    }
    adminLogger.addLog("Admin session saved (ID: " + to_string(_adminID) + ")", "INFO");
    out << j.dump(4); // 4 = فاصله برای خوانایی بیشتر
}

void AdminSession::SessionManager::login(string adminPho, string password)
{
    auto& msgBox = ConsoleMessageBox::instance();
    msgBox.setPosition(7, 20, 100, 5);
    fs::path adminSessionsDir = ConfigPaths::instance().getAdminSessionsDir();
    if (!Admin::isThereAnyAdmin()) 
    {
        try 
        {
            fs::create_directories(adminSessionsDir);
            adminLogger.addLog("Session directory created successfully for admin: " + adminPho, "INFO");
        }
        catch (const fs::filesystem_error& e) 
        {
            adminLogger.addLog("Error creating admin sessions directory: " + string(e.what()), "ERROR");
            msgBox.addMessage("Error creating directory: " + string(e.what()), MsgColor::RED);
            msgBox.showMessages();
            system("pause");
            msgBox.clear();
            throw;
        }
        msgBox.addMessage("No admin found. Registering first admin...", MsgColor::GREEN);
        msgBox.showMessages();
        system("pause");
        msgBox.clear();
        adminLogger.addLog("No admin found, registering first admin (" + adminPho + ")", "INFO");
        Admin::sign_in(adminPho, password);
        adminLogger.addLog("First admin registered successfully", "INFO");
        msgBox.addMessage("First admin registered successfully.", MsgColor::GREEN);
        msgBox.showMessages();
        system("pause");
        msgBox.clear();
    }
    else
    {
        // اگر ادمین وجود داشت، مسیر فایل سشن ادمین مربوط به username
        fs::path sessionFile = adminSessionsDir / ("Admin_" + adminPho + ".json");
        if (!fs::exists(sessionFile))
        {
            adminLogger.addLog("Admin session file not found for " + adminPho, "WARNING");
            throw std::runtime_error("Admin session file not found.");
        }
        // اگر فایل بود، بارگذاری سشن و چک کردن پسورد
        load_session(adminPho, password);
        adminLogger.addLog("Admin " + adminPho + " logged in successfully", "INFO");
        msgBox.addMessage("Admin login successfully.", MsgColor::GREEN);
        msgBox.showMessages();
        system("pause");
        msgBox.clear();
    }
}

void AdminSession::SessionManager::logout(string adminPho, string password)
{
    auto& msgBox = ConsoleMessageBox::instance();
    msgBox.setPosition(7, 20, 100, 5);
    if (_currentAdmin == nullptr) 
    {
        adminLogger.addLog("Logout attempt with no active admin session", "WARNING");
        msgBox.addMessage("No admin is currently logged in.", MsgColor::GREEN);
        msgBox.showMessages();
        system("pause");
        msgBox.clear();
        return;
    }
    fs::path sessionFile = ConfigPaths::instance().getAdminSessionsDir() / ("Admin_" + adminPho + ".json");
    if (fs::exists(sessionFile)) 
    {
        fs::remove(sessionFile);
    }
    adminLogger.addLog("Admin " + adminPho + " logged out", "INFO");
    delete _currentAdmin;
    _currentAdmin = nullptr;
    _adminID = 0;
    msgBox.addMessage("Admin logged out successfully.", MsgColor::GREEN);
    msgBox.showMessages();
    system("pause");
    msgBox.clear();
}
