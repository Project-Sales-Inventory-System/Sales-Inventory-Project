#include <iostream>
#include <limits>
#include <vector>
#include <iomanip>
#include "SYSTEM.h"
#include "USER_ACCOUNT.h"
#include "../include/ConsoleHelper.h"
#include "../include/ADMIN.h"
using namespace std;

// Constructor
ADMIN::ADMIN(const std::string & pass, PRODUCT_REPO& repository, AUTHORITY_SERVICE& auth_svc) 
    : passcode(pass)
{
    repo = &repository;
    auth_service = &auth_svc;
}

// Authenticate admin with passcode
bool ADMIN::authenticate(AUTHORITY_SERVICE& auth)
{
    return auth.verifyAdmin(passcode);
}

// Perform admin action
void ADMIN::performAction()
{
    AdminMenu();
}

// Admin Menu - display only
void ADMIN::AdminMenu()
{
    ConsoleHelper::ClearScreen();
    ConsoleHelper::SetColor(11);
    ConsoleHelper::PrintHeader("-------ADMIN PANEL-------");
    ConsoleHelper::ResetColor();
    ConsoleHelper::PrintDivider();
    cout << "\n--- Admin Panel ---\n";
    cout << "1. Manage User\n";
    cout << "2. View Products by Category\n";
    cout << "3. Add Product\n";
    cout << "4. Remove Product\n";
    cout << "5. Update Product\n";
    cout << "6. Search Product\n";
    cout << "7. Logout\n";
    cout << "Enter Choice: ";
}

void ADMIN::handleUserManagement()
{
    if (!auth_service)
    {
        cout << "Auth service not available." << endl;
        return;
    }

    vector<USER_ACCOUNT> users = auth_service->getAllRegisteredUsers();
    if (users.empty())
    {
        cout << "No users registered." << endl;
        return;
    }

    cout << endl;
    cout << "===============================================" << endl;
    cout << "REGISTERED USERS" << endl;
    cout << "===============================================" << endl;
    cout << "INDEX | NAME | USERNAME | ROLE | EMAIL" << endl;
    cout << "-----------------------------------------------" << endl;
    for (int i = 0; i < users.size(); i++)
    {
        cout << i + 1 << "     | "
             << users[i].getFullname() << " | "
             << users[i].getUsername() << " | "
             << (users[i].getAuthority() == ClientSELLER ? "Seller" : "Buyer") << " | "
             << users[i].getMailAddress()
             << endl;
    }
    cout << "-----------------------------------------------" << endl;
    
    string usernameToDelete;
    cout << "Enter username to delete or 0 to go back: ";
    getline(cin, usernameToDelete);

    if (usernameToDelete == "0")
    {
        return;
    }
    if (auth_service->deleteUserByUsername(usernameToDelete))
    {
        cout << "User deleted successfully!" << endl;
        cout << "\n===============================================" << endl;
        cout << "UPDATED USER LIST" << endl;
        cout << "===============================================" << endl;
        
        vector<USER_ACCOUNT> updatedUsers = auth_service->getAllRegisteredUsers();
        if (updatedUsers.empty())
        {
            cout << "No users registered." << endl;
        }
        else
        {
            cout << "INDEX | NAME | USERNAME | ROLE | EMAIL" << endl;
            cout << "-----------------------------------------------" << endl;
            for (int i = 0; i < updatedUsers.size(); i++)
            {
                cout << i + 1 << "     | "
                     << updatedUsers[i].getFullname() << " | "
                     << updatedUsers[i].getUsername() << " | "
                     << (updatedUsers[i].getAuthority() == ClientSELLER ? "Seller" : "Buyer") << " | "
                     << updatedUsers[i].getMailAddress()
                     << endl;
            }
            cout << "-----------------------------------------------" << endl;
        }
    }
    else
    {
        cout << "User not found or failed to delete." << endl;
    }
    cout << "Press Enter to continue...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

// Get username
std::string ADMIN::getUsername() const
{
    return "ADMIN";
}

// Admin session handler
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
            cout << "Invalid input. Try again." << endl;
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
                cout << "Press Enter to continue...";
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
                cout << "===============================================" << endl;
                cout << "PRODUCT TO BE ADDED:" << endl;
                cout << "Category: " << category << endl;
                cout << "Name: " << name << endl;
                cout << "Price: Rs" << fixed << setprecision(2) << price << endl;
                cout << "Quantity: " << qty << endl;
                cout << "===============================================" << endl;
                
                PRODUCT product(category, name, price, qty);
                if (repo)
                {
                    repo->addProduct(product);
                    repo->saveToFile();
                    cout << "Product added successfully!" << endl;
                }
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
                cout << "Press Enter to continue...";
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                break;
            case 5:
                if (repo)
                {
                    repo->updateProduct();
                    repo->saveToFile();
                }
                cout << "Press Enter to continue...";
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                break;
            case 6:
            {
                string name;
                cout << "Enter product name to search: ";
                getline(cin, name);
                if (repo)
                {
                    repo->searchByName(name);
                }
                cout << "Press Enter to continue...";
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                break;
            }
            case 7:
                cout << "Admin logout." << endl;
                adminLoggedIn = false;
                break;
            default:
                cout << "Invalid choice. Try again." << endl;
        }
    }
}

// View product (implementing pure virtual)
void ADMIN::viewProduct(std::string category)
{
    // Admin can view all products in a category
    if (repo)
    {
        repo->searchByCategory(category);
    }
    else
    {
        cout << "Product repository not available." << endl;
    }
}

// Search product (implementing pure virtual)
void ADMIN::searchProduct(std::string productName)
{
    if (repo)
    {
        repo->searchByName(productName);
    }
    else
    {
        cout << "Product repository not available." << endl;
    }
}

// UI Handler for Admin Login - All console input/output here
void ADMIN::handleAdminLoginUI(AUTHORITY_SERVICE& auth_service, PRODUCT_REPO& repo)
{
    string adminPass;
    cout << "Enter admin passcode (Tab to show/hide): ";
    adminPass= ConsoleHelper::getPassword();
    
    if(adminPass.empty())
    {
        cout << "Error: Admin passcode cannot be empty!" << endl;
        cout << "Press Enter to continue...";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return;
    }

    if (!auth_service.verifyAdmin(adminPass))
    {
        cout << "Invalid Passcode." << endl;
        cout << "Press Enter to continue...";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return;
    }

    cout << "Admin login successful." << endl;

    ADMIN admin(adminPass, repo, auth_service);
    admin.startSession();

    cout << "\nPress Enter to continue...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}
