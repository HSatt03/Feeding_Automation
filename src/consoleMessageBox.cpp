#include <windows.h> // برای gotoxy و تغییر رنگ
#include <string>

#include "consoleMessageBox.hpp"
#include "utils.hpp"

ConsoleMessageBox::ConsoleMessageBox(int x, int y, int width, int height)
    : _x(x), _y(y), _width(width), _height(height) {}

ConsoleMessageBox& ConsoleMessageBox::instance()
{
    static ConsoleMessageBox msgBox(0, 0, 50, 5);
    return msgBox;
}

void ConsoleMessageBox::setPosition(int x, int y, int width, int height)
{
    _x = x;
    _y = y;
    _width = width;
    _height = height;
}

void ConsoleMessageBox::addMessage(const std::string& msg, MsgColor color)
{
    _messages.push_back({msg, color});
}

void ConsoleMessageBox::showMessages()
{
    drawBox();
    int msgY = _y + 1;
    for (auto& m : _messages)
    {
        if (msgY >= _y + _height - 1) break;
        gotoxy(_x + 1, msgY++);
        setColor(m.second);
        std::cout << m.first.substr(0, _width - 2);
        resetColor();
    }
}

void ConsoleMessageBox::clear()
{
    for (int i = 0; i < _height; ++i)
    {
        gotoxy(_x, _y + i);
        std::cout << std::string(_width, ' ');
    }
    _messages.clear();
}

void ConsoleMessageBox::drawBox()
{
    gotoxy(_x, _y);
    std::cout << "+" << std::string(_width - 2, '-') << "+";
    for (int i = 1; i < _height - 1; ++i)
    {
        gotoxy(_x, _y + i);
        std::cout << "|" << std::string(_width - 2, ' ') << "|";
    }
    gotoxy(_x, _y + _height - 1);
    std::cout << "+" << std::string(_width - 2, '-') << "+";
}

void ConsoleMessageBox::gotoxy(int x, int y)
{
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void ConsoleMessageBox::setColor(MsgColor color)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    switch(color)
    {
        case MsgColor::RED: SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_INTENSITY); break;
        case MsgColor::GREEN: SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_INTENSITY); break;
        case MsgColor::YELLOW: SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY); break;
        case MsgColor::BLUE: SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE | FOREGROUND_INTENSITY); break;
        default: SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE); break;
    }
}

void ConsoleMessageBox::resetColor()
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
}
