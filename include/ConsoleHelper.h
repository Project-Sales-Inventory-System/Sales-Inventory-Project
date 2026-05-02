#pragma once
#include <string>
#include<string>
#include<WINDOWS.h>
class ConsoleHelper {
    public:
    static void SetColor(int ColourCode);
    static void ResetColor();
    static void ClearScreen();
    static void PrintError();
    static void PrintDivider();
    static void PrintSuccess();
    static void PrintHeader(std::string title);
    static std:: string getPassword();

};