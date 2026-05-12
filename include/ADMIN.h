/*
class ADMIN : Represents admin user in the system, inherits from USER class

STANDARD LIBRARIES USED:
-vector:Used for storing collections of data.
-string:Used for text handling.

Data members
- PRODUCT_REPO* repo:Pointer to product repository used for product operations.
- AUTHORITY_SERVICE* auth_service:Pointer to authentication service used for admin/user verification.
- BILL_SERVICE* bill_service:Pointer to billing service used for report management.
- std::string passcode:Stores admin passcode for authentication.

Private member functions
- void AdminMenu():Displays the admin dashboard/menu.
- void handleUserManagement():Handles operations related to user management.
- void manageSalesReports():Handles sales report management operations.

Public member functions
- ADMIN(const std::string& pass,PRODUCT_REPO& repository,AUTHORITY_SERVICE& auth_svc,BILL_SERVICE& bill_svc)
    Constructor to initialize ADMIN object with:
    - admin passcode
    - product repository
    - authentication service
    - billing service

- bool authenticate(AUTHORITY_SERVICE& auth):Authenticates admin using AUTHORITY_SERVICE.
    Parameters:
    - auth : Reference to AUTHORITY_SERVICE object
    Returns:
    - true  -> authentication successful
    - false -> authentication failed

- void performAction():Performs admin-specific operations and actions.
- std::string getUsername() const:Returns admin username.
- void viewProduct(std::string category = "") override:Displays all available products.
- void searchProduct(std::string productName) override:Searches for a specific product by its name.
- void startSession():Starts admin interaction session and dashboard.
- void viewAllUsers():Displays all registered users in the system.
- void deleteProduct(std::string productName):Deletes a product by its name.
- void updateProduct(PRODUCT product):Updates product information/details.
- void manageProduct(std::string productName):Manages product operations such as update/delete.
- void generateSalesReport():Generates sales report using BILL_SERVICE.
- void manageSalesReport():Displays and manages sales reports.
- static void handleAdminLoginUI(AUTHORITY_SERVICE& auth_service, PRODUCT_REPO& repo, BILL_SERVICE& bill_service):Static function used for admin login interface handling.
    Parameters:
    - auth_service : authentication service reference
    - repo         : product repository reference
    - bill_service : billing service reference


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
    void viewProduct(std::string category="")override;
    void searchProduct(std::string productName) override;
    void startSession();
    
    static void handleAdminLoginUI(AUTHORITY_SERVICE& auth_service, PRODUCT_REPO& repo, BILL_SERVICE& bill_service);
};