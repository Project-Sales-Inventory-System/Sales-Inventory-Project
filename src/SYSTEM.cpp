#include "../include/SYSTEM.h"
#include "../include/USER.h"
#include "../include/USER_ACCOUNT.h"
#include "../include/BUYER.h"
#include "../include/SELLER.h"
#include "../include/ADMIN.h"
#include "../include/ConsoleHelper.h"
#include "../include/UI_config.h"
#include "../include/BILL_SERVICE.h"
#include "../include/PRODUCT_REPO.h"
#include "../include/BILL.h"
#include <iostream>
#include <limits>
#include <cctype>

using namespace std;

SYSTEM::SYSTEM()
    : current_user(nullptr), isAdminLoggedin(false), isRegistered(false) {
   
    repo = new PRODUCT_REPO();
    auth = new AUTHORITY_SERVICE();
    bill_service = new BILL_SERVICE();
}

SYSTEM::~SYSTEM() {
    // Clean up heap memory to prevent leaks
    delete repo;
    delete auth;
    delete bill_service;
    if (current_user) {
        delete current_user;
    }
}

bool SYSTEM::registerAccount(const USER_ACCOUNT& account) {
    return auth->registerUser(account);
}

USER* SYSTEM::loginAccount(const std::string& username, const std::string& password) {
    if (current_user) {
        delete current_user;
        current_user = nullptr;
    }
    current_user = auth->login(username, password);
    isAdminLoggedin = false;
    return current_user;
}

bool SYSTEM::adminLogin(const std::string& passcode) {
    isAdminLoggedin = auth->verifyAdmin(passcode);
    return isAdminLoggedin;
}

std::vector<USER_ACCOUNT> SYSTEM::getAllUsers() const {
    return auth->getAllRegisteredUsers();
}

bool SYSTEM::deleteUser(const std::string& username) {
    return auth->deleteUserByUsername(username);
}

USER* SYSTEM::process(bool isLogin, USER_ACCOUNT account) {
    if (!isLogin) {
        registerAccount(account);
        return nullptr;
    } else {
        return loginAccount(account.getUsername(), account.getPassword());
    }
}

void SYSTEM::addProduct(PRODUCT product) {
    if (isAdminLoggedin) {
        repo->addProduct(product);
        return;
    }
    if (current_user == nullptr) {
        ConsoleHelper::SetColor(12);
        cout << "⚠️ No user logged in." << endl;
        ConsoleHelper::ResetColor();
        return;
    }
    if (current_user->getAuthority() != ClientSELLER) {
        ConsoleHelper::SetColor(12);
        cout << "⚠️ Access not granted! Only sellers or admins can add products." << endl;
        ConsoleHelper::ResetColor();
        return;
    }
    repo->addProduct(product);
}


void SYSTEM::searchProduct() {
    ConsoleHelper::ClearScreen();
    ConsoleHelper::SetColor(10);
    ConsoleHelper::PrintHeader("SEARCH PRODUCTS");
    ConsoleHelper::SetColor(15);
    ConsoleHelper::PrintDivider();
    ConsoleHelper::SetColor(10);
    cout << "[1] Search by Product Name" << endl;
    cout << "[2] Search by Category" << endl;
    cout << "[3] Back to Menu" << endl;
     ConsoleHelper::SetColor(15);
    ConsoleHelper::PrintDivider();
    ConsoleHelper::ResetColor();
    cout << "Enter your choice: ";

    int choice;
    if (!(cin >> choice)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return;
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    if (choice == 3) return;

    string query;
    cout << "Enter search term: ";
    getline(cin, query);

    if (query.empty()) {
        ConsoleHelper::SetColor(12);
        cout << "⚠️ Error: Search term cannot be empty!" << endl;
        ConsoleHelper::ResetColor();
        return;
    }

    vector<PRODUCT> results;
    if (choice == 1) {
        results = repo->searchByName(query);
    } else if (choice == 2) {
        results = repo->searchByCategory(query);
    } else {
        ConsoleHelper::SetColor(12);
        cout << "⚠️ Invalid choice!" << endl;
        ConsoleHelper::ResetColor();
        return;
    }

    if (results.empty()) {
        ConsoleHelper::SetColor(12);
        cout << "⚠️ No products found matching: " << query << endl;
        ConsoleHelper::ResetColor();
    } else {
        ConsoleHelper::SetColor(10);
        cout << "\n" << string(60, '=') << endl;
        cout << "SEARCH RESULTS" << endl;
        cout << string(60, '=') << endl;
        cout << "INDEX | NAME | CATEGORY | PRICE | QUANTITY" << endl;
        cout << string(60, '-') << endl;
        ConsoleHelper::ResetColor();
        for (int i = 0; i < (int)results.size(); i++) {
            cout << (i+1) << "     | " 
                 << results[i].getName() << " | " 
                 << results[i].getCategory() << " | " 
                 << results[i].getPrice() << " | " 
                 << results[i].getQuantity() << endl;
        }
        cout << string(60, '=') << endl;
    }
    ConsoleHelper::SetColor(13);
    cout << "\nPress Enter to continue...";
    ConsoleHelper::ResetColor();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

void SYSTEM::removeProduct() {
    if (!isAdminLoggedin) {
        ConsoleHelper::SetColor(12);
        cout << "⚠️ Access not granted!" << endl;
        ConsoleHelper::ResetColor();
        return;
    }
    repo->removeProduct();
}

void SYSTEM::updateProduct() {
    if (!isAdminLoggedin) {
        ConsoleHelper::SetColor(12);
        cout << "⚠️ Access not granted!" << endl;
        ConsoleHelper::ResetColor();
        return;
    }
    repo->updateProduct();
}

void SYSTEM::getAllProducts() {
    if (isAdminLoggedin) {
        repo->getAllProducts(true);
    } else if (current_user != nullptr) {
        repo->getAllProducts(false);
    } else {
        cout << "Please log in to view the full catalog." << endl;
    }
}

void SYSTEM::saveToFile() {
    repo->saveToFile();
}

PRODUCT_REPO* SYSTEM::getRepo() {
    return repo;
}

AUTHORITY_SERVICE* SYSTEM::getAuthService() {
    return auth;
}

void SYSTEM::displayGuestMenu() {
    ConsoleHelper::Header();
    const int terminalWidth = 80;
    std::string line = std::string(44, '=');
    std::string message = "    👥 Welcome to our System Portal 👥";

    int padding = (terminalWidth - line.length()) / 2;
    
    ConsoleHelper::SetColor(15);
    cout << string(padding, ' ') << line << endl;
    ConsoleHelper::SetColor(10);
    cout << string(padding, ' ') << message << endl;
    ConsoleHelper::SetColor(15);
    cout << string(padding, ' ') << line << endl;

    ConsoleHelper::SetColor(12);
    cout << "Guideline:" << endl;
    cout << "Register to the System if you wish to buy/sell." << endl;
    cout<< "If you're already a registered user"<<endl;
    cout<<"Proceed to next Menu exiting this Menu"<<endl;
    cout << "Navigate with number keys for speed." << endl;
    ConsoleHelper::SetColor(15);
    ConsoleHelper::PrintDivider();
    ConsoleHelper::SetColor(10);
    cout << "[1] Register" << endl;
    cout << "[2] Search Products" << endl;
    cout << "[3] View All Products" << endl;
    cout << "[4] Exit Guest Mode" << endl;
    ConsoleHelper::PrintDivider();
    ConsoleHelper::ResetColor();
    cout << "Enter choice: ";
}

void SYSTEM::displayMainMenu() {
    ConsoleHelper::Header();
    const int terminalWidth = 80;
    std::string line = std::string(44, '=');
    std::string message = "Welcome to our Management Portal";

    int padding = (terminalWidth - line.length()) / 2;

    ConsoleHelper::SetColor(15);
    cout << string(padding, ' ') << line << endl;
    ConsoleHelper::SetColor(10);
    cout << string(padding, ' ') << message << endl;
    ConsoleHelper::SetColor(15);
    cout << string(padding, ' ') << line << endl;

    ConsoleHelper::SetColor(12);
    cout << "Guideline:" << endl;
    cout << "Please select your role to continue." << endl;
    cout << "Navigate with number keys." << endl;
    ConsoleHelper::SetColor(15);
    ConsoleHelper::PrintDivider();
    ConsoleHelper::SetColor(10);
    cout << "[1] User Login" << endl;
    cout << "[2] Admin Login" << endl;
    cout << "[3] Exit" << endl;
    ConsoleHelper::PrintDivider();
    ConsoleHelper::ResetColor();
    cout << "Enter choice: ";
}

void SYSTEM::handleRegistration() {
    bool success = USER::handleUserRegistrationUI(*auth);
    if (success) {
        isRegistered = true;
    }
}

void SYSTEM::handleUserLogin() {
    USER::handleUserLoginUI(*auth, *repo, *bill_service);
}

void SYSTEM::handleAdminLogin() {
    ADMIN::handleAdminLoginUI(*auth, *repo, *bill_service);
}
void SYSTEM::viewProductList() {
    ConsoleHelper::ClearScreen();
    repo->getAllProducts(false);
    ConsoleHelper::SetColor(13);
    cout << "\nPress Enter to return...";
    ConsoleHelper::ResetColor();
    cin.get();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

void SYSTEM::guestMenu() {
    bool end = true;
    while (end) {
        displayGuestMenu();
        int choice;
        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch (choice) {
            case 1: handleRegistration(); break;
            case 2: searchProduct(); break;
            case 3: viewProductList(); break;
            case 4: end = false; break;
            default: cout << "⚠️ Invalid input." << endl;
        }
    }
}

void SYSTEM::run() {
    bool running = true;
    while (running) {
        displayMainMenu();
        int choice;
        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch (choice) {
            case 1: handleUserLogin(); break;
            case 2: handleAdminLogin(); break;
            case 3: running = false; break;
            default: cout << "⚠️ Invalid input." << endl;
        }
    }
}