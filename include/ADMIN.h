#pragma once
#include"USER.h"
#include"PRODUCT.h"
#include"AUTHORITY_SERVICE.h"
#include"PRODUCT_REPO.h"
#include"BILL_SERVICE.h"
#include<string>
#include<vector>
class ADMIN: public USER
{
    private:
    std:: string passcode;
    PRODUCT_REPO* repo;
    AUTHORITY_SERVICE* auth_service;
    BILL_SERVICE* bill_service;
    
    void AdminMenu();
    void handleUserManagement();
    void manageSalesReports();
    
    public:
    ADMIN(const std:: string & pass, PRODUCT_REPO& repository, AUTHORITY_SERVICE& auth_svc, BILL_SERVICE& bill_svc);
    bool authenticate(AUTHORITY_SERVICE& auth);
    void performAction();
    std:: string getUsername() const;
    void viewProduct(std::string category) override;
    void searchProduct(std::string productName) override;
    void startSession();
    
    // UI Handler Method
    static void handleAdminLoginUI(AUTHORITY_SERVICE& auth_service, PRODUCT_REPO& repo, BILL_SERVICE& bill_service);
};
