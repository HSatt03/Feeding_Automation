#ifndef ADMIN_HPP
#define ADMIN_HPP

#include <iostream>
#include "user.hpp"
#include "json.hpp"

using namespace std;
using json = nlohmann::json;
class Admin : public User
{
public:
    Admin(int = 0, string = "", string = "", string = "", string = "");
    void print()const;
    string getType();
    static bool isThereAnyAdmin();
    static void sign_in(string&, string&);

private:
};

namespace nlohmann
{
    template<>
    struct adl_serializer<Admin>
    {
        static void to_json(json& j, const Admin& a)
        {
            // فقط فیلدهای User رو serialize کن، Admin خودش فیلد اضافه نداره
            j = static_cast<const User&>(a);
        }

        static void from_json(const json& j, Admin& a)
        {
            // ابتدا json رو به User تبدیل کن
            User& u = a; // upcast
            u = j.get<User>();
        }
    };
}

#endif