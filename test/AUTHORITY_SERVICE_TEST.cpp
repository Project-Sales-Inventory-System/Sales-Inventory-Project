#include<cassert>
#include<iostream>
#include"../include/AUTHORITY_SERVICE.h"
#include"../include/USER_ACCOUNT.h"

int main(){
    AUTHORITY_SERVICE auth;

    //register sucessfull
    USER_ACCOUNT user1("Rakhi Sah","rakhi123", "1234", "9800000000",19,"biratnagar","abc@gmail.com",ClientBUYER);
    bool registered = auth.registerUser(user1);
    assert(registered == true);

    //register failed
    USER_ACCOUNT user2("Rakhi Sah","rakhi123", "1234", "9800000000",19,"biratnagar","abc@gmail.com",ClientBUYER);
    bool not_registered = auth.registerUser(user2);
    assert(not_registered == false);

    //login test

    //username exist
    assert(auth.usernameExists("rakhi123")==true);

    //username doesnot exist
    assert(auth.usernameExists("abc123")==false);

    //Verify client (correct password)
    assert(auth.verifyClient("rakhi123", "1234") == true);

    //Verify client (wrong password)
    assert(auth.verifyClient("rakhi123", "wrong") == false);

    //Verify and get account (correct login)
    USER_ACCOUNT acc = auth.verifyAndGetAccount("rakhi123", "1234");
    assert(acc.getUsername() == "rakhi123");

    //Wrong login returns empty account
    USER_ACCOUNT wrongAcc = auth.verifyAndGetAccount("rakhi123", "5678");
    assert(wrongAcc.getUsername() == "");

    //Delete user
    bool deleted = auth.deleteUserByUsername("rakhi123");
    assert(deleted == true);

    //User should not exist after deletion
    assert(auth.usernameExists("rakhi123") == false);

    //Admin verification
    USER_ACCOUNT user("Admin","admin123", "abcd", "9800000000",30,"brt","123@gmail.com",Admin);
    auth.registerUser(user);

    //Verify admin (correct password)
    assert(auth.verifyAdmin("admin1234") == true);

    //Verify admin (wrong password)
    assert(auth.verifyAdmin("1234") == false);


    std::cout << "All AUTHORITY_SERVICE tests passed!\n";

    return 0;
}