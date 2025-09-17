#ifndef CONSOLE_MESSAGE_BOX_HPP
#define CONSOLE_MESSAGE_BOX_HPP

#include <iostream>
#include <vector>
#include <string>

using namespace std;

enum class MsgColor { DEFAULT, RED, GREEN, YELLOW, BLUE };

class ConsoleMessageBox
{
public:
    ConsoleMessageBox(int x = 0, int y = 0, int width = 50, int height = 5);

    static ConsoleMessageBox& instance();

    void setPosition(int x, int y, int width, int height);
    void addMessage(const string& msg, MsgColor color = MsgColor::DEFAULT);
    void showMessages();
    void clear();

private:
    void drawBox();
    void gotoxy(int x, int y);
    void setColor(MsgColor color);
    void resetColor();

    int _x, _y, _width, _height;
    vector<pair<string, MsgColor>> _messages;
};

#endif


