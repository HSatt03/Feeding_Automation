#ifndef DININGHALL_H
#define DININGHALL_H
#include <iostream>
#include <string>
#include "json.hpp"

using namespace std;
using json = nlohmann::json;

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
    void inputHalls();
    void print()const;
    void print_panel(int, int)const;
    bool operator==(DiningHall);
    int getHallId()const
    {
        return _hall_id;
    }
    string getName()const
    {
        return _name;
    }
    Gender getGender()const
    {
        return _gender;
    }
    string getAddress()const
    {
        return _address;
    }
    int getCapacity()const
    {
        return _capacity;
    }

    static Gender stringToGender(const string&);
    static string genderToString(Gender g);
    static Gender selectGender();
    // Gender stringToGender(const string&);

    friend ostream& operator<<(ostream& os, const Gender&);

private:
    int _hall_id;
    string _name;
    Gender _gender;
    string _address;
    int _capacity;
};
namespace nlohmann
{
    template<>
    struct adl_serializer<DiningHall>
    {
        static void to_json(json& j, const DiningHall& h)
        {
            j = {
                {"hallID", h.getHallId()},
                {"name", h.getName()},
                {"gender", DiningHall::genderToString(h.getGender())},
                {"address", h.getAddress()},
                {"capacity", h.getCapacity()}
                };
        }
        static void from_json(const json& j, DiningHall& h)
        {
            h.setHallId(j.at("hallID").get<int>());
            h.setName(j.at("name").get<string>());
            h.setGender(DiningHall::stringToGender(j.at("gender").get<string>()));
            h.setAddress(j.at("address").get<string>());
            h.setCapacity(j.at("capacity").get<int>());
        }
    };
}

#endif