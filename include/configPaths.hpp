#ifndef CONFIGPATHS_HPP
#define CONFIGPATHS_HPP

#include <filesystem>

namespace fs = std::filesystem;

class ConfigPaths
{
public:
    static ConfigPaths& instance();

    fs::path getConfigDir() const;
    fs::path getStudentsCsv() const;
    fs::path getFoodServiceDir() const;
    fs::path getSessionsDir() const;
    fs::path getAdminConfig() const;
    fs::path getConfigPathsFile() const;
    fs::path getMealsJson() const;
    fs::path getDiningHallsJson() const;
    fs::path getStudentSessionsDir() const;
    fs::path getAdminSessionsDir() const;
    fs::path getFoodServiceIds() const;
    fs::path getStudentsLogFile() const;
    fs::path getAdminsLogFile() const;
    fs::path getLogsDir() const;
    fs::path getStudentTransactionsFile() const;

private:
    ConfigPaths(); // constructor private for singleton
    ConfigPaths(const ConfigPaths&) = delete;
    ConfigPaths& operator=(const ConfigPaths&) = delete;

    fs::path d_config;
    fs::path c_students;
    fs::path d_foodservice;
    fs::path d_sessions;
    fs::path j_admin_config;
    fs::path j_ConfigPaths;
    fs::path j_meals;
    fs::path j_dininghalls;
    fs::path d_student_sessions;
    fs::path d_admin_sessions;
    fs::path j_foodservice_ids;
    fs::path l_students_log_file;
    fs::path l_admins_log_file;
    fs::path d_logs;
    fs::path t_student_transactions;
};

#endif // CONFIGPATHS_HPP
