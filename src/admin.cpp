#include <iostream>
#include <fstream>
#include "../include/admin.hpp"
#include "../include/sessionManager2.hpp"
#include <configPaths.hpp>
#include "json.hpp"
#include "../Bcrypt.cpp/include/bcrypt.h"
using namespace std;
using json = nlohmann::json;

Admin::Admin(int user_id, string first_name, string last_name, string Passsword, string phone) 
: User(user_id, first_name, last_name, Passsword, phone) {}

bool Admin::isThereAnyAdmin()
{   
    // 1. مسیر پوشه‌ای که سشن ادمین‌ها توش ذخیره شده رو می‌گیریم
    fs::path adminSessionsDir = ConfigPaths::instance().getAdminSessionsDir();

    // 2. چک می‌کنیم آیا این مسیر وجود داره و واقعاً یه دایرکتوری هست
    if (!fs::exists(adminSessionsDir) || !fs::is_directory(adminSessionsDir))
        return false;  // اگه وجود نداشت یا دایرکتوری نبود، یعنی ادمینی نیست

    // 3. داخل پوشه می‌گردیم ببینیم حداقل یه فایل با پسوند .json هست یا نه
    for (const auto& entry : fs::directory_iterator(adminSessionsDir))
    {
        // 4. اگر فایل با پسوند .json پیدا کردیم، فرض می‌کنیم ادمینی هست
        if (entry.path().extension() == ".json")
        {
            return true;
        }
    }

    // 5. اگر هیچ فایل .json پیدا نشد، ادمینی وجود نداره
    return false;
}

bool Admin::sign_in()
{
    return !isThereAnyAdmin();
}

void SessionManager::register_admin(string& studentNumber, string& password)
{
    fs::path csvPath = ConfigPaths::instance().getStudentsCsv();
    ifstream file(csvPath);
    if (!file.is_open())
    {
        throw std::runtime_error("Cannot open students CSV file.");
    }

    string line;
    bool found = false;
    while (getline(file, line))
    {
        stringstream ss(line);
        string userIDStr, firstName, lastName, studentID, hashedPassword, email, phone;

        getline(ss, userIDStr, ',');
        getline(ss, firstName, ',');
        getline(ss, lastName, ',');
        getline(ss, studentID, ',');
        getline(ss, hashedPassword, ',');
        getline(ss, email, ',');
        getline(ss, phone, ',');

        if (studentID == studentNumber)
        {
            found = true;
            if (!bcrypt::validatePassword(password, hashedPassword))
            {
                throw runtime_error("Incorrect password.");
            }

            int adminID = stoi(userIDStr);

            _currentAdmin = new Admin(adminID, firstName, lastName, password, phone);
            _adminID = adminID;

            save_session();

            cout << "Admin registered successfully." << endl;
            break;
        
        }
    }

    if (!found)
    {
        throw runtime_error("Student ID not found in records.");
    }
}

void Admin::print()const
{
        User::print();
}

string Admin::getType()
{
    return "Admin";
}