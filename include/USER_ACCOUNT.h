/*
USER_ACCOUNT class stores and manages account information for users within the system.

STANDARD LIBRARIES USED:
-string:Used for text handling.

ENUM Authority:Defines different user roles in the system.
-Client:General client user.
-ClientBUYER:Buyer account type.
-ClientSELLER:Seller account type.
-Admin:Administrator account type.

PRIVATE DATA MEMBERS:
authority:Stores user role and authority level.
-full_name:Stores user's full name.
-contact_num:Stores user's contact number.
-location:Stores user's address or location.
-age:Stores user's age.
-username:Stores unique username for login.
-password:Stores user password.
-mail_address:Stores user's email address.

PUBLIC FUNCTIONS:
-USER_ACCOUNT():Default constructor.
-USER_ACCOUNT(std::string full_name, std::string username, std::string password, std::string contact_num, int age, std::string location,std::string mail_address, Authority auth):Parameterized constructor used to initialize user details.
-setAuthority(Authority auth):Sets user authority level.
-getAuthority() const:Returns user authority type.
-getFullname() const:Returns user's full name.
-getPassword() const:Returns user password.
-getUsername() const:Returns username.
-getContactNumber() const:Returns contact number.
-getAge() const:Returns user age.
-getUserId() const:Returns unique user ID.
-getLocation() const:Returns user location.
-getMailAddress() const:Returns user email address.

*/
#pragma once
#include <string>

enum Authority { Client, ClientBUYER, ClientSELLER, Admin };

class USER_ACCOUNT
{
    private:
        Authority authority;
        std::string full_name;
        std::string contact_num;
        std::string location;
        int age;
        std::string username;
        std::string password, mail_address;
    public:
       USER_ACCOUNT();
       USER_ACCOUNT(std:: string full_name, std:: string username, std:: string password, std:: string contact_num, int age, std:: string location, std:: string  mail_address, Authority auth);
        void setAuthority(Authority auth);
        Authority getAuthority() const;
        std::string getFullname() const;
        std::string getPassword() const;
        std::string getUsername() const;
        std::string getContactNumber() const;
        int getAge() const;
        int getUserId() const;  
        std::string getLocation() const;
        std::string getMailAddress() const;
};