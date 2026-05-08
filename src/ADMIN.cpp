#include <iostream>
#include <limits>
#include <vector>
#include <iomanip>
#include"../include/USER.h"
#include"../include/PRODUCT_REPO.h"
#include"../include/AUTHORITY_SERVICE.h"
#include"../include/BILL_SERVICE.h"
#include "../include/SYSTEM.h"
#include "../include/USER_ACCOUNT.h"
#include "../include/ConsoleHelper.h"
#include "../include/ADMIN.h"
#include "../include/UI_config.h"
using namespace std;


ADMIN::ADMIN(const std::string & pass, PRODUCT_REPO& repository, AUTHORITY_SERVICE& auth_svc, BILL_SERVICE& bill_svc) 
: USER() 
{
    this->repo = &repository;
    this->auth_service = &auth_svc;
    this->bill_service = &bill_svc; 
    this->passcode = pass;          
}
bool ADMIN::authenticate(AUTHORITY_SERVICE& auth)
{
    return auth.verifyAdmin(passcode);
}

void ADMIN::performAction()
{
    AdminMenu();
}

// Admin Menu - display only
void ADMIN::AdminMenu()
{
   ConsoleHelper::Header();
    ConsoleHelper::SetColor(10);
    const int terminalWidth = 80; // assume 80 characters wide
    std::string line = std::string(44, '=');
    std::string message = "Welcome to our Admin Portal";

    int padding = (terminalWidth - line.length()) / 2;
    int msgPadding = (terminalWidth - message.length()) / 2;

    ConsoleHelper::SetColor(15);
    cout << string(padding, ' ') << line << endl;
    ConsoleHelper::SetColor(10);
    cout << string(padding, ' ') << message << endl;
    ConsoleHelper::SetColor(15);
    cout << string(padding, ' ') << line << endl;

    ConsoleHelper::SetColor(15);
    ConsoleHelper::PrintDivider();
    ConsoleHelper::SetColor(11);
    cout << "[1]  Manage user" << endl;
    cout << "[2]  View Products by Category" << endl;
    cout << "[3]  Add Product" << endl;
    cout << "[4]  Remove Product" << endl;
    cout << "[5]  Update Product" << endl;
    cout << "[6]  Search Products" << endl;
    cout << "[7]  Logout" << endl;
    ConsoleHelper::SetColor(15);
    ConsoleHelper::PrintDivider();
    ConsoleHelper::ResetColor();
    cout << "Enter your Choice: ";
}

void ADMIN::handleUserManagement()
{
    ConsoleHelper::ClearScreen();
    ConsoleHelper::Header();
    if (!auth_service)
    {
        ConsoleHelper::SetColor(12);
        cout << "⚠️ Auth service not available." << endl;
        return;
    }

    vector<USER_ACCOUNT> users = auth_service->getAllRegisteredUsers();
    if (users.empty())
    {
        cout << "No users registered." << endl;
        return;
    }

    cout << endl;
    ConsoleHelper::SetColor(15);
    cout << "===============================================" << endl;
    ConsoleHelper::SetColor(10);
    cout << "REGISTERED USERS" << endl;
    ConsoleHelper::SetColor(15);
    cout << "===============================================" << endl;
    ConsoleHelper::SetColor(15);
    ConsoleHelper::SetColor(10);
    cout << "INDEX | NAME | USERNAME | ROLE | EMAIL" << endl;
    ConsoleHelper::SetColor(15);
    cout << "-----------------------------------------------" << endl;
    ConsoleHelper::SetColor(7);
    for (int i = 0; i < users.size(); i++)
    {
        cout << i + 1 << "     | "
             << users[i].getFullname() << " | "
             << users[i].getUsername() << " | "
             << (users[i].getAuthority() == ClientSELLER ? "Seller" : "Buyer") << " | "
             << users[i].getMailAddress()
             << endl;
    }
    ConsoleHelper::SetColor(15);
    cout << "-----------------------------------------------" << endl;
    ConsoleHelper::SetColor(7);
    string usernameToDelete;
    cout << "Enter username to delete or 0 to go back: ";
    getline(cin, usernameToDelete);
    if (usernameToDelete == "0")
    {
        return;
    }
    if (auth_service->deleteUserByUsername(usernameToDelete))
    {
        ConsoleHelper::SetColor(10);
        cout << "User deleted successfully!" << endl;
        ConsoleHelper::SetColor(15);
        cout << "\n===============================================" << endl;
        ConsoleHelper::SetColor(10);
        cout << "UPDATED USER LIST" << endl;
        ConsoleHelper::SetColor(15);
        cout << "===============================================" << endl;
        ConsoleHelper::ResetColor();
        vector<USER_ACCOUNT> updatedUsers = auth_service->getAllRegisteredUsers();
        if (updatedUsers.empty())
        {
            ConsoleHelper::SetColor(12);
            cout << "⚠️ No users registered." << endl;
            ConsoleHelper::ResetColor();
        }
        else
        {
            ConsoleHelper::SetColor(10);
            cout << "INDEX | NAME | USERNAME | ROLE | EMAIL" << endl;
            ConsoleHelper::SetColor(15);
            cout << "-----------------------------------------------" << endl;
            for (int i = 0; i < updatedUsers.size(); i++)
            {
                ConsoleHelper::SetColor(10);
                cout << i + 1 << "     | "
                     << updatedUsers[i].getFullname() << " | "
                     << updatedUsers[i].getUsername() << " | "
                     << (updatedUsers[i].getAuthority() == ClientSELLER ? "Seller" : "Buyer") << " | "
                     << updatedUsers[i].getMailAddress()
                     << endl;
            }
            ConsoleHelper::SetColor(15);
            cout << "-----------------------------------------------" << endl;
        }
    }
    else
    {
        ConsoleHelper::SetColor(12);
        cout << "⚠️ User not found or failed to delete." << endl;
    }
    ConsoleHelper::SetColor(13);
    cout << "Press Enter to continue...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

// Get username
std::string ADMIN::getUsername() const
{
    return "ADMIN";
}

void ADMIN::startSession()
{
    bool adminLoggedIn = true;
    while (adminLoggedIn)
    {
        AdminMenu();
        int adminChoice;
        cin >> adminChoice;

        if (cin.fail())
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            ConsoleHelper::SetColor(12);
            cout << "⚠️ Invalid input. Try again." << endl;
            ConsoleHelper::SetColor(7);
            continue;
        }

        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch (adminChoice)
        {
            case 1:
                handleUserManagement();
                break;
            case 2:
            {
                string category;
                cout << "Enter category to view products: ";
                getline(cin, category);
                viewProduct(category);
                ConsoleHelper::SetColor(13);
                cout << "Press Enter to continue...";
                ConsoleHelper::SetColor(7);
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                break;
            }
            case 3:
            {
                string category, name;
                double price;
                int qty;
                cout << "Enter product category: ";
                getline(cin, category);
                cout << "Enter product name: ";
                getline(cin, name);
                cout << "Enter product price: ";
                cin >> price;
                cout << "Enter product quantity: ";
                cin >> qty;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                
                // Show confirmation before adding
                cout << endl;
                ConsoleHelper::SetColor(15);
                cout << "===============================================" << endl;
                ConsoleHelper::SetColor(10);
                cout << "PRODUCT TO BE ADDED:" << endl;
                ConsoleHelper::SetColor(11);
                cout << "Category: " << category << endl;
                cout << "Name: " << name << endl;
                cout << "Price: Rs" << fixed << setprecision(2) << price << endl;
                cout << "Quantity: " << qty << endl;
                ConsoleHelper::SetColor(15);
                cout << "===============================================" << endl;
                ConsoleHelper::SetColor(7);
                PRODUCT product(category, name, price, qty);
                if (repo)
                {
                    repo->addProduct(product);
                    repo->saveToFile();
                    ConsoleHelper::SetColor(10);
                    cout << "Product added successfully!" << endl;
                }
                ConsoleHelper::SetColor(13);
                cout << "Press Enter to continue...";
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                break;
            }
            case 4:
                if (repo)
                {
                    repo->removeProduct();
                    repo->saveToFile();
                }
                ConsoleHelper::SetColor(13);
                cout << "Press Enter to continue...";
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                ConsoleHelper::SetColor(7);
                break;
            case 5:
                if (repo)
                {
                    repo->updateProduct();
                    repo->saveToFile();
                }
                ConsoleHelper::SetColor(13);
                cout << "Press Enter to continue...";
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                break;
            case 6:
            {
                string name;
                ConsoleHelper::SetColor(7);
                cout << "Enter product name to search: ";
                getline(cin, name);
                if (repo)
                {
                    repo->searchByName(name);
                }
                ConsoleHelper::SetColor(13);
                cout << "Press Enter to continue...";
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                ConsoleHelper::SetColor(7);
                break;
            }
            case 7:
            ConsoleHelper::SetColor(12);
                cout << "Admin logout." << endl;
                adminLoggedIn = false;
                break;
            default:
            ConsoleHelper::SetColor(12);
                cout << "⚠️ Invalid choice. Try again." << endl;
        }
    }
}


void ADMIN::viewProduct(std::string category)
{
    int choice;
    ConsoleHelper::SetColor(15);
    ConsoleHelper::PrintDivider();
    ConsoleHelper::SetColor(10);
    cout << "[1] View Products Category " << endl;
    cout << "[2] View Product Stock" << endl;
    ConsoleHelper::SetColor(15);
    ConsoleHelper::PrintDivider();
    ConsoleHelper::ResetColor();
    cout << "Enter choice: ";
    cin>>choice;

    if (choice==1)
    {
        repo->searchByCategory(category);
    }
    else if(choice==2)
    {
        repo->getAllProducts(true);
    }
    else
    {
        cout<<"⚠️ Product info not found in repositroy"<<endl;
    }
}


void ADMIN::searchProduct(std::string productName)
{
    if (repo)
    {
        repo->searchByName(productName);
    }
    else
    {
        cout << "⚠️ Product repository not available." << endl;
    }
}

void ADMIN::handleAdminLoginUI(AUTHORITY_SERVICE& auth_service, PRODUCT_REPO& repo, BILL_SERVICE& bill_service) 
{
    string adminPass;
    cout << "Enter admin passcode (Tab to show/hide): ";
    adminPass= ConsoleHelper::getPassword();
    
    if(adminPass.empty())
    {
        cout << "⚠️ Error: Admin passcode cannot be empty!" << endl;
        cout << "Press Enter to continue...";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return;
    }

    if (!auth_service.verifyAdmin(adminPass))
    {
        ConsoleHelper::SetColor(12);
        cout << "⚠️ Invalid Passcode." << endl;
        ConsoleHelper::SetColor(13);
        cout << "Press Enter to continue...";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return;
    }
     ConsoleHelper::SetColor(10);
    cout << "Admin login successful." << endl;

ADMIN admin(adminPass, repo, auth_service, bill_service);    admin.startSession();
    ConsoleHelper::SetColor(13);
    cout << "Press Enter to continue...";
    ConsoleHelper::ResetColor();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}
