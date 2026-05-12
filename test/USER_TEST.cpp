#include<cassert>
#include<iostream>
#include<sstream>
#include<cstdio>
#include"../include/USER.h"
#include"../include/AUTHORITY_SERVICE.h"
#include"../include/USER_ACCOUNT.h"
#include"../include/PRODUCT_REPO.h"
#include"../include/BUYER.h"
#include"../include/SELLER.h"
#include"../include/BILL_SERVICE.h"

using namespace std;

bool isValidName(const string& name) {
    int spaces = 0;
    for (char c : name) if (c == ' ') spaces++;
    return !name.empty() && spaces >= 1;
}

bool isValidUsername(const string& username) {
    if (username.empty() || username.length() < 5) return false;
    string specialChars = "@#$%&!^*()_+-=[]{}|;:,.<>?/~`";
    for (char c : username)
        if (specialChars.find(c) != string::npos) return true;
    return false;
}

bool isValidContact(const string& contact) {
    if (contact.length() != 10) return false;
    for (char c : contact) if (!isdigit(c)) return false;
    return contact.substr(0, 2) == "97" || contact.substr(0, 2) == "98";
}

bool isValidEmail(const string& email) {
    return email.find("@gmail")   != string::npos ||
           email.find("@outlook") != string::npos ||
           email.find("@yahoo")   != string::npos;
}

bool isValidPassword(const string& password) {
    return !password.empty() && password.length() >= 5;
}

int main()
{
    
    {
        //single word name fails
        assert(isValidName("Rakhi") == false);
    
        //two word name passes
        assert(isValidName("Rakhi Sah") == true);
    
        //empty name fails
        assert(isValidName("") == false);

        //three word name passes
        assert(isValidName("Rakhi Kumar Sah") == true);
    
        //too short fails
        assert(isValidUsername("ra@1") == false);

        //no special char fails
        assert(isValidUsername("rakhi123") == false);

        //empty username fails
        assert(isValidUsername("") == false);

        //valid username passes
        assert(isValidUsername("rakhi@123") == true);

        //exactly 5 chars with special char passes
        assert(isValidUsername("ab@cd") == true);

        //too short fails
        assert(isValidPassword("abc") == false);    

        //empty password fails
        assert(isValidPassword("") == false);
           

        //exactly 5 chars passes
        assert(isValidPassword("abcde") == true);

        //valid password passes
        assert(isValidPassword("pass123") == true);

        //too short fails
        assert(isValidContact("12345") == false);

        //wrong prefix fails
        assert(isValidContact("1234567890") == false);    

        //contains letters fails
        assert(isValidContact("981234567a") == false);

        //valid 98 prefix passes
        assert(isValidContact("9812345678") == true);    
            
        //valid 97 prefix passes
        assert(isValidContact("9712345678") == true);    
            
        //hotmail domain fails
        assert(isValidEmail("rakhi@hotmail.com") == false);

        //empty email fails
        assert(isValidEmail("") == false);
        
        //gmail passes
        assert(isValidEmail("rakhi@gmail.com") == true);

        //outlook passes
        assert(isValidEmail("rakhi@outlook.com") == true);    
        
        //yahoo passes
        assert(isValidEmail("rakhi@yahoo.com") == true);
    }
    
    std::cout << "\nAll USER tests passed!" << endl;
    return 0;
}