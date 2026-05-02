#include "AUTHORITY_SERVICE.h"
#include"../include/ConsoleHelper.h"
#include<iostream>
#include<fstream>
#include<sstream>
using namespace std;
#include"USER_ACCOUNT.h"
#include<vector>
#include"BUYER.h"
#include"SELLER.h"
#include"ADMIN.h"

namespace
{
    string escapeCsvField(const string& field)
    {
        bool mustQuote = false;
        for (char c : field)
        {
            if (c == ',' || c == '"' || c == '\n' || c == '\r')
            {
                mustQuote = true;
                break;
            }
        }

        if (!mustQuote)
        {
            return field;
        }

        string escaped = "\"";
        for (char c : field)
        {
            if (c == '"')
            {
                escaped += "\"\"";
            }
            else
            {
                escaped += c;
            }
        }
        escaped += "\"";
        return escaped;
    }

    vector<string> parseCsvLine(const string& line)
    {
        vector<string> fields;
        string current;
        bool inQuotes = false;

        for (size_t i = 0; i < line.size(); ++i)
        {
            char ch = line[i];

            if (ch == '"')
            {
                if (inQuotes && i + 1 < line.size() && line[i + 1] == '"')
                {
                    current += '"';
                    ++i;
                }
                else
                {
                    inQuotes = !inQuotes;
                }
            }
            else if (ch == ',' && !inQuotes)
            {
                fields.push_back(current);
                current.clear();
            }
            else
            {
                current += ch;
            }
        }

        fields.push_back(current);
        return fields;
    }
}

AUTHORITY_SERVICE::AUTHORITY_SERVICE()
{
    loadUsersFromCsv();
}

void AUTHORITY_SERVICE::loadUsersFromCsv()
{
    ifstream file(users_file);
    if (!file.is_open())
    {
        return;
    }

    string line;
    bool isFirstLine = true;
    while (getline(file, line))
    {
        if (line.empty())
        {
            continue;
        }

        if (isFirstLine)
        {
            isFirstLine = false;
            if (line.find("full_name,username,password") == 0)
            {
                continue;
            }
        }

        vector<string> columns = parseCsvLine(line);
        if (columns.size() != 8)
        {
            continue;
        }

        int parsedAge = 0;
        int parsedAuthority = static_cast<int>(ClientBUYER);

        try
        {
            parsedAge = stoi(columns[4]);
            parsedAuthority = stoi(columns[7]);
        }
        catch (...)
        {
            continue;
        }

        if (parsedAuthority < static_cast<int>(ClientBUYER) || parsedAuthority > static_cast<int>(Admin))
        {
            parsedAuthority = static_cast<int>(ClientBUYER);
        }

        USER_ACCOUNT account(
            columns[0],
            columns[1],
            columns[2],
            columns[3],
            parsedAge,
            columns[5],
            columns[6],
            static_cast<Authority>(parsedAuthority)
        );

        bool duplicate = false;
        for (int i = 0; i < registered_user.size(); i++)
        {
            if (registered_user[i].getUsername() == account.getUsername())
            {
                duplicate = true;
                break;
            }
        }

        if (!duplicate)
        {
            registered_user.push_back(account);
        }
    }
}

bool AUTHORITY_SERVICE::saveUsersToCsv() const
{
    ofstream file(users_file, ios::trunc);
    if (!file.is_open())
    {
        return false;
    }

    file << "full_name,username,password,contact_num,age,location,mail_address,authority\n";

    for (int i = 0; i < registered_user.size(); i++)
    {
        const USER_ACCOUNT& account = registered_user[i];
        file
            << escapeCsvField(account.getFullname()) << ','
            << escapeCsvField(account.getUsername()) << ','
            << escapeCsvField(account.getPassword()) << ','
            << escapeCsvField(account.getContactNumber()) << ','
            << account.getAge() << ','
            << escapeCsvField(account.getLocation()) << ','
            << escapeCsvField(account.getMailAddress()) << ','
            << static_cast<int>(account.getAuthority())
            << "\n";
    }

    return true;
}

bool AUTHORITY_SERVICE::registerUser(USER_ACCOUNT account) 
{
    ConsoleHelper::SetColor(11);
    ConsoleHelper::PrintHeader("------REGISTER USER-------");
    ConsoleHelper::ResetColor();
    ConsoleHelper::PrintDivider();
    for (int i = 0; i < registered_user.size(); i++)
    {
        if (registered_user[i].getUsername() == account.getUsername())
        {
            return false;
        }
    }
    registered_user.push_back(account);

    if (!saveUsersToCsv())
    {
        registered_user.pop_back();
        return false;
    }

    cout << "User '" << account.getUsername() << "' registered successfully!" << endl;
    return true;
}

USER* AUTHORITY_SERVICE::login(std::string username, std::string password)
{
    ConsoleHelper::PrintHeader("LOGIN");
    ConsoleHelper::PrintDivider();
    cout << "Attempting login for user: " << username << endl;
    bool usernameFound = false;

    for (int i = 0; i < registered_user.size(); i++)
    {
        if (!(registered_user[i].getAuthority() == ClientBUYER || registered_user[i].getAuthority() == ClientSELLER || registered_user[i].getAuthority()==Client))
        {
            continue;
        }

        if (registered_user[i].getUsername() != username)
        {
            continue;
        }

        usernameFound = true;

        if (registered_user[i].getPassword() != password)
        {
            cout << "Password incorrect T-T" << endl;
            return nullptr;
        }

        cout << "Login Successful >-<" << endl;
        // Don't create BUYER/SELLER here - SYSTEM will do that
        // AUTHORITY_SERVICE cannot know about PRODUCT_REPO
        return nullptr;  // SYSTEM will handle user object creation
    }

    if (!usernameFound)
    {
        cout << "Username Incorrect T-T" << endl;
    }

    return nullptr;
}

bool AUTHORITY_SERVICE::verifyClient(const std::string& username, const std::string& password)
{
    for (int i = 0; i < registered_user.size(); i++)
    {
        if (registered_user[i].getUsername() == username)
        {
            if (password.empty() || registered_user[i].getPassword() == password)
            {
                return true;
            }
            else
            {
                return false; 
            }
        }
    }
    return false; 
}

bool AUTHORITY_SERVICE::verifyAdmin(std::string passcode)
{
    ConsoleHelper::PrintHeader("ADMIN VERIFICATION");
    ConsoleHelper::PrintDivider();
    cout << "Verifying admin access..." << endl;
    if (passcode == admin_pass)
            {
                return true;
            }
            else
            {
                return false;
            }
}

std::vector<USER_ACCOUNT> AUTHORITY_SERVICE::getAllRegisteredUsers() const
{
    return registered_user;
}

bool AUTHORITY_SERVICE::deleteUserByUsername(const std::string& username)
{
    for (int i = 0; i < registered_user.size(); i++)
    {
        if (registered_user[i].getUsername() == username)
        {
            registered_user.erase(registered_user.begin() + i);
            return saveUsersToCsv();
        }
    }

    return false;
}

USER_ACCOUNT AUTHORITY_SERVICE::verifyAndGetAccount(const std::string& username, const std::string& password)
{
    for (int i = 0; i < registered_user.size(); i++)
    {
        if (registered_user[i].getUsername() == username)
        {
            if (registered_user[i].getPassword() == password)
            {
                cout << "Login Successful >-<" << endl;
                return registered_user[i];  // Return copy, not pointer
            }
            else
            {
                cout << "Password incorrect T-T" << endl;
                return USER_ACCOUNT();  // Return empty account
            }
        }
    }
    cout << "Username Incorrect T-T" << endl;
    return USER_ACCOUNT();  // Return empty account
}

bool AUTHORITY_SERVICE::usernameExists(const std::string& username) const
{
    for (int i = 0; i < registered_user.size(); i++)
    {
        if (registered_user[i].getUsername() == username)
        {
            return true;
        }
    }
    return false;
}

