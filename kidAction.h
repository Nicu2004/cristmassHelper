#ifndef KID_ACTION_H
#define KID_ACTION_H
#include "Kid.h"
#include <string>
#include <iostream>

using std::string;
using std::cin;
Kid* searchKid(Kid* listHead, string name)
{
    while(listHead!=nullptr)
    {
        if(name.compare(listHead->name)==0)
        {
            return listHead;
        }
        listHead = listHead->next;
    }
    return nullptr;
}
void displayKid(Kid* kid)
{
    string name;
    cout<<"Enter child's Name: \n";
    cin>>name;
    cin.ignore(1000, '\n');
    Kid *targetKid = searchKid(kid, name);
    if(targetKid!=nullptr)
    {
        targetKid->displayData();
    }
    else{
        cout<<"No kid found\n";
    }
}
#endif