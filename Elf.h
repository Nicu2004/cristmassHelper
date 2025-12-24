#ifndef ELF_H
#define ELF_H
#include "User.h"
#include "Kid.h"
#include "xorCipher.h"
#include <string>

using std::string;
class Elf: public User
{
    public:
        Kid* kidList;
        Elf(): kidList(nullptr),User(){}
        Elf(string nume, string password, bool isAdmin, bool isActive, Kid* kidList):User(nume, xorCipher(password, 10), false, true), kidList(kidList){}
        virtual~Elf(){delete kidList;};
};
class GeneralElf
{
    public:
    string name;
    Kid* KidList;
    GeneralElf(string name, Kid* KidList):name(name), KidList(KidList){}
    virtual ~GeneralElf(){delete KidList;}
};
#endif