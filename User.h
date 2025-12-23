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
    User(string name, string password, bool isAdmin, bool isActive): name(std::move(name)), password(std::move(xorCipher(password, 10))), isAdmin(isAdmin), isActive(isActive){cout<<"NEW USER IS CREATED\n ";};
    virtual ~User() {}
};
#endif