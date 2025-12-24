#ifndef GIFT_ACTION_H
#define GIFT_ACTION_H

#include "Kid.h"
#include <string>
#include <iostream>
#include "kidAction.h"

using std::getline;
using std::string;
using std::getline;
using std::cin;


Gift* deleteGiftAtPos(Gift* head, int position) {
    if (!head || position < 1) return head;

    if (position <= head->jucarii.size()) {
        auto it = head->jucarii.begin();
        std::advance(it, position - 1);
        head->jucarii.erase(it);
    }
    if (position <= head->dulciuri.size()) {
        auto it = head->dulciuri.begin();
        std::advance(it, position - 1);
        head->dulciuri.erase(it);
    }

    return head;
}
void removeGift(Kid* kidList) {   
    std::string name;
    std::cout << "Enter kid's name: ";
    std::getline(std::cin >> std::ws, name);
    
    // Now searchKid is visible because Kid.h was included above
    Kid* targetKid = searchKid(kidList, name);
    if (targetKid != nullptr) {
        // Now the compiler knows what 'giftList' is because Kid.h is fully loaded
        if (targetKid->giftList != nullptr) {
            targetKid->giftList->displayGift();
            int opt;
            std::cout << "Enter option to delete: ";
            std::cin >> opt;
            targetKid->giftList = deleteGiftAtPos(targetKid->giftList, opt);
            std::cout << "Gift deleted successfully\n";
        }
    }
}
void displayGift(Kid* kidList) {
    std::string name;
    std::cout << "Enter kid's name: ";
    std::getline(std::cin >> std::ws, name);
    Kid* targetKid = searchKid(kidList, name);
    if (targetKid != nullptr && targetKid->giftList != nullptr) {
        targetKid->giftList->displayGift();
    }
}
void addKidToElfList(Kid*& head, Kid* newKid)
{
    if (head == nullptr) {
        head = newKid;
        return;
    }
    Kid* tmp = head;
    while(tmp->next != nullptr)
    {
        tmp = tmp->next;
    }
    tmp->next = newKid;
}
void AssignGiftToChild(Kid*& kidList)
{
    string kidName;
    cout << "Enter Kid's name: ";
    getline(cin >> std::ws, kidName);

    Kid* targetKid = searchKid(kidList, kidName);
   if(targetKid==nullptr) {
        cout << "Kid not found. Creating new kid\n";
        targetKid = new Kid(kidName, new Gift());
        addKidToElfList(kidList, targetKid);
    }
    if (targetKid->giftList == nullptr) {
        targetKid->giftList = new Gift();
    }
    int noOfToys;
    cout << "Enter number of Toys: ";
    cin >> noOfToys;
    for(int i = 0; i < noOfToys; i++) {
        string tName;
        float tPrice;
        cout << "Toy " << i+1 << " name: ";
        cin >> tName;
        cout << "Toy " << i+1 << " price: ";
        cin >> tPrice;
        targetKid->giftList->jucarii.push_back(std::make_tuple(tName, tPrice));
    }
    int noOfSweets;
    cout << "Enter number of Sweets: ";
    cin >> noOfSweets;
    for(int i = 0; i < noOfSweets; i++) {
        string sName;
        float sPrice;
        cout << "Sweet " << i+1 << " name: ";
        cin >> sName;
        cout << "Sweet " << i+1 << " price: ";
        cin >> sPrice;
        targetKid->giftList->dulciuri.push_back(std::make_tuple(sName, sPrice));
    }
    cout << "Gifts assigned successfully.\n";
}
void ListChildrenWithGifts(Kid* KidList)
{
    while(KidList!=nullptr)
    {
        cout<<KidList->name;
        Gift* giftList = KidList->giftList;
        while(giftList!=nullptr)
        {
            giftList->displayGift();
            giftList = giftList->next;
        }
        KidList = KidList->next;
    }
}
#endif