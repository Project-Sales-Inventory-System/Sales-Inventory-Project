#pragma once
#include <string>
#include<string>
#ifndef WINDOWS_H
#define WINDOWS_H
#include <windows.h>
#undef WINDOWS_H
#endif
class ConsoleHelper {
    public:
    static void SetColor(int ColourCode);
    static void ResetColor();
    static void ClearScreen();
    static void PrintError();
    static void PrintDivider();
    static void PrintSuccess();
    static void PrintHeader(std::string title);
    static void Header();
    static std:: string getPassword();

};