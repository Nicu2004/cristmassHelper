#ifndef KID_H
#define KID_H


#include "Gift.h"
#include <string>
#include <iostream>

using std::move;
using std::string;
using std::cout;

class Kid
{
    public:
        Gift*giftList;
        string name;
        Kid* next;
        Kid(string name, Gift *giftList): name(move(name)), giftList(giftList),next(nullptr){}
        Kid(): name("NULL"), giftList(nullptr), next(nullptr){};
        void displayData()
        {
            cout<<"Kid's name: "<<name;
            if(giftList!=nullptr)
            {
                giftList->displayGift();
            }
            else
            {
                cout<<"No data to be displayed\n";
            }
        }
        ~Kid(){
            delete giftList;
        }
};
#endif