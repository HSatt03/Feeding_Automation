#include <iostream>
#include <string>
#include <algorithm>
#include <stdexcept>
#include "diningHall.hpp"

using namespace std;

ostream& operator<<(ostream& os, const Gender& gender)
{
    if(gender == Gender::MALE)
    {
        os << "Male";
    }
    else if(gender == Gender::FEMALE)
    {
        os << "Female";
    }
    else
    {
        os << "Female";
    }
    return os;
} 

DiningHall::DiningHall(int hall_id, string name, string address, int capacity)
{
    _hall_id = hall_id;
    _name = name;
    _address = address;
    _capacity = capacity;
}
void DiningHall::setHallId(int hall_id)
{
    if(hall_id >= 0)
    {
        _hall_id = hall_id;
    }
    else 
    {
        throw invalid_argument("Incorect value for hall_id!!!");
    }
}
void DiningHall::setName(string name)
{
    int value = name.length();
    for(int i = 0; i < value; i++)
    {
        if(!isalpha(name[i]))
        {
            throw invalid_argument("Incorrect name!!!");
        }
    }
    _name = name;
}
void DiningHall::setGender(Gender g)
{
    if(g == Gender::MALE || g == Gender::FEMALE)
    {
        _gender = g;
    }
    else
    {
        throw invalid_argument("Incorrect value for gender!!!");
    }
}
void DiningHall::setAddress(string address)
{
    _address = address;
}
void DiningHall::setCapacity(int capacity)
{
    if(capacity > 0)
    {
        _capacity = capacity;
    }
}

void DiningHall::inputHalls()
{
    cout << "DiningHall ID: ";
    cin >> _hall_id;
    cin.ignore();
    cout << "DiningHall Name: ";
    getline(cin, _name);
    _gender = selectGender();
    cin.ignore();
    cout << "DiningHall Address: ";
    getline(cin, _address);
    cout << "DiningHall Capacity: ";
    cin >> _capacity;
}

void DiningHall::print()const
{
    cout << "Name: " << _name << 
                            "\nHall Id: " << _hall_id << 
                                                    "\nAddress: " << _address << 
                                                                            "\nCapacity: " << _capacity << "\nGender: " << _gender << endl <<
                                                                                                                                     "***********" << endl;            
}

Gender DiningHall::stringToGender(const string& s) 
{
    if(s == "Male")
    { 
        return Gender::MALE;
    }
    else if(s == "Female")
    { 
        return Gender::FEMALE;
    }
    else
    {
        return Gender::FEMALE; // پیش‌فرض
    }
}

string DiningHall::genderToString(Gender g) 
{
    switch (g) 
    {
        case Gender::FEMALE:
            return "FEMALE";
        case Gender::MALE:
            return "MALE";
    }
    return "UNKNOWN";
} 

Gender DiningHall::selectGender() 
{
    int choice;
    cout << "Select gender:\n1. Male\n2. Female\nChoice: ";
    cin >> choice;
    switch (choice) {
        case 1: return Gender::MALE;
        case 2: return Gender::FEMALE;
        default: 
            cout << "Invalid choice, default BREAKFAST selected.\n";
            return Gender::FEMALE;
    }
}

// static inline void trim_inplace(string& s) {
//     auto not_space = [](int ch){ return !isspace(ch); };
//     s.erase(s.begin(), find_if(s.begin(), s.end(), not_space));
//     s.erase(find_if(s.rbegin(), s.rend(), not_space).base(), s.end());
// }

// static inline string upper_copy(std::string s) {
//     transform(s.begin(), s.end(), s.begin(),
//                    [](unsigned char c){ return toupper(c); });
//     return s;
// }

// Gender DiningHall::stringToGender(const string& in) {
//     string s = in;
//     trim_inplace(s);
//     s = upper_copy(s);

//     if (s == "MALE"   || s == "M") return Gender::MALE;
//     if (s == "FEMALE" || s == "F") return Gender::FEMALE;

//     throw invalid_argument("Invalid gender: " + in);
// }

/*std::ostream& operator<<(ostream& os, const Gender& g) {
    os << (g == Gender::MALE ? "Male" : "Female");
    return os;
}*/


