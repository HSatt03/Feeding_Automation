#ifndef ADMIN_HPP
#define ADMIN_HPP
#include <iostream>
#include "user.hpp"
using namespace std;

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

#endif