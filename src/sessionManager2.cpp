#include <iostream>
#include <fstream>
#include <filesystem>
#include "../include/sessionBase.hpp"
#include "../include/SessionManager2.hpp"
#include "../include/admin.hpp"
#include <configPaths.hpp>
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

void SessionManager::load_session(string& username, const string& password)
{
    fs::path sessionFile = ConfigPaths::instance().getAdminSessionsDir() / ("Admin_" + username + ".json");
    
    ifstream file(sessionFile);
    if (!file.is_open()) 
    {
        throw runtime_error("Cannot open admin session file.");
    }

    json j;
    file >> j;
    file.close();

    string storedHashedPass = j["hashedPassword"];
    if (!bcrypt::validatePassword(password, storedHashedPass)) 
    {
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
    cout << "Session loaded successfully." << endl;
}

void SessionManager::save_session()
{
    fs::path path = ConfigPaths::instance().getAdminSessionsDir() / ("Admin_" + to_string(_adminID) + ".json");
    string hashedPassword = bcrypt::generateHash(_currentAdmin->getPasssword());
    
    json j;
    j["userID"] = _adminID;
    j["firstName"] = _currentAdmin->getName();
    j["lastName"] = _currentAdmin->getLastName();
    j["hashedPassword"] = hashedPassword;  
    j["phone"] = _currentAdmin->getPhone();
    
    ofstream out(path);
    if (!out.is_open()) 
    {
        throw std::runtime_error("Cannot open admin session file for writing.");
    }
    out << j.dump(4); // 4 = فاصله برای خوانایی بیشتر
}