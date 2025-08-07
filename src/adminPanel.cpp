#include <iostream>
#include <filesystem>
#include "adminPanel.hpp"
#include "configPaths.hpp"
using namespace std;
namespace fs = std::filesystem;

fs::path AdminPanel::chooseCsvFile()
{
    fs::path csvPath = ConfigPaths::instance().getStudentsCsv();
    return csvPath;
}

