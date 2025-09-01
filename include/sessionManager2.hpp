#ifndef SESSIONMANAGER_HPP
#define SESSTIONMANAGER_HPP
#include <iostream>
#include "sessionBase.hpp"
#include "admin.hpp"
using namespace std;

namespace AdminSession
{
class SessionManager : public SessionBase
    {
    public:
        SessionManager();
        void login(string, string) override;
        void logout(string, string) override;
        Admin* currentAdmin();
        static SessionManager& instance();
        void load_session(string&, const string&) override;
        void save_session(string&, const string&) override;
        void setCurrentAdmin(Admin*, int);
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
    };
}
#endif

 