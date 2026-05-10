#include <cassert>
#include <iostream>
#include "../include/USER_ACCOUNT.h"

int main() {

    // Default Authority
    USER_ACCOUNT user1;
    assert(user1.getAuthority() == Authority::Client);

    //Set and Get Authority
    user1.setAuthority(Authority::Admin);
    assert(user1.getAuthority() == Authority::Admin);

    //Change Authority Multiple Times
    user1.setAuthority(Authority::ClientBUYER);
    assert(user1.getAuthority() == Authority::ClientBUYER);

    user1.setAuthority(Authority::Admin);
    assert(user1.getAuthority() == Authority::Admin);

    //Username check
    USER_ACCOUNT user2("Rakhi Sah","rakhiiiii64", "1234", "9800000000",19,"biratnagar","abc@gmail.com",ClientBUYER);
    assert(user2.getUsername() == "rakhiiiii64");

    //Full name check
    assert(user2.getFullname() == "Rakhi Sah");

    std::cout << "All USER_ACCOUNT tests passed!\n";

    return 0;
}