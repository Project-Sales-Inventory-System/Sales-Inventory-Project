/*
- class ADMIN : Represents admin user in the system, inherits from USER class
- string passcode : stores the admin passcode used for authentication
- ADMIN(const std:: string & pass ) : Constructor to initialize admin with passcode and &pass: passcode is passed by reference variable pass
- bool authenticate(AUTHORITY_SERVICE& auth) : Authenticates admin using AUTHORITY_SERVICE, auth Reference to AUTHORITY_SERVICE
- void performAction() : Displays messages indicating admin's action
- std:: string getUsername() const : get username of the admin
- void viewProduct() : Displays all available Product
- void searchProduct(std::string) : search specific product by its name
- void manageProduct(std:: string) : manages product by its name
- void deleteProduct(std:: string productName) : delete product by its name
- void updateProduct(PRODUCT product) : Updates product details and product: PRODUCT object with updated data
- void manageSalesReport() : manages sales report
- void viewAllUsers() : Displays all registered users
- void generateSalesReport() : Generates sales report
*/
#pragma once
#include "USER.h"
#include "../include/PRODUCT.h"
#include "../include/AUTHORITY_SERVICE.h"
#include "../include/BILL_SERVICE.h" 
#include "PRODUCT_REPO.h"
#include <string>
#include <vector>

class ADMIN : public USER
{
private:
    PRODUCT_REPO* repo;
    AUTHORITY_SERVICE* auth_service;
    BILL_SERVICE* bill_service; 
    
    void AdminMenu();
    void handleUserManagement();
    void manageSalesReports(); 
    std::string passcode;
public:
ADMIN(const std::string& pass, PRODUCT_REPO& repository, AUTHORITY_SERVICE& auth_svc, BILL_SERVICE& bill_svc);    
    bool authenticate(AUTHORITY_SERVICE& auth);
    void performAction();
    std::string getUsername() const;
    void viewProduct(std::string category) override;
    void searchProduct(std::string productName) override;
    void startSession();
    
    static void handleAdminLoginUI(AUTHORITY_SERVICE& auth_service, PRODUCT_REPO& repo, BILL_SERVICE& bill_service);
};