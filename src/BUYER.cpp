#include"../include/BUYER.h"
#include<iostream>
#include<iomanip>
#include<limits>
#include<vector>
using namespace std;
#include"../include/ConsoleHelper.h"
#include"../include/USER.h"
#include"../include/CART.h"
#include"../include/BILL.h"
#include"../include/BILL_SERVICE.h"
#include"../include/PRODUCT.h"
#include"../include/AUTHORITY_SERVICE.h"

BUYER::BUYER(USER_ACCOUNT Bdetails, PRODUCT_REPO& repository, BILL_SERVICE& bill_svc)
{
    user_acc = Bdetails;
    repo = &repository;
    bill_service = &bill_svc;
}

bool BUYER::authenticate(AUTHORITY_SERVICE& auth) {
    return auth.verifyClient(user_acc.getUsername(), "");
}

void BUYER::performAction() {
    cout << "Buyer interacting" << endl;
}

std::string BUYER::getUsername() const {
    return user_acc.getUsername();
}

int BUYER::getCartItemCount() const {
    return cart.getItemCount();
}

double BUYER::getCartTotal() {
    return cart.calculateTotal();
}

void BUYER::BuyerMenu()
{
    ConsoleHelper::Header();
    const int terminalWidth = 80;
    std::string line = std::string(44, '=');
    std::string message = "   👥 BUYER MENU 👥";

    int padding = (terminalWidth - line.length()) / 2;
    
    ConsoleHelper::SetColor(15);
    std::cout << std::string(padding, ' ') << line << std::endl;
    ConsoleHelper::SetColor(10);
    std::cout << std::string(padding, ' ') << message << std::endl;
    ConsoleHelper::SetColor(15);
    std::cout << std::string(padding, ' ') << line << std::endl;
    ConsoleHelper::SetColor(10);
    cout << "[1] View Product" << endl;
    cout << "[2] Search Product" << endl;
    cout << "[3] Edit Cart" << endl;
    cout << "[4] Request Bill" << endl;
    cout << "[5] Logout" << endl;
    cout << "Enter your choice: ";
}

void BUYER::viewProduct(std::string) {
    ConsoleHelper::ClearScreen();
    if (repo)
    {
        repo->getAllProducts(false);
    }
    ConsoleHelper::SetColor(13);
    cout << "\nPress Enter to return to menu...";
    ConsoleHelper::ResetColor();
    cin.get();
}

void BUYER::searchProduct(std::string keyword) {
    bool search_again = true;

    while (search_again) {
        ConsoleHelper::Header();
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
        ConsoleHelper::SetColor(7);
        cout << "Enter your choice: ";

        int searchChoice;
        cin >> searchChoice;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if (searchChoice == 3) return;

        vector<PRODUCT> results;

        switch (searchChoice) {
            case 1: {
                string productName;
                cout << "Enter product name to search: ";
                getline(cin, productName);
                if (productName.empty()) {
                    ConsoleHelper::SetColor(12);
                    cout << "⚠️ Error: Product name cannot be empty!" << endl;
                    ConsoleHelper::ResetColor();
                } else {
                    results = repo->searchByName(productName);
                }
                break;
            }
            case 2: {
                string category;
                cout << "Enter product category to search: ";
                getline(cin, category);
                if (category.empty()) {
                    ConsoleHelper::SetColor(12);
                    cout << "⚠️ Error: Category cannot be empty!" << endl;
                    ConsoleHelper::ResetColor();
                } else {
                    results = repo->searchByCategory(category);
                }
                break;
            }
            default:
                ConsoleHelper::SetColor(12);
                cout << "⚠️ Invalid choice!" << endl;
                ConsoleHelper::ResetColor();
                continue;
        }

        if (results.empty()) {
            ConsoleHelper::SetColor(12);
            cout << "⚠️ No result found. Press Enter...";
            ConsoleHelper::ResetColor();
            cin.get();
            continue;
        }

        ConsoleHelper::SetColor(15);
        cout << "\n===============================================" << endl;
        ConsoleHelper::SetColor(10);
        cout << "SEARCH RESULTS" << endl;
        ConsoleHelper::SetColor(15);
        cout << "===============================================" << endl;
        ConsoleHelper::SetColor(10);
        cout << "INDEX | NAME | CATEGORY | PRICE | QUANTITY" << endl;
        ConsoleHelper::SetColor(15);
        cout << "-----------------------------------------------" << endl;
        ConsoleHelper::SetColor(7);
        for (int i = 0; i < (int)results.size(); i++) {
            ConsoleHelper::SetColor(11);
            cout << i + 1 << "     | "
                 << results[i].getName() << " | "
                 << results[i].getCategory() << " | "
                 << results[i].getPrice() << " | "
                 << results[i].getQuantity()
                 << endl;
        }
        ConsoleHelper::SetColor(15);
        cout << "-----------------------------------------------" << endl;
        ConsoleHelper::ResetColor();

        bool interacting = true;
        while (interacting) {
            ConsoleHelper::SetColor(15);
            ConsoleHelper::PrintDivider();
            ConsoleHelper::SetColor(10);
            cout << "\nADD TO CART: Enter index number and A, e.g. [1A]" << endl;
            cout << "TO VIEW CART: Enter V" << endl;
            cout << "TO SEARCH AGAIN: Enter S" << endl;
            cout << "TO EXIT: Enter 0" << endl;
            ConsoleHelper::SetColor(15);
            ConsoleHelper::PrintDivider();
            ConsoleHelper::SetColor(7);
            cout << "Enter your choice: ";

            string choice;
            getline(cin, choice);

            if (choice == "0") {
                search_again = false;
                interacting = false;
    
            }
            else if (choice.size() >= 2 && (choice.back() == 'a' || choice.back() == 'A')) {
                string indexStr = choice.substr(0, choice.size() - 1);
                int id = stoi(indexStr);
                if (id < 1 || id > (int)results.size()) {
                    ConsoleHelper::SetColor(12);
                    cout << "⚠️ Invalid index" << endl;
                    ConsoleHelper::ResetColor();
                } else {
                    ConsoleHelper::SetColor(7);
                    cout << "Enter quantity to add: ";
                    int quantity;
                    cin >> quantity;
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');

                    if (quantity <= 0) {
                        ConsoleHelper::SetColor(12);
                        cout << "⚠️ Invalid quantity!" << endl;
                        ConsoleHelper::ResetColor();
                    } else if (quantity > results[id - 1].getQuantity()) {
                        ConsoleHelper::SetColor(10);
                        cout << "Only " << results[id - 1].getQuantity() << " available in stock." << endl;
                        ConsoleHelper::ResetColor();
                    } else {
                        PRODUCT item = results[id - 1];
                        item.setQuantity(quantity);
                        cart.addItem(item);
                        ConsoleHelper::SetColor(10);
                        cout << "✓ " << quantity << "x " << results[id - 1].getName() << " added to Cart!!" << endl;
                        ConsoleHelper::ResetColor();
                    }
                }
            }
            else if (choice == "s" || choice == "S") {
                interacting = false;
            }
            else if (choice == "v" || choice == "V") {
                cart.viewCart();
            }
            else {
                ConsoleHelper::SetColor(12);
                cout << "⚠️ Invalid input" << endl;
                ConsoleHelper::ResetColor();
            }
        }
    }
}

void BUYER::startSession()
{
    ConsoleHelper::Header();
    bool buyerLoggedIn = true;
    while (buyerLoggedIn)
    {
        ConsoleHelper::ClearScreen();
        BuyerMenu();
        int choice;
        cin >> choice;

        if (cin.fail())
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            ConsoleHelper::SetColor(12);
            cout << "⚠️ Invalid input. Try again." << endl;
            ConsoleHelper::ResetColor();
            continue;
        }

        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch (choice)
        {
            case 1: viewProduct(""); break;
            case 2: searchProduct(""); break;
            case 3: editCart(); break;
            case 4: requestBill(); break;
            case 5:
                ConsoleHelper::SetColor(10);
                cout << "Thank you for shopping!" << endl;
                ConsoleHelper::ResetColor();
                buyerLoggedIn = false;
                break;
            default:
                ConsoleHelper::SetColor(12);
                cout << "⚠️ Invalid choice" << endl;
                ConsoleHelper::ResetColor();
                cout << "Press Enter to continue...";
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
}

void BUYER::editCart() {
    ConsoleHelper::Header();
    ConsoleHelper::SetColor(10);
    ConsoleHelper::PrintHeader("EDIT CART");
    ConsoleHelper::ResetColor();

    bool editing = true;
    while (editing) {
        cart.viewCart();
        if (cart.getItemCount() == 0) {
            ConsoleHelper::SetColor(12);
            std::cout << "⚠️ Cart is empty!!" << std::endl;
            ConsoleHelper::ResetColor();
            ConsoleHelper::SetColor(13);
            cout << "Press Enter to continue...";
            ConsoleHelper::ResetColor();
            cin.get();
            break;
        }
        ConsoleHelper::ResetColor();
        std::cout << "[R] Remove Item | [U] Update Quantity | [B] Back: ";
        char choice;
        std::cin >> choice;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        if (choice == 'B' || choice == 'b') {
            editing = false;
            continue;
        }

        std::string productName;
        std::cout << "Enter exact product name: ";
        std::getline(std::cin >> std::ws, productName);

        if (choice == 'R' || choice == 'r') {
            cart.removeItem(productName);
        }
        else if (choice == 'U' || choice == 'u') {
            int qty;
            std::cout << "Enter new quantity: ";
            if (!(std::cin >> qty)) {
                std::cout << "Invalid quantity!" << std::endl;
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                continue;
            }
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            cart.updateQuantity(productName, qty);
        }

        std::cout << "\nPress Enter to refresh cart...";
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        ConsoleHelper::ClearScreen();
    }
}

void BUYER::requestBill() {
    ConsoleHelper::Header();
    ConsoleHelper::SetColor(10);
    ConsoleHelper::PrintHeader("REQUEST BILL");
    ConsoleHelper::ResetColor();
    ConsoleHelper::PrintDivider();

    if (cart.getItemCount() == 0) {
        ConsoleHelper::SetColor(12);
        cout << "⚠️ Your cart is empty! Add items before requesting a bill." << endl;
        ConsoleHelper::ResetColor();
        cout << "Press Enter to continue...";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return;
    }

    if (!bill_service) {
        ConsoleHelper::SetColor(12);
        cout << "⚠️ Bill service not available." << endl;
        ConsoleHelper::ResetColor();
        return;
    }

    BILL bill = bill_service->autoGenerateBill(cart);
    bill.displayBill();

    cout << "\nConfirm payment for Bill #" << bill.getBillId() << "? (Y/N): ";
    char confirm;
    cin >> confirm;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    if (confirm == 'Y' || confirm == 'y') {
        ConsoleHelper::SetColor(10);
        bill.confirmPayment();
        bill_service->autoConfirmSale(bill.getBillId(), *repo);
        ConsoleHelper::ResetColor();

        ConsoleHelper::SetColor(10);
        cout << "\n✓ Payment confirmed successfully!" << endl;
        cout << "✓ Sale recorded and inventory updated." << endl;
        ConsoleHelper::ResetColor();

        cart = CART();
    } else {
        ConsoleHelper::SetColor(12);
        cout << "\n✗ Payment cancelled." << endl;
        ConsoleHelper::ResetColor();
    }
    ConsoleHelper::SetColor(13);
    cout << "Press Enter to continue...";
    ConsoleHelper::ResetColor();
    cin.get();
}