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
            // ابتدا داده‌های User رو به JSON اضافه کن
            j = json(a); // این خط خودش to_json کلاس User رو صدا می‌کنه
            // بعد فیلدهای خودش رو اضافه کن
        }
        static void from_json(const json& j, Admin& a)
        {
            // اول داده‌های User رو بارگذاری کن
            User& u = a; // upcast
            u = j.get<User>();
        }
    };
}

#endif