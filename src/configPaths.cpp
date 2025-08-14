#include <iostream>
#include "configPaths.hpp"
using namespace std;

ConfigPaths::ConfigPaths()
{
    d_config = "../config/";
    c_students = "../studentsCsvFile.csv";
    d_foodservice = "../config/foodservice/";
    d_sessions = "../config/sessions/";
    j_admin_config = "../config/admin_config.json";
    j_ConfigPaths = "../config/paths_config.json";
    j_meals = "../config/foodservice/meals.json";
    j_dininghalls = "../config/foodservice/dining_halls.json";
    d_student_sessions = "../config/sessions/student/";
    d_admin_sessions = "../config/sessions/admin/";
    j_foodservice_ids = "../config/foodservice/service_ids.json";
    l_students_log_file = "../logs/student.log";
    l_admins_log_file = "../logs/admin.log";
    d_logs = "logs/";
    t_student_transactions = "../config/student_transactions.json";
}

ConfigPaths& ConfigPaths::instance()
{
    static ConfigPaths instance;
    return instance;
}

// Getters
fs::path ConfigPaths::getConfigDir() const
{ 
    return d_config;
}
fs::path ConfigPaths::getStudentsCsv() const
{ 
    return c_students; 
}
fs::path ConfigPaths::getFoodServiceDir() const 
{ 
    return d_foodservice; 
}
fs::path ConfigPaths::getSessionsDir() const 
{ 
    return d_sessions; 
}
fs::path ConfigPaths::getAdminConfig() const 
{ 
    return j_admin_config; 
}
fs::path ConfigPaths::getConfigPathsFile() const 
{ 
    return j_ConfigPaths; 
}
fs::path ConfigPaths::getMealsJson() const 
{ 
    return j_meals; 
}
fs::path ConfigPaths::getDiningHallsJson() const 
{ 
    return j_dininghalls; 
}
fs::path ConfigPaths::getStudentSessionsDir() const 
{ 
    return d_student_sessions; 
}
fs::path ConfigPaths::getAdminSessionsDir() const 
{ 
    return d_admin_sessions;
 }
fs::path ConfigPaths::getFoodServiceIds() const 
{ 
    return j_foodservice_ids; 
}
fs::path ConfigPaths::getStudentsLogFile() const 
{ 
    return l_students_log_file; 
}
fs::path ConfigPaths::getAdminsLogFile() const 
{ 
    return l_admins_log_file; 
}
fs::path ConfigPaths::getLogsDir() const 
{ 
    return d_logs; 
}
fs::path ConfigPaths::getStudentTransactionsFile() const 
{ 
    return t_student_transactions; 
}
