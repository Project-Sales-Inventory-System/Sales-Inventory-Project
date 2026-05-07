#include"../include/SYSTEM.h"
#include"../include/USER.h"
#include<iostream>
#include"../include/USER_ACCOUNT.h"
#include"../include/BUYER.h"
#include"../include/SELLER.h"
#include"../include/ADMIN.h"
#include"../include/ConsoleHelper.h"
#include "../include/UI_config.h"
#include"../include/BILL_SERVICE.h"
#include"../include/BILL.h"
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
    cout << "Please select your role to continue." << endl;
    cout << "Navigate with number keys for speed." << endl;
    ConsoleHelper::SetColor(15);
    ConsoleHelper::PrintDivider();
    ConsoleHelper::SetColor(10);
    cout << "[1] Register" << endl;
    cout << "[2] Search Products" << endl;
    cout << "[3] View Products" << endl;
    cout << "[4]  Exit" << endl;
    ConsoleHelper::SetColor(15);
    ConsoleHelper::PrintDivider();
    ConsoleHelper::ResetColor();
    cout << "Enter choice: ";
}

void SYSTEM:: displayMainMenu()
{
    ConsoleHelper::Header();
    ConsoleHelper::SetColor(10);
    const int terminalWidth = 80; // assume 80 characters wide
    std::string line = std::string(44, '=');
    std::string message = "Welcome to our Management Portal";

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
    cout<<"Register to the System if you like"<<endl;
    cout<< "If you're already a registered user"<<endl;
    cout<<"Proceed to next Menu exiting this Menu"<<endl;
    cout << "Navigate with number keys." << endl;
    
    ConsoleHelper::SetColor(15);
    ConsoleHelper::PrintDivider();
    ConsoleHelper::SetColor(10);
    cout << "[1] User Login" << endl;
    cout << "[2]  Admin Login" << endl;
    cout << "[3]  Exit" << endl;
    ConsoleHelper::SetColor(15);
    ConsoleHelper::PrintDivider();
    ConsoleHelper::ResetColor();
    cout << "Enter choice: ";
}

void SYSTEM::handleRegistration()
{
    // UI logic separated to USER class for easy modification
   bool success = USER::handleUserRegistrationUI(auth);
    if (success)
    {
        isRegistered = true;
    }
    
}

void SYSTEM::handleUserLogin()
{
    USER::handleUserLoginUI(auth, repo);
}


void SYSTEM::handleAdminLogin()
{
    ADMIN::handleAdminLoginUI(auth, repo);
}

void SYSTEM:: guestMenu()
{
    bool end= true;
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
            cout << "⚠️ Invalid input. Try again." << endl;
        }
    }
}

void SYSTEM::run()
{
    bool running = true;
    while (running)
    {
        displayMainMenu();
        int choice;
        cin >> choice;

        if (cin.fail())
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "⚠️ Invalid input. Try again." << endl;
            continue;
        }

        switch (choice)
        {
            
            case 1:
                handleUserLogin();
                break;
             case 2:
                handleAdminLogin();
                break;
            case 3:
                cout << "Exiting system..." << endl;
                running = false;
                break;
            default:
            cout << "⚠️ Invalid input. Try again." << endl;
        }
    }

}