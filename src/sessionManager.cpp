#include <iostream>
#include <fstream>
#include <filesystem>
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
   
}
void SessionManager::load_session()
{

}
void SessionManager::save_session()
{
    fs::path path = ConfigPaths::instance().getStudentSessionsDir() / ( "Student_" + to_string(_studentID) + ".json");
    json j;
    j["first_name"] = _currentStudent->getName();
    j["last_name"] = _currentStudent->getLastName();
    j["student_id"] = _studentID;
    j["email"] = _currentStudent->getEmail();
    ofstream out(path);
    out << j.dump(4);
}
void SessionManager::login(string studentNumber, string password)
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
        int userID;
        string firstName, lastName, studentID, hashedPassword, email, phone;

        cin >> userID;
        cin.ignore();
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
            string hash = bcrypt::generateHash(password);
            if(hash == hashedPassword)
            {
                _studentID = stoi(studentID);
                _currentStudent = new Student(userID, firstName, lastName, password, studentID, email, 0, true);
                _shopping_cart = new ShoppingCart();

                save_session();
                cout << "Login successful." << endl;
                break;
            }
            else 
            {
                throw runtime_error("Incorrect password.");
            }
        }
    }
    if(!found) 
    {
        throw runtime_error("Student ID not found.");
    }
}
void SessionManager::logout()
{

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