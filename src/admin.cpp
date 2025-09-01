#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#include <iostream>
#include <fstream>
#include "admin.hpp"
#include "user.hpp"
#include "sessionManager2.hpp"
#include "configPaths.hpp"
#include "json.hpp"
#include "utils.hpp"
#include "windows.h"
#include "bcrypt.h"
#include "consoleMessageBox.hpp"

using namespace std;
using json = nlohmann::json;

Admin::Admin(int user_id, string first_name, string last_name, string hashedPasssword, string phone) 
: User(user_id, first_name, last_name, hashedPasssword, phone) 
{
    
}

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

void Admin::sign_in(string& adminPho, string& password)
{
    auto& msgBox = ConsoleMessageBox::instance();
    msgBox.setPosition(7, 20, 100, 5);
    string userID, firstName, lastName, hashedPassword;
    drawBox(10, 3, 56, 10);
    gotoxy(12, 5);
    cout << "*to complete your sign_in complete these information*";
    gotoxy(13, 8);
    cout << "Name: ";
    cin >> firstName;
    gotoxy(13, 10);
    cout << "Last Name: ";
    cin >> lastName;
    gotoxy(20, 20);
    auto& adminSession = AdminSession::SessionManager::instance();
    int adminID = 0;
    hashedPassword = bcrypt::generateHash(password);
    Admin *currentAdmin = new Admin(adminID, firstName, lastName, hashedPassword, adminPho);
    //int adminID = adminID;
    adminSession.setCurrentAdmin(currentAdmin, adminID);
    adminSession.save_session(adminPho, password);
    // msgBox.addMessage("Admin registered successfully.", MsgColor::GREEN);
    // msgBox.showMessages();
    // system("pause");
    // msgBox.clear();
    // cout << "Admin registered successfully." << endl;
}

void Admin::print()const
{
        User::print();
}

string Admin::getType()
{
    return "Admin";
}