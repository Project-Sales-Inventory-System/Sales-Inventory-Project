#include "../include/ConsoleHelper.h"
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <iostream>
#include <iomanip>
#include<conio.h>
#include<string>
using namespace std;
void ConsoleHelper::SetColor(int ColorCode)
{
    static bool utf8_initialized = false;
    if (!utf8_initialized) {
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleOutputCP(65001); // UTF-8
        SetConsoleCP(65001); // UTF-8
        utf8_initialized = true;
    }
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), ColorCode);
}
void ConsoleHelper::ResetColor()
{
    SetColor(7);
}
void ConsoleHelper::ClearScreen() 
{
    system("cls"); 
}
void ConsoleHelper::PrintError() 
{
    SetColor(9);
    cout << "⚠️ Try again" << endl; 
}
void ConsoleHelper::PrintDivider()
{
    ConsoleHelper::SetColor(15);
    cout << string(60, '-') << endl;
}
void ConsoleHelper::PrintSuccess()
{
    SetColor(10);
    cout << "SUCCESS!!" << endl;
}
void ConsoleHelper::Header()
{
    ConsoleHelper::ClearScreen();
     ConsoleHelper::ClearScreen();
    const int terminalWidth = 80; // assume 80 characters wide
    std::string message = "✦ Sales & Inventory System ✦";

    // compute left padding for centering
    int msgPadding = (terminalWidth - message.length()) / 2;

    ConsoleHelper::SetColor(1);
    cout << string(msgPadding, ' ') << message << endl;
}
void ConsoleHelper::PrintHeader(std::string title)
{
    SetColor(10);
    cout << setfill('-') << setw(10) << endl;
    cout << "  " << title << endl;
    cout << setfill('-') << setw(10) << endl;
} 
 std:: string ConsoleHelper:: getPassword() {
    string password;
    char ch;
    bool show = false;

    while ((ch = _getch()) != '\r') // '\r' is Enter key
    {
        if (ch == '\b') // Backspace
        {
            if (!password.empty()) {
                password.pop_back();
                cout << "\b \b"; // erase last * from screen
            }
        }
        else if (ch == 9) // Tab key to toggle show/hide
        {
            show = !show;
        }
        else
        {
            password += ch;
            if (show)
                cout << ch;
            else
                cout << '*';
        }
    }
    cout << endl;
    return password;
}