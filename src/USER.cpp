#include<iostream>
using namespace std;
#include "../include/USER.h"
#include"../include/USER_ACCOUNT.h"
#include"../include/AUTHORITY_SERVICE.h"
#include"../include/ConsoleHelper.h"
#include"../include/SYSTEM.h"
#include"../include/BUYER.h"
#include"../include/SELLER.h"
#include"../include/PRODUCT_REPO.h"
#include<limits>
#include<cctype>
USER::USER() {
}

USER_ACCOUNT USER::getAccount() const {
    return user_acc;
}

Authority USER::getAuthority() const {
    return user_acc.getAuthority();
}

bool USER::handleUserRegistrationUI(AUTHORITY_SERVICE& auth_service)
{
    string fullName, username, password, contactNo, location, email;
    int age;

    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    bool validName = false;
    do {
        cout << "Enter full name (First Name Last Name - at least 2 words): ";
        getline(cin, fullName);
        
        int spaceCount = 0;
        validName = false;
        
        if (!fullName.empty()) {
            for (char c : fullName) {
                if (c == ' ') {
                    spaceCount++;
                }
            }
            if (spaceCount >= 1) {
                validName = true;
            }
        }
        
        if (!validName) {
            cout << "Error: Please enter at least first and last name!" << endl;
        }
    } while (!validName);

    bool validUsername = false;
    do {
        cout << "Enter username (min 5 characters, must include 1 special character like @, #, $, %, &, !): ";
        getline(cin, username);
        
        if (username.empty()) {
            ConsoleHelper::SetColor(12);
            cout << "⚠️ Error: Username cannot be empty!" << endl;
            ConsoleHelper::ResetColor();
            continue;
        }
        
        if (username.length() < 5) {
            ConsoleHelper::SetColor(12);
            cout << "⚠️ Error: Username must be at least 5 characters long!" << endl;
            ConsoleHelper::ResetColor();
            continue;
        }
        
        bool hasSpecialChar = false;
        string specialChars = "@#$%&!^*()_+-=[]{}|;:,.<>?/~`";
        for (char c : username) {
            if (specialChars.find(c) != string::npos) {
                hasSpecialChar = true;
                break;
            }
        }
        
        if (!hasSpecialChar) {
            ConsoleHelper::SetColor(12);
            cout << "⚠️ Error: Username must contain at least one special character (@, #, $, %, &, !, etc.)!" << endl;
            ConsoleHelper::ResetColor();
            continue;
        }
        
        if (auth_service.usernameExists(username)) {
            ConsoleHelper::SetColor(12);
            cout << "⚠️ Error: Username already exists! Please enter a different username." << endl;
            ConsoleHelper::ResetColor();
        } else {
            validUsername = true;
        }
    } while (!validUsername);

    bool validPassword = false;
    do {
        cout << "Enter password - minimum 5 characters (Tab to show/hide): ";
        password = ConsoleHelper::getPassword();
        
        if (password.empty()) {
            ConsoleHelper::SetColor(12);
            cout << "⚠️ Error: Password cannot be empty!" << endl;
            ConsoleHelper::ResetColor();
            continue;
        }
        
        if (password.length() < 5) {
            ConsoleHelper::SetColor(12);
            cout << "⚠️ Error: Password must have at least 5 characters!" << endl;
            ConsoleHelper::ResetColor();
        } else {
            validPassword = true;
        }
    } while (!validPassword);

    do {
        cout << "Enter contact number: ";
        getline(cin, contactNo);
        
        bool validContact = false;
        if (contactNo.length() == 10) {
            bool allDigits = true;
            for (char c : contactNo) {
                if (!isdigit(c)) {
                    allDigits = false;
                    break;
                }
            }
            
            if (allDigits && (contactNo.substr(0, 2) == "97" || contactNo.substr(0, 2) == "98")) {
                validContact = true;
            }
        }
        
        if (!validContact) {
            cout << "Enter the correct contact number!" << endl;
        } else {
            break;
        }
    } while (true);

    cout << "Enter age: ";
    cin >> age;

    if (cin.fail())
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        ConsoleHelper::SetColor(12);
        cout << "⚠️ Invalid age" << endl;
        ConsoleHelper::ResetColor();
        return false;
    }

    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    cout << "Enter location: ";
    getline(cin, location);

    // Email validation - must end with @gmail, @outlook, or @yahoo
    do {
        cout << "Enter email (@gmail, @outlook, or @yahoo): ";
        getline(cin, email);
        
        bool validEmail = false;
        if (email.find("@gmail") != string::npos || 
            email.find("@outlook") != string::npos || 
            email.find("@yahoo") != string::npos) {
            validEmail = true;
        }
        
        if (!validEmail) {
            cout << "Incorrect email format" << endl;
        } else {
            break;
        }
    } while (true);

    USER_ACCOUNT newAccount(fullName, username, password, contactNo, age, location, email, Client);
    if (auth_service.registerUser(newAccount)) {
        ConsoleHelper::SetColor(10);
        cout << "Registration successful!" << endl;
        ConsoleHelper::ResetColor();
        cin.get();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return true;  // ← CHANGE false to true here!
    } else {
        ConsoleHelper::SetColor(12);
        cout << "⚠️ Registration failed. Please try again." << endl;
        ConsoleHelper::ResetColor();
        ConsoleHelper::SetColor(13);
        cout << "\nPress Enter to continue...";
        ConsoleHelper::ResetColor();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return false;
    }
    return false;
}

void USER::handleUserLoginUI(AUTHORITY_SERVICE& auth_service, PRODUCT_REPO& repo, BILL_SERVICE& bill_svc)
{
    int modeChoice;
    cout << "Enter as: " << endl;
    ConsoleHelper::SetColor(15);
    ConsoleHelper::PrintDivider();
    ConsoleHelper::SetColor(10);
    cout << "[1] Buyer" << endl;
    cout << "[2] Seller" << endl;
    ConsoleHelper::SetColor(15);
    ConsoleHelper::PrintDivider();
    ConsoleHelper::ResetColor();
    cout << "Enter choice: ";
    cin >> modeChoice;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    string username, password;
    cout << "Enter username: ";
    getline(cin, username);

    cout << "Enter password (tab to show/hide): ";
    password = ConsoleHelper::getPassword();
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // ← FIX: flush the '\n' getPassword() leaves behind

    if (username.empty() || password.empty())
    {
        ConsoleHelper::SetColor(12);
        cout << "⚠️ Username and password can't be empty" << endl;
        ConsoleHelper::ResetColor();
        return;
    }

    USER_ACCOUNT account = auth_service.verifyAndGetAccount(username, password);

    if (account.getUsername().empty())
    {
        ConsoleHelper::SetColor(12);
        cout << "⚠️ Login failed. Invalid credentials." << endl;
        ConsoleHelper::ResetColor();
         ConsoleHelper::SetColor(13);
        cout << "Press Enter to continue...";
        ConsoleHelper::ResetColor();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return;
    }
    ConsoleHelper::SetColor(10);
    cout << "\tWelcome " << account.getUsername() << "!" << endl;
    ConsoleHelper::ResetColor();

    if (modeChoice == 1)
    {
        BUYER buyer(account, repo, bill_svc);
        buyer.startSession();
    }
    else if (modeChoice == 2)
    {
        SELLER seller(account, repo);
        seller.startSession();
    }
    else
    {
        ConsoleHelper::SetColor(12);
        cout << "⚠️ Invalid Choice" << endl;
        ConsoleHelper::ResetColor();
         ConsoleHelper::SetColor(13);
        cout << "Press Enter to continue...";
        ConsoleHelper::ResetColor();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return;
    }
    ConsoleHelper::SetColor(13);
    cout << "Press Enter to continue...";
    ConsoleHelper::ResetColor();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}