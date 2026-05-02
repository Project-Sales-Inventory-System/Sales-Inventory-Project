#include "../include/USER_ACCOUNT.h"
#include"../include/consoleHelper.h"
#include<iostream>
#include "USER_ACCOUNT.h"
using namespace std;

USER_ACCOUNT::USER_ACCOUNT(){
    full_name="";
    username="";
    password="";
    contact_num="";
    age=0;
    location="";
    mail_address="";
    authority= Client;
        
}
USER_ACCOUNT:: USER_ACCOUNT(std:: string full_name, std:: string username, std:: string password, std:: string contact_num, int age, std:: string location, std:: string  mail_address, Authority auth)
{
    this-> full_name= full_name;
    this-> username= username;
    this-> password= password;
    this-> contact_num = contact_num;
    this-> age= age;
    this-> location= location;
    this-> mail_address = mail_address;
    this-> authority= auth;

}

Authority USER_ACCOUNT::getAuthority() const
{
    return authority;   
}

void USER_ACCOUNT::setAuthority(Authority auth)
{
    authority = auth;   
}
string USER_ACCOUNT:: getFullname() const
{
    return full_name;
}

string USER_ACCOUNT::getPassword() const
{
    return password;
}

string USER_ACCOUNT::getUsername() const
{
    return username;
}

string USER_ACCOUNT::getContactNumber() const
{
    return contact_num;
}

int USER_ACCOUNT::getAge() const
{
    return age;
}

string USER_ACCOUNT::getLocation() const
{
    return location;
}

string USER_ACCOUNT::getMailAddress() const
{
    return mail_address;
}