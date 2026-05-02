#pragma once
#include<string>
#include"../include/USER_ACCOUNT.h"
#include<vector>

#include"USER.h"

class AUTHORITY_SERVICE
{
    private:
    std::string admin_pass = "admin1234";
    std::vector<USER_ACCOUNT> registered_user;
    const std::string users_file = "users.csv";
    void loadUsersFromCsv();
    bool saveUsersToCsv() const;
    public:
    AUTHORITY_SERVICE();
    bool registerUser(USER_ACCOUNT account);
    bool verifyClient(const std::string& username, const std::string& password);
    USER* login(std::string username, std::string password);
    bool verifyAdmin(std::string passcode);
    std::vector<USER_ACCOUNT> getAllRegisteredUsers() const;
    bool deleteUserByUsername(const std::string& username);
    USER_ACCOUNT verifyAndGetAccount(const std::string& username, const std::string& password);
    bool usernameExists(const std::string& username) const;
};