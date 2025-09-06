#ifndef LOGSYSTEM_HPP
#define LOGSYSTEM_HPP

#include <string>

using namespace std;

class LogSystem {
private:
    string filename;
    string getCurrentTime(); // گرفتن زمان و تاریخ فعلی

public:
    LogSystem(const string &file); // سازنده
    void addLog(const string &message, const std::string &level = "INFO"); // افزودن پیام
};
// دوتا لاگر جداگانه
extern LogSystem adminLogger;
extern LogSystem studentLogger;

#endif // LOGSYSTEM_HPP
