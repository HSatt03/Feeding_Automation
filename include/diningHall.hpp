#ifndef DININGHALL_H
#define DININGHALL_H
#include <iostream>
#include <string>
using namespace std;

enum class Gender
{
    MALE,
    FEMALE
};

class DiningHall
{
public:
    DiningHall(int = 1, string = "Sadaf", string = "Next to the central library", int = 100);
    void setHallId(int);
    void setName(string);
    void setGender(Gender);
    void setAddress(string);
    void setCapacity(int);
    void print()const;
    bool operator==(DiningHall);
    int getHallId()
    {
        return _hall_id;
    }
    string getName()
    {
        return _name;
    }
    Gender getGender()
    {
        return _gender;
    }
    string getAddress()
    {
        return _address;
    }
    int getCapacity()
    {
        return _capacity;
    }

    static Gender stringToGender(const string&);
    static Gender selectGender();

    friend ostream& operator<<(ostream& os, const Gender&);

private:
    int _hall_id;
    string _name;
    Gender _gender;
    string _address;
    int _capacity;
};

#endif