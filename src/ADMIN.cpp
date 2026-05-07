#include <iostream>
#include <limits>
#include <vector>
#include <iomanip>
#include "../include/SYSTEM.h"
#include "../include/USER_ACCOUNT.h"
#include "../include/ConsoleHelper.h"
#include "../include/ADMIN.h"
#include "../include/UI_config.h"
using namespace std;

// Constructor
ADMIN::ADMIN(const std::string & pass, PRODUCT_REPO& repository, AUTHORITY_SERVICE& auth_svc, BILL_SERVICE& bill_svc) 
    : passcode(pass)
{
    repo = &repository;
    auth_service = &auth_svc;
    bill_service = &bill_svc;
}

// Authenticate admin with passcode
bool ADMIN::authenticate(AUTHORITY_SERVICE& auth)
{
    return auth.verifyAdmin(passcode);
}


void ADMIN::performAction()
{
    AdminMenu();
}


void ADMIN::AdminMenu()
{
   ConsoleHelper::Header();
    ConsoleHelper::SetColor(10);
    std::string line = std::string(44, '=');
    std::string message = "Welcome to our Admin Portal";
    ConsoleHelper::SetColor(15);
    ConsoleHelper::PrintDivider();
    ConsoleHelper::SetColor(11);
    cout << "[1]  Manage user" << endl;
    cout << "[2]  View Products by Category" << endl;
    cout << "[3]  Add Product" << endl;
    cout << "[4]  Remove Product" << endl;
    cout << "[5]  Update Product" << endl;
    cout << "[6]  Search Products" << endl;
    cout << "[7]  Manage Sales Reports" << endl;
    cout << "[8]  Logout" << endl;
    ConsoleHelper::SetColor(15);
    ConsoleHelper::PrintDivider();
    ConsoleHelper::ResetColor();
    cout << "Enter your Choice: ";
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
    ConsoleHelper::SetColor(10);
    cout << "===============================================" << endl;
    cout << "REGISTERED USERS" << endl;
    cout << "===============================================" << endl;
    ConsoleHelper::SetColor(15);
    cout << "INDEX | NAME | USERNAME | ROLE | EMAIL" << endl;
    cout << "-----------------------------------------------" << endl;
    ConsoleHelper::SetColor(10);
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
        cout << "User deleted successfully!" << endl;
        ConsoleHelper::SetColor(10);
        cout << "\n===============================================" << endl;
        cout << "UPDATED USER LIST" << endl;
        cout << "===============================================" << endl;
        vector<USER_ACCOUNT> updatedUsers = auth_service->getAllRegisteredUsers();
        if (updatedUsers.empty())
        {
            ConsoleHelper::SetColor(12);
            cout << "No users registered." << endl;
        }
        else
        {
            ConsoleHelper::SetColor(15);
            cout << "INDEX | NAME | USERNAME | ROLE | EMAIL" << endl;
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
                    ConsoleHelper::SetColor(13);
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
            {
                manageSalesReports();
                break;
            }
            case 8:
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


void ADMIN::manageSalesReports()
{
    if (!bill_service)
    {
        cout << "Bill service not available." << endl;
        return;
    }
    
    bool manageReports = true;
    while (manageReports)
    {
        ConsoleHelper::ClearScreen();
        ConsoleHelper::Header();
        ConsoleHelper::SetColor(10);
        cout << string(60, '=') << endl;
        cout << "MANAGE SALES REPORTS" << endl;
        cout << string(60, '=') << endl;
        ConsoleHelper::ResetColor();
        ConsoleHelper::PrintDivider();
        
        cout << "[1] View All Sales" << endl;
        cout << "[2] View Sales by Customer" << endl;
        cout << "[3] Back to Menu" << endl;
        ConsoleHelper::PrintDivider();
        cout << "Enter your choice: ";
        
        int reportChoice;
        cin >> reportChoice;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        
        switch (reportChoice)
        {
            case 1:
                bill_service->displayAllSales();
                break;
            case 2:
            {
                string customer;
                cout << "Enter customer username: ";
                getline(cin, customer);
                bill_service->displaySalesByCustomer(customer);
                break;
            }
            case 3:
                manageReports = false;
                break;
            default:
                cout << "⚠️ Invalid choice!" << endl;
                cout << "Press Enter to continue...";
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
}


void ADMIN::viewProduct(std::string category)
{
    // Admin can view all products in a category
    int choice;
    ConsoleHelper::SetColor(15);
    cout << "──────────────────────────────" << endl;
    ConsoleHelper::SetColor(11);
    cout << "[1] View Products Category " << endl;
    cout << "[2] View Product Stock" << endl;
    ConsoleHelper::SetColor(15);
    cout << "──────────────────────────────" << endl;
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
        cout << "⚠️ Invalid Passcode." << endl;
        cout << "Press Enter to continue...";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return;
    }

    cout << "Admin login successful." << endl;

    ADMIN admin(adminPass, repo, auth_service, bill_service);
    admin.startSession();
    ConsoleHelper::SetColor(13);
    cout << "Press Enter to continue...";
    ConsoleHelper::ResetColor();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}
