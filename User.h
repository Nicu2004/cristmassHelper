#ifndef USER_H
#define USER_H

#include <string>
#include "xorCipher.h"
#include <iostream>
using std::string;
using std::move;
using std::cout;
class User
{
    protected:
    std::string name;
    std::string password;
    bool isAdmin, isActive;

    public:
    string getName()
    {
        return name;
    }
    string getPassword()
    {
        return password;
    }
    void setPassword(string pass)
    {
        this->password  = pass;
    }
    bool getStatus()
    {
        return isAdmin; 
    }
    void setStatus(bool val)
    {
        isActive = val;
    }
    bool getActivity()
    {
        return isActive;
    }
    User():name(std::move("USER")), password(std::move(xorCipher("password", 0))), isAdmin(false), isActive(false){}
    User(string name, string password, bool isAdmin, bool isActive): name(std::move(name)), password(std::move(xorCipher(password, 10))), isAdmin(isAdmin), isActive(isActive){};
    virtual ~User() {}
};
User* logInUser(std::list<User*>& users)
{
    std::ifstream fff("users.txt");
    if(!fff)
    {
        std::cout << "NO FILE COULD BE OPENED";
        return nullptr;
    }

    std::string username;
    std::cout << "ENTER USERNAME: ";
    std::getline(std::cin, username);

    std::string data;
    while(std::getline(fff, data))
    {
        std::stringstream ss(data);
        std::string name, StoredPassword, inputPassword;
        bool isAdmin, isActive;

        if (ss >> name >> StoredPassword >> isAdmin >> isActive) 
        {
            if(username == name)
            {
                std::cout << "ENTER PASSWORD: ";
                SetStdinEcho(false);
                cout<<xorCipher(StoredPassword, 10)<<std::endl;
                std::getline(std::cin, inputPassword);
                SetStdinEcho(true);
                std::cout << std::endl;

                
                if(StoredPassword == xorCipher(inputPassword, 10))
                {
                    fff.close();
                    cout<<"Elf is online, hope so\n";
                    return new User(name, inputPassword, isAdmin, isActive);
                }
                else {
                    std::cout << "Password incorrect\n";
                    fff.close();
                    return nullptr;
                }
            }
        }
    }
    fff.close();
    return nullptr; 
}
#endif