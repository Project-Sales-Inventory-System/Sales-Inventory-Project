#include"SYSTEM.h"
#include"USER.h"
#include<iostream>
#include"USER_ACCOUNT.h"
#include"BUYER.h"
#include"SELLER.h"
#include"ADMIN.h"
#include"../include/ConsoleHelper.h"
#include<limits>
#include<cctype>
using namespace std;
SYSTEM::SYSTEM()
    : current_user(nullptr), repo(), isAdminLogggedin(false){}

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
    isAdminLogggedin = false;
    return current_user;
}

bool SYSTEM::adminLogin(const std::string& passcode)
{
    isAdminLogggedin= auth.verifyAdmin(passcode);
    return isAdminLogggedin;
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


void SYSTEM::logoutCurrentUser()
{
    if(isAdminLogggedin==true)
    {
        isAdminLogggedin= false;
        cout<<"Admin logout"<<endl;
        return;
    }
    if (!current_user) {
        cout << "No user is currently logged in." << endl;
        return;
    }

    std::string uname = current_user->getUsername();
    delete current_user;
    current_user = nullptr;
    cout << "Session ended for " << uname << endl;
}
    void SYSTEM:: addProduct(PRODUCT product){
        if(isAdminLogggedin){
            repo.addProduct(product);
            return;
        }
        if(current_user==nullptr){
            cout<<"No user Logged in"<<endl;
            return;
        }
        if(current_user->getAuthority()!=ClientSELLER)
        {
            cout<<"Access not granted!!"<<endl;
            return;
        }
        repo.addProduct(product);
    }
    void SYSTEM::removeProduct(){
        if(!isAdminLogggedin){
            cout<<"Access not granted!!"<<endl;
            return;
        }

        repo.removeProduct();
    }
    void SYSTEM:: updateProduct(){
        if(!isAdminLogggedin){
            cout<<"Access not granted!!"<<endl;
            return;
        }
        repo.updateProduct();
    }
    void SYSTEM:: searchByName(string name){
        
        repo.searchByName(name);
        


    }

    void SYSTEM:: getAllProducts(){
        if(isAdminLogggedin){
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

void SYSTEM::displayMainMenu()
{
    cout << endl;
    ConsoleHelper::ClearScreen();
    ConsoleHelper::SetColor(11);
    ConsoleHelper::PrintHeader("--------------SALES & INVENTORY SYSTEM---------------");
    ConsoleHelper::ResetColor();
    ConsoleHelper::PrintDivider();
    cout << "\n1. Register\n2. User Login\n3. Admin Login\n4. Exit\n";
    cout << "Enter choice: ";
}

void SYSTEM::handleRegistration()
{
    // UI logic separated to USER class for easy modification
    USER::handleUserRegistrationUI(auth);
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
            cout << "Invalid input. Try again." << endl;
            continue;
        }

        switch (choice)
        {
            case 1:
                handleRegistration();
                break;
            case 2:
                handleUserLogin();
                break;
             case 3:
                handleAdminLogin();
                break;
            case 4:
                cout << "Exiting system..." << endl;
                running = false;
                break;
            default:
                cout << "Invalid choice. Try again." << endl;
        }
    }
}