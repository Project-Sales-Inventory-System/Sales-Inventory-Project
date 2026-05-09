#include"../include/SELLER.h"
#include"../include/USER.h"
#include"../include/BILL.h"
#include"../include/PRODUCT.h"
#include"../include/AUTHORITY_SERVICE.h"
#include"../include/ConsoleHelper.h"
#include"../include/USER_ACCOUNT.h"
#include"../include/PRODUCT_REPO.h"
#include<string>
#include<iostream>
#include<iomanip>
#include<limits>
#include<vector>

SELLER::SELLER(USER_ACCOUNT sDetails, PRODUCT_REPO& repository){
    user_acc = sDetails;
    repo = &repository;
}

std::string SELLER::getUsername() const{
    return user_acc.getUsername();
}

bool SELLER::authenticate(AUTHORITY_SERVICE& auth) {
    return auth.verifyClient(user_acc.getUsername(), "");
}

void SELLER::performAction(){
    std::cout << "Seller interacting" << std::endl;
}

void SELLER::SellerMenu()
{
    ConsoleHelper::SetColor(11);
    ConsoleHelper::PrintHeader("--------SELLER MENU -------");
    ConsoleHelper::ResetColor();
    ConsoleHelper::PrintDivider();
    std::cout << "[1] Add Product"    << std::endl;
    std::cout << "[2] Search Product" << std::endl;
    std::cout << "[3] View Products"  << std::endl;
    std::cout << "[4] Logout"         << std::endl;
    std::cout << "Enter your choice: ";
}

void SELLER::viewProduct(std::string){
    ConsoleHelper::ClearScreen();
    if (repo)
    {
        repo->getAllProducts(false);
    }
}

void SELLER::displayResults(const std::vector<PRODUCT>& results)
{
    ConsoleHelper::SetColor(10);
    std::cout << "\nSEARCH RESULTS" << std::endl;
    std::cout << std::string(60, '=') << std::endl;
    ConsoleHelper::SetColor(15);
    std::cout << std::left
              << std::setw(5)  << "NO"
              << std::setw(20) << "NAME"
              << std::setw(15) << "CATEGORY"
              << std::setw(10) << "PRICE"
              << "QUANTITY" << std::endl;
    std::cout << std::string(60, '-') << std::endl;

    for (int i = 0; i < (int)results.size(); i++)
    {
        ConsoleHelper::SetColor(11);
        std::cout << std::left
                  << std::setw(5)  << i + 1
                  << std::setw(20) << results[i].getName()
                  << std::setw(15) << results[i].getCategory()
                  << std::setw(10) << std::fixed << std::setprecision(2) << results[i].getPrice()
                  << results[i].getQuantity() << std::endl;
    }
    ConsoleHelper::SetColor(15);
    std::cout << std::string(60, '-') << std::endl;
    ConsoleHelper::ResetColor();
}

void SELLER::searchProduct(std::string keyword){
    ConsoleHelper::ClearScreen();
    ConsoleHelper::PrintHeader("SEARCH PRODUCTS");
    ConsoleHelper::PrintHeader("-SEARCH OPTION-");
    ConsoleHelper::PrintDivider();
    std::cout << "[1] Search by Product Name" << std::endl;
    std::cout << "[2] Search by Category"     << std::endl;
    std::cout << "[3] Back to Menu"           << std::endl;
    ConsoleHelper::PrintDivider();
    std::cout << "Enter your choice: ";

    int searchChoice;
    std::cin >> searchChoice;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    switch(searchChoice)
    {
        case 1:
        {
            std::string productName;
            std::cout << "Enter product name to search: ";
            std::getline(std::cin, productName);

            if (productName.empty())
            {
                ConsoleHelper::SetColor(12);
                std::cout << "⚠️ Product name cannot be empty!" << std::endl;
                ConsoleHelper::ResetColor();
            }
            else if (repo)
            {
                std::vector<PRODUCT> results = repo->searchByName(productName);
                if (results.empty())
                {
                    ConsoleHelper::SetColor(12);
                    std::cout << "⚠️ No products found." << std::endl;
                    ConsoleHelper::ResetColor();
                }
                else
                {
                    displayResults(results);
                }
            }
            break;
        }
        case 2:
        {
            std::string category;
            std::cout << "Enter product category to search: ";
            std::getline(std::cin, category);

            if (category.empty())
            {
                ConsoleHelper::SetColor(12);
                std::cout << "⚠️ Category cannot be empty!" << std::endl;
                ConsoleHelper::ResetColor();
            }
            else if (repo)
            {
                std::vector<PRODUCT> results = repo->searchByCategory(category);
                if (results.empty())
                {
                    ConsoleHelper::SetColor(12);
                    std::cout << "⚠️ No products found." << std::endl;
                    ConsoleHelper::ResetColor();
                }
                else
                {
                    displayResults(results);
                }
            }
            break;
        }
        case 3:
            return;
        default:
            ConsoleHelper::SetColor(12);
            std::cout << "⚠️ Invalid choice!" << std::endl;
            ConsoleHelper::ResetColor();
    }

    std::cout << "\nPress Enter to continue...";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

void SELLER::addProduct(PRODUCT product){
    if (repo)
    {
        repo->addProduct(product);
        repo->saveToFile();
    }
    ConsoleHelper::SetColor(11);
    ConsoleHelper::PrintHeader("--------PRODUCT ADDED SUCCESSFULLY-------");
    ConsoleHelper::ResetColor();
    ConsoleHelper::PrintDivider();
}

void SELLER::startSession()
{
    bool sellerLoggedIn = true;
    while (sellerLoggedIn)
    {
        SellerMenu();
        int choice;
        std::cin >> choice;

        if (std::cin.fail())
        {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            ConsoleHelper::SetColor(12);
            std::cout << "⚠️ Invalid input. Try again." << std::endl;
            ConsoleHelper::ResetColor();
            continue;
        }

        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        switch (choice)
        {
            case 1:
            {
                std::string category, name;
                double price;
                int qty;
                std::cout << "Enter product category: ";
                std::getline(std::cin, category);
                std::cout << "Enter product name: ";
                std::getline(std::cin, name);
                std::cout << "Enter product price: ";
                std::cin >> price;
                std::cout << "Enter product quantity: ";
                std::cin >> qty;
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                PRODUCT product(category, name, price, qty);
                addProduct(product);
                ConsoleHelper::SetColor(13);
                std::cout << "Press Enter to continue...";
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                break;
            }
            case 2:
                searchProduct("");
                break;
            case 3:
                viewProduct("");
                ConsoleHelper::SetColor(13);
                std::cout << "Press Enter to continue...";
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                break;
            case 4:
                ConsoleHelper::SetColor(10);
                std::cout << "Logging out..." << std::endl;
                ConsoleHelper::ResetColor();
                sellerLoggedIn = false;
                break;
            default:
                ConsoleHelper::SetColor(12);
                std::cout << "⚠️ Invalid choice. Try again." << std::endl;
                ConsoleHelper::ResetColor();
        }
    }
}