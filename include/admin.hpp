#ifndef ADMIN_HPP
#define ADMIN_HPP
#include <iostream>
#include "../include/user.hpp"
using namespace std;

class Admin : public User
{
public:
    Admin(int = 0, string = "", string = "", string = "", string = "");
    void print()const;
    string getType();
    static bool isThereAnyAdmin();
    static bool sign_in();
    static void register_admin(string&, string&);

private:
};

#endif