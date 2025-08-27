@echo off
REM =========================
REM Compile utils.cpp separately
REM =========================
g++ -c src/utils.cpp -Iinclude -o utils.o

REM =========================
REM Compile all other source files
REM =========================
g++ -c src/sessionManager2.cpp src/sessionBase.cpp src/admin.cpp src/user.cpp src/logsystem.cpp src/configPaths.cpp src/adminPanel.cpp src/meal.cpp src/diningHall.cpp Bcrypt.cpp/src/bcrypt.cpp Bcrypt.cpp/src/blowfish.cpp src/main.cpp -Iinclude -IBcrypt.cpp/include

REM =========================
REM Link all object files into main.exe
REM =========================
g++ *.o -o src/main.exe

REM =========================
REM Run the program
REM =========================
echo Running program...
.\src\main.exe

REM =========================
REM Keep the CMD window open after execution
REM =========================
pause8
