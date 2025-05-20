#ifndef SESSIONMANAGER_HPP
#define SESSTIONMANAGER_HPP
#include <iostream>
#include "../include/sessionBase.hpp"
#include "../include/admin.hpp"
using namespace std;

namespace AdminSession
{
class SessionManager : public SessionBase
    {
    public:
        //void login(string, string) : override
        //void logout() : override
        Admin currentAdmin();
        static SessionManager& instance();
        Admin getCurrentAdmin()const
        {
            return *_currentAdmin;
        }
        int getAdminID()const
        {
            return _adminID;
        }

    private:
        Admin *_currentAdmin;
        int _adminID;
        SessionManager(Admin, int);
        SessionManager(const SessionManager&) = delete;
        SessionManager operator=(const SessionManager&) = delete;
        //void loadSwssion() : override
        //void saveSession() : override
    

    };
}
#endif

 