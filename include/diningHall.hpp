#ifndef DININGHALL_H
#define DININGHALL_H
#include <iostream>
#include <string>
using namespace std;
class DiningHall
{
public:
    DiningHall(int = 1, string = "Sadaf", string = "Next to the central library", int = 100);
    void setHallId(int);
    void setName(string);
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
    string getAddress()
    {
        return _address;
    }
    int getCapacity()
    {
        return _capacity;
    }

private:
    int _hall_id;
    string _name;
    string _address;
    int _capacity;
};
#endif