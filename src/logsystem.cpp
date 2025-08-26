#include "logsystem.hpp"
#include <iostream>
#include <fstream>
#include <ctime>
#include <iomanip>
#include <sstream>

using namespace std;

string LogSystem::getCurrentTime() {
    time_t now = time(nullptr);
    tm *ltm = localtime(&now);

    ostringstream oss;
    oss << put_time(ltm, "%Y-%m-%d %H:%M:%S");
    return oss.str();
}

#include <filesystem>

LogSystem::LogSystem(const std::string &file) : filename(file) {
    namespace fs = std::filesystem;
    fs::path logPath = fs::path(file).parent_path();

    if (!logPath.empty() && !fs::exists(logPath)) {
        fs::create_directories(logPath);
    }

    std::ofstream outfile(filename, std::ios::app);
    outfile.close();
}

void LogSystem::addLog(const string &message, const string &level) {
    ofstream outfile(filename, ios::app);
    if (!outfile) {
        cerr << "Error: Cannot open log file!" << endl;
        return;
    }

    outfile << "[" << getCurrentTime() << "] "
            << "[" << level << "] "
            << message << endl;

    outfile.close();
}
