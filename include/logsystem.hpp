#ifndef LOGSYSTEM_HPP
#define LOGSYSTEM_HPP
using namespace std;


#include <string>

class LogSystem {
private:
    string filename;
    string getCurrentTime(); // گرفتن زمان و تاریخ فعلی

public:
    LogSystem(const string &file); // سازنده
    void addLog(const string &message, const std::string &level = "INFO"); // افزودن پیام
};

#endif // LOGSYSTEM_HPP
