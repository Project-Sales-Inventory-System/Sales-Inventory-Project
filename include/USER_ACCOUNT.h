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
        std::string getLocation() const;
        std::string getMailAddress() const;
};