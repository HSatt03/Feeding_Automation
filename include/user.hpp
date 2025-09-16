#ifndef USER_HPP
#define USER_HPP

#include <iostream>
#include <string>
#include "json.hpp"

using namespace std;
using json = nlohmann::json;

class User
{
public:
    User(int = 0, string = "", string = "", string = "", string  = "");

    void setUserID(int);
    void setName(string);
    void setLastName(string);
    void setHashPassword(string);
    void setPhone(string);

    virtual void print()const;
    virtual string getType();
    
    int getUserID()const
    {
        return _user_id;
    }
    string getName()const
    {
        return _name;
    }
    string getLastName()const
    {
        return _last_name;
    }
    string getHashedPasssword()const
    {
        return _hashed_password;
    }
    string getPhone()const
    {
        return _phone;
    }

private:
    int _user_id;
    string _name;
    string _last_name;
    string _hashed_password;
    string _phone;
};

namespace nlohmann
{
    template<>
    struct adl_serializer<User>
    {
        static void to_json(json& j, const User& a)
        {
            j = {
                {"userID", a.getUserID()},
                {"name", a.getName()},
                {"lastname", a.getLastName()},
                {"hashpassword", a.getHashedPasssword()},
                {"phone", a.getPhone()}
                };
        }
        static void from_json(const json& j, User& s)
        {
            s.setUserID(j.at("userID").get<int>());
            s.setName(j.at("name").get<string>());
            s.setLastName(j.at("lastname").get<string>());
            s.setHashPassword(j.at("hashpassword").get<string>());
            s.setPhone(j.at("phone").get<string>());
        }
    };
}

#endif
