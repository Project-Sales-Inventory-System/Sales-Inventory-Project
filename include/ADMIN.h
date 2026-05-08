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