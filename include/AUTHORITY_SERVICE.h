/*
AUTHORITY_SERVICE : Provides authentication and user management services.

STANDARD LIBRARIES USED:
-vector:Used for storing collections of data.
-string:Used for text handling.

PRIVATE DATA MEMBERS:
-admin_pass="admin1234"-Default administrator password.Used for admin verification.
-registered_user:Vector containing all registered users.
-users_file:Path of CSV file containing user data.

PRIVATE FUNCTIONS:
-loadUsersFromCsv():Loads user information from CSV file into memory.
-saveUsersToCsv():Saves all registered users to CSV file.

PUBLIC FUNCTIONS:
-AUTHORITY_SERVICE():Constructor that initializes the service.
-registerUser(USER_ACCOUNT account):Registers a new user.
-verifyClient(username, password):Verifies user login credentials.
-login(username, password):Logs user into the system.
-verifyAdmin(passcode):Verifies administrator
-getAllRegisteredUsers():Returns all registered users.
-deleteUserByUsername(username):Removes a user account using username.
-verifyAndGetAccount(username, password):Verifies credentials and returns account information.
-usernameExists(username):Checks whether username already exists.

*/
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