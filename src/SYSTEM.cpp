#include"SYSTEM.h"
#include"USER.h"
#include<iostream>
#include"USER_ACCOUNT.h"
#include"BUYER.h"
#include"SELLER.h"
#include"ADMIN.h"
#include"../include/ConsoleHelper.h"
#include "../include/UI_config.h"
#include<limits>
#include<cctype>
using namespace std;
SYSTEM::SYSTEM()
    : current_user(nullptr), repo(), isAdminLoggedin(false), isRegistered(false){}


bool SYSTEM::registerAccount(const USER_ACCOUNT& account)
{
    return auth.registerUser(account);
}

USER* SYSTEM::loginAccount(const std::string& username, const std::string& password)
{
    if (current_user)
    {
        delete current_user;
        current_user = nullptr;
    }

    current_user = auth.login(username, password);
    isAdminLoggedin = false;
    return current_user;
}

bool SYSTEM::adminLogin(const std::string& passcode)
{
    isAdminLoggedin= auth.verifyAdmin(passcode);
    return isAdminLoggedin;
}

std::vector<USER_ACCOUNT> SYSTEM::getAllUsers() const
{
    return auth.getAllRegisteredUsers();
}

bool SYSTEM::deleteUser(const std::string& username)
{
    return auth.deleteUserByUsername(username);
}

 USER* SYSTEM:: process(bool isLogin, USER_ACCOUNT account)
{
   if(!isLogin)
   {
         registerAccount(account);
         return nullptr;
   }
   else
   {
         return loginAccount(account.getUsername(), account.getPassword()); 
   }
}


void SYSTEM:: addProduct(PRODUCT product){
        if(isAdminLoggedin){
            repo.addProduct(product);
            return;
        }
        if(current_user==nullptr){
            cout<<"No user Logged in"<<endl;
            return;
        }
        if(current_user->getAuthority()!=ClientSELLER)
        {
            cout <<"Access not granted!!"<<endl;
            return;
        }
        repo.addProduct(product);
    }
    void SYSTEM::removeProduct(){
        if(!isAdminLoggedin){
            cout<<"Access not granted!!"<<endl;
            return;
        }

        repo.removeProduct();
    }
    void SYSTEM:: updateProduct(){
        if(!isAdminLoggedin){
            cout<<"Access not granted!!"<<endl;
            return;
        }
        repo.updateProduct();
    }
    void SYSTEM:: searchByName(std:: string name){
        
        repo.searchByName(name);
        


    }

    void SYSTEM:: getAllProducts(){
        if(isAdminLoggedin){
            repo.getAllProducts(true);
            return;
        }
        if(current_user==nullptr){
            cout<<"No user Logged in"<<endl;
            return;
        }
        repo.getAllProducts(false);
    }
    void SYSTEM:: saveToFile()
    {
        repo.saveToFile();
    }

PRODUCT_REPO& SYSTEM::getRepo()
{
    return repo;
}

AUTHORITY_SERVICE& SYSTEM::getAuthService()
{
    return auth;
}

void SYSTEM::displayGuestMenu()
{
    cout << endl;
    ConsoleHelper::ClearScreen();
    ConsoleHelper::Header();
    const int terminalWidth = 80; // assume 80 characters wide
    std::string line = std::string(44, '=');
    std::string message ="    👥 Welcome to our System Portal 👥" ;

     // compute left padding for centering
    int padding = (terminalWidth - line.length()) / 2;
    int msgPadding = (terminalWidth - message.length()) / 2;

    ConsoleHelper::SetColor(15);
    cout << string(padding, ' ') << line << endl;
    ConsoleHelper::SetColor(10);
    cout << string(padding, ' ') << message << endl;
    ConsoleHelper::SetColor(15);
    cout << string(padding, ' ') << line << endl;

    ConsoleHelper::SetColor(12);
    cout << "Guideline:" << endl;
    cout << "Please select your role to continue:" << endl;
    cout << "Navigate with number keys for speed." << endl;
    cout << "Press '1' to register." << endl;
    cout << "Press '2' for view Product. " << endl;
    cout << "Press '3' for search product." << endl;
    cout << "Press '4' to exit." << endl;
    ConsoleHelper::SetColor(15);
    cout << "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━" << endl;
    ConsoleHelper::SetColor(10);
    cout << "📋 Register" << endl;
    cout << "🔍 Search Products" << endl;
    cout << "👀 View Products" << endl;
    cout << "⏹️  Exit" << endl;
    ConsoleHelper::SetColor(15);
    cout << "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━" << endl;
    ConsoleHelper::ResetColor();
    cout << "Enter choice: ";
}

void SYSTEM:: displayMainMenu()
{
    ConsoleHelper::Header();
    ConsoleHelper::SetColor(10);
    const int terminalWidth = 80; // assume 80 characters wide
    std::string line = std::string(44, '=');
    std::string message = "Welcome to our Management Portal👋";

    // compute left padding for centering
    int padding = (terminalWidth - line.length()) / 2;
    int msgPadding = (terminalWidth - message.length()) / 2;

    ConsoleHelper::SetColor(15);
    cout << string(padding, ' ') << line << endl;
    ConsoleHelper::SetColor(10);
    cout << string(padding, ' ') << message << endl;
    ConsoleHelper::SetColor(15);
    cout << string(padding, ' ') << line << endl;

    ConsoleHelper::SetColor(12);
    cout << "Guideline:" << endl;
    cout << "Please select your role to continue:" << endl;
    cout << "Navigate with number keys for speed." << endl;
    cout << "Press '1' to UserLogin." << endl;
    cout << "Press '2' to AdminLogin." << endl;
    cout << "Press '3' to Exit." << endl;
    ConsoleHelper::SetColor(15);
    cout << "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━" << endl;
    ConsoleHelper::SetColor(10);
    cout << "👤 User Login" << endl;
    cout << "🛡️  Admin Login" << endl;
    cout << "⏹️  Exit" << endl;
    ConsoleHelper::SetColor(15);
    cout << "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━" << endl;
    ConsoleHelper::ResetColor();
    cout << "Enter choice: ";
}


void SYSTEM::handleRegistration()
{
    // UI logic separated to USER class for easy modification
   bool success = USER::handleUserRegistrationUI(auth);
    if (success)
    {
        isRegistered = true;   // only set true if actually registered
    }
    // if failed → isRegistered stays false
    // → guest loop continues
    // → pressing 4 exits on first press ✅
}

void SYSTEM::handleUserLogin()
{
    // UI logic separated to USER class for easy modification
    USER::handleUserLoginUI(auth, repo);
}


void SYSTEM::handleAdminLogin()
{
    // UI logic separated to ADMIN class for easy modification
    ADMIN::handleAdminLoginUI(auth, repo);
}


void SYSTEM:: guestMenu()
{
    bool end = true;
    while(end)
    {
       displayGuestMenu();
        int choice;
        cin>>choice;
        if (cin.fail())
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "⚠️ Invalid input. Try again." << endl;
            continue;
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        switch (choice)
        {
            case 1:
                handleRegistration();
                break;
            case 2:
               { string name;
                cout<<"Enter the name of the product: ";
                getline(cin,name);
                searchByName(name);
                break;
               }
             case 3:
                repo.getAllProducts(false);
                break;

            case 4:
                cout << "Exiting system..." << endl;
                end = false;
                break;
            default:
                cout << "⚠️ Invalid choice. Try again." << endl;
        }
    }
}

void SYSTEM::run()
{
    bool running = true;

    while (running)
    {
        if (!isRegistered)
        {
            // show guest menu
            displayGuestMenu();

            int choice;
            cin >> choice;

            if (cin.fail())
            {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                ConsoleHelper::SetColor(12);
                cout << "  ⚠️  Invalid input. Try again." << endl;
                ConsoleHelper::ResetColor();
                continue;
            }
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            switch (choice)
            {
                case 1:
                    handleRegistration(); // sets isRegistered = true
                    break;               // next iteration shows main menu
                                         // automatically — no double exit

                case 2:
                {
                    ConsoleHelper::ClearScreen();
                    ConsoleHelper::Header();
                    repo.getAllProducts(false);
                    cout << "\n  Press Enter to go back...";
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    break;
                }

                case 3:
                {
                    ConsoleHelper::ClearScreen();
                    ConsoleHelper::Header();
                    string name;
                    ConsoleHelper::SetColor(11);
                    cout << "  Enter product name to search: ";
                    ConsoleHelper::ResetColor();
                    getline(cin, name);
                    searchByName(name);
                    cout << "\n  Press Enter to go back...";
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    break;
                }

                case 4: // ONE press exits cleanly
                    ConsoleHelper::ClearScreen();
                    ConsoleHelper::SetColor(14);
                    cout << "\n  ✨ Thank you for visiting us! ✨" << endl;
                    cout << "  Have a great day!!!\n" << endl;
                    ConsoleHelper::ResetColor();
                    running = false; // exits the ONE loop
                    break;

                default:
                    ConsoleHelper::SetColor(12);
                    cout << "  ⚠️  Invalid choice. Try again." << endl;
                    ConsoleHelper::ResetColor();
            }
        }
        else
        {
            // show main menu
            displayMainMenu();

            int choice;
            cin >> choice;

            if (cin.fail())
            {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                ConsoleHelper::SetColor(12);
                cout << "  ⚠️  Invalid input. Try again." << endl;
                ConsoleHelper::ResetColor();
                continue;
            }
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            switch (choice)
            {
                case 1:
                    handleUserLogin();
                    break;

                case 2:
                    handleAdminLogin();
                    break;

                case 3: // ONE press exits cleanly
                    ConsoleHelper::ClearScreen();
                    ConsoleHelper::SetColor(14);
                    cout << "\n  ✨ Thank you for visiting us! ✨" << endl;
                    cout << "  Have a great day!!!\n" << endl;
                    ConsoleHelper::ResetColor();
                    running = false; // exits the SAME loop
                    break;

                default:
                    ConsoleHelper::SetColor(12);
                    cout << "  ⚠️  Invalid choice. Try again." << endl;
                    ConsoleHelper::ResetColor();
            }
        }
    }
}