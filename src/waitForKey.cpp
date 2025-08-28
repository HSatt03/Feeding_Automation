#include <iostream>
#include <conio.h>
#include "waitForKey.hpp"

using namespace std;

void waitForKey()
{
    cout << "Press any key to continue...";
    _getch();  // صبر می‌کنه تا کاربر یه کلید بزنه
    cout << endl;
}