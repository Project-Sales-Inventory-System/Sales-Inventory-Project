#include<iostream>
using namespace std;
#include "USER.h"
#include"USER_ACCOUNT.h"
#include"AUTHORITY_SERVICE.h"
#include"../include/ConsoleHelper.h"
#include"SYSTEM.h"
#include"BUYER.h"
#include"SELLER.h"
#include"PRODUCT_REPO.h"
#include<limits>
#include<cctype>
//#include"../include/CART.h"

// Constructor
USER::USER() {
}

USER_ACCOUNT USER::getAccount() const {
    return user_acc;
}

Authority USER::getAuthority() const {
    return user_acc.getAuthority();
}

// UI Handler for User Registration - All console input/output here
void USER::handleUserRegistrationUI(AUTHORITY_SERVICE& auth_service)
{
    string fullName, username, password, contactNo, location, email;
    int age;

    // Clear input buffer at the start
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    // Full name - MANDATORY (at least first + last name)
    bool validName = false;
    do {
        cout << "Enter full name (First Name Last Name - at least 2 words): ";
        getline(cin, fullName);
        
        // Count spaces to ensure at least first + last name
        int spaceCount = 0;
        validName = false;
        
        if (!fullName.empty()) {
            for (char c : fullName) {
                if (c == ' ') {
                    spaceCount++;
                }
            }
            // At least 1 space means 2 words (first and last name)
            if (spaceCount >= 1) {
                validName = true;
            }
        }
        
        if (!validName) {
            cout << "Error: Please enter at least first and last name!" << endl;
        }
    } while (!validName);

    // Username - Check for duplicates immediately
    bool validUsername = false;
    do {
        cout << "Enter username (min 5 characters, must include 1 special character like @, #, $, %, &, !): ";
        getline(cin, username);
        
        if (username.empty()) {
            cout << "Error: Username cannot be empty!" << endl;
            continue;
        }
        
        if (username.length() < 5) {
            cout << "Error: Username must be at least 5 characters long!" << endl;
            continue;
        }
        
        // Check for at least one special character
        bool hasSpecialChar = false;
        string specialChars = "@#$%&!^*()_+-=[]{}|;:,.<>?/~`";
        for (char c : username) {
            if (specialChars.find(c) != string::npos) {
                hasSpecialChar = true;
                break;
            }
        }
        
        if (!hasSpecialChar) {
            cout << "Error: Username must contain at least one special character (@, #, $, %, &, !, etc.)!" << endl;
            continue;
        }
        
        if (auth_service.usernameExists(username)) {
            cout << "Error: Username already exists! Please enter a different username." << endl;
        } else {
            validUsername = true;
        }
    } while (!validUsername);

    // Password - At least 5 characters
    bool validPassword = false;
    do {
        cout << "Enter password - minimum 5 characters (Tab to show/hide): ";
        password = ConsoleHelper::getPassword();
        
        if (password.empty()) {
            cout << "Error: Password cannot be empty!" << endl;
            continue;
        }
        
        if (password.length() < 5) {
            cout << "Error: Password must have at least 5 characters!" << endl;
        } else {
            validPassword = true;
        }
    } while (!validPassword);

    // Contact number - 10 digits, must start with 97 or 98
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
        cout << "Invalid age" << endl;
        return;
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
        cout << "Registration successful!" << endl;
    } else {
        cout << "Registration failed. Please try again." << endl;
    }
    cout << "\nPress Enter to continue...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

// UI Handler for User Login - All console input/output here
void USER::handleUserLoginUI(AUTHORITY_SERVICE& auth_service, PRODUCT_REPO& repo)
{
    int modeChoice;
    cout<<"Enter as: "<<endl;
    cout<<"[1] Buyer"<<endl;
    cout<<"[2] Seller"<<endl;
    cout<<"Enter choice: ";
    cin>>modeChoice;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    
    string username, password;
    cout << "Enter username: ";
    getline(cin, username);
    cout << "Enter password (tab to show/hide): ";
    password=ConsoleHelper::getPassword();

    if(username.empty() || password.empty())
    {
        cout<<"Username and password cann't be empty"<<endl;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return;
    }
    
    // Verify credentials and get account
    USER_ACCOUNT account = auth_service.verifyAndGetAccount(username, password);
    
    // Check if account is valid (username not empty means successful login)
    if (account.getUsername().empty())
    {
        cout << "Login failed. Invalid credentials." << endl;
        return;
    }
    cout<<" Welcome "<<account.getUsername()<<"!"<<endl;
    
    if(modeChoice==1)
    {
        BUYER buyer(account, repo);
        buyer.startSession();
    }
    else if(modeChoice==2)
    {
        SELLER seller(account, repo);
        seller.startSession();
    }
    else{
        cout<<"Invalid Choice"<<endl;
        cout << "Press Enter to continue...";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return;
    }
    cout << "Press Enter to continue...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}