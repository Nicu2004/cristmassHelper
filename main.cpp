#include <iostream>
#include <string>
#include <list>
#include <vector>
#include <fstream>
#include <sstream>
#include "xorCipher.h"
#include "diplayMenu.h"
#include "User.h"
#include "Gift.h"
#include "Kid.h"
#include "Elf.h"
#include "giftActions.h"

using std::cin;
using std::cout;
using std::string;
using std::list;
using std::ifstream;
using std::ofstream;
using std::stringstream;
using std::vector;
using std::get;

void showReports(Kid* kidList)
{
    Kid* tmp = kidList;
    while(tmp!=nullptr)
    {
        float totalPrice = 0.0;
        int numOfGifts = 0;
        cout<<tmp->name<<" ";
        Gift* giftList = tmp->giftList;
        while(giftList!=nullptr)
        {
            std::list<std::tuple<string, float>>::iterator itr1 = giftList->jucarii.begin();
            while(itr1!=giftList->jucarii.end())
            {
                totalPrice+=std::get<1>(*itr1);
                itr1++;
            }
            std::list<std::tuple<string, float>>::iterator itr2 = giftList->dulciuri.begin();
            while(itr2!=giftList->dulciuri.end())
            {
                totalPrice+=std::get<1>(*itr2);
                itr2++;
            }
            numOfGifts++;
            giftList = giftList->next;
        }
        cout<<"Number of gifts: "<<numOfGifts<<" Total price is: "<<totalPrice<<"\n";
        tmp = tmp->next;
        }
}
//admin astuff


list<User*> usersList;
void loadElfs()
{
    ifstream fff("users.txt");
    if(!fff.is_open())
    {
        puts("error oppeng the file");
        return ;
    }
    string lineToRead;
    while(getline(fff, lineToRead))
    {
        stringstream ss(lineToRead);
        string elfName;
        string password;
        int status;
        int activity;
        ss>>elfName>>password>>status>>activity;
        cout<<elfName<<"\n";
        User* user = new User(elfName, password, status, activity);
        usersList.push_back(user);
    }
    cout << "\nTotal users loaded: " << usersList.size() << std::endl;
    cout << "List of names:\n";
    
    for (User* u : usersList) 
    {
        cout << "- " << u->getName() << "\n"; 
    }
}
int sortDataElfs(list<User*>&UserList)
{
    UserList.sort([](User* entr1, User* entr2){
        return entr1->getName()<entr2->getName();});
        if(&UserList)
            return 1;
        return 0;
}
std::list<GeneralElf*> generalElfKidList;
void readGeneralElfKidList();
void CreateNewElf()
{
    cout<<"Creating new Elf\n";
    string name;
    cout<<"Enter Elf's name: ";
    cin>>name;
    string password;
    cout<<"Enter elfs password: ";
    cin>>password;
    User* elf = new User(name, xorCipher(password, 10), false, true);//by default the elf's account will be enabled, on the way this can be disabled
    usersList.push_back(elf);
    cout<<"New Elf Created";
    if(sortDataElfs(usersList)==1)
    {
        cout<<"Sorted\n";
    }
}
void ChangeExistingElfPassword(){
    string name;
    cout<<"Enter elf name: ";
    cin>>name;
    list<User*>::iterator elfItr = usersList.begin();
    while(elfItr!=usersList.end())
    {
        if(name.compare((*elfItr)->getName())==0)
        {
            string password;
            cout<<"Enter new Password";
            cin>>password;
            (*elfItr)->setPassword(password);
            cout<<"Password change succesfuly\n";
            return;
        }
        elfItr++;
    }
    cout<<"Elf not found:\n";
}
void disableElfAccount(){
    string name;
    cout<<"Enter elf name";
    list<User*>::iterator elfItr = usersList.begin();
    while(elfItr!=usersList.end())
    {
        if(name.compare((*elfItr)->getName())==0)
        {
            (*elfItr)->setStatus(false);
            return;
        }
        elfItr++;
    }
    cout<<"Elf not found:\n";
}
void Raports(){
    readGeneralElfKidList();
    list<GeneralElf*>::iterator elfItr = generalElfKidList.begin();
    while(elfItr!=generalElfKidList.end())
    {
        showReports((*elfItr)->KidList);
        elfItr++;
    }
}
void saveNewElfData();
void DoAdminStuff(User* admin)
{
    cout<<"User is admin\n";
    do
    {
        adminMenu();
        int option;
        cout<<"Enter option: ";
        cin>>option;
        cin.ignore(1000, '\n');
        switch (option)
        {
        case 1: CreateNewElf(); break;
        case 2: ChangeExistingElfPassword();break;
        case 3: disableElfAccount();break;
        case 4: Raports(); break;
        case 5: return;
        }
    } while (true);
}
void doElfStuff(Elf* elf)
{
    cout<<"Elf is Online\n";
    do
    {
        elfMenu();
        int option;
        cout<<"Enter option: ";
        cin>>option;
        cin.ignore(1000, '\n');
        switch (option)
        {
        case 1: AssignGiftToChild(elf->kidList);break;
        case 2: ListChildrenWithGifts(elf->kidList);break;
        case 3: displayKid(elf->kidList);break;
        case 4: displayGift(elf->kidList); break;
        case 5: removeGift(elf->kidList); break;
        case 6: showReports(elf->kidList); break;
        case 0: return;
        }
    } while (true);
}
//pre use && post use
void addNewGift(Gift*& head, Gift* newGift)
{
    if (head == nullptr) {
        head = newGift;
        return;
    }
    Gift* tmp = head;
    while(tmp->next != nullptr)
    {
        tmp = tmp->next;
    }
    tmp->next = newGift;
}
void readGeneralElfKidList()
{
    generalElfKidList.clear();
    std::ifstream ffg("gifts.txt");
    if(!ffg.is_open())
    {
        cout<<"FILE COUD NOT BE OPPENED";
        exit(1);
    }
    string lineToRead;
    while(getline(ffg, lineToRead))
    {
        std::stringstream ss(lineToRead);
        string elfName, kidName;
        if(lineToRead.empty())continue;

        if(!(ss>>elfName>>kidName)) continue;

        list<std::tuple<string, float>> jucarii;
        list<std::tuple<string, float>> duciuri;
        
        string itemName;
        float price;
        bool isToy = true;

        while(ss>>itemName>>price)
        {
            if(isToy)jucarii.push_back(std::make_tuple(itemName, price));
      
               else duciuri.push_back(std::make_tuple(itemName, price));
               isToy = !isToy;
            
        }
        Gift* newGift  = new Gift(jucarii, duciuri);
        Kid* newKid = new Kid(kidName, newGift);
        newKid->next = nullptr;
        GeneralElf* targetElf = nullptr;

        if(!generalElfKidList.empty())
        {
            if(generalElfKidList.back()->name==elfName)
            {
                targetElf = generalElfKidList.back();
            }
        }
        if(targetElf!=nullptr)
        {
            if(targetElf->KidList==nullptr)
            {
                targetElf->KidList = newKid;
            }
            else{
                Kid* tmp = targetElf->KidList;
                while(tmp->next!=nullptr)
                {
                    tmp = tmp->next;
                }
                tmp->next = newKid;
            }
        }
        else{
            GeneralElf * newElf = new GeneralElf(elfName, newKid);
            generalElfKidList.push_back(newElf);
        }
    }
    ffg.close();
}
void readKidList(Elf* elf)
{
   list<GeneralElf*>::iterator elfItr = generalElfKidList.begin();
   while(elfItr!= generalElfKidList.end())
   {
        if((*elfItr)->name.compare(elf->getName())==0)
        {
            elf->kidList = (*elfItr)->KidList;
            cout<<elf->getName()<<"\n";
            Kid* tmp = elf->kidList;
            while(tmp!=nullptr)
            {
                tmp->displayData();
                tmp= tmp->next;
            }
            return;
        }
        elfItr++;
   }
   cout<<"ELF HAS NO KIDS\n";

}
int sortData(list<GeneralElf*> generalElfKidList)
{
    generalElfKidList.sort([](GeneralElf * entr1, GeneralElf* entr2){
        return entr1->name<entr2->name;});
        if(&generalElfKidList)
            return 1;
        return 0;
}
void writeToFile(std::list<GeneralElf*>& elfList) {
    ofstream ffc("gifts.txt");
    if (!ffc.is_open()) return;

    for (auto const& elf : elfList) {
        Kid* currentKid = elf->KidList;
        while (currentKid != nullptr) {
            ffc << elf->name << " " << currentKid->name; 
            if (currentKid->giftList != nullptr) {
                auto toyItr = currentKid->giftList->jucarii.begin();
                auto sweetItr = currentKid->giftList->dulciuri.begin();
                while (toyItr != currentKid->giftList->jucarii.end()) {
                    ffc << " " << std::get<0>(*toyItr) << " " << std::get<1>(*toyItr);
                
                    if (sweetItr != currentKid->giftList->dulciuri.end()) {
                        ffc << " " << std::get<0>(*sweetItr) << " " << std::get<1>(*sweetItr);
                        ++sweetItr;
                    }
                    ++toyItr;
                }
            }
            ffc << "\n";
            currentKid = currentKid->next;
        }
    }
    ffc.close();
}
void updateGenralElfList(Elf* elf) {
    generalElfKidList.remove_if([&](GeneralElf* gelf) {
        if (gelf->name == elf->getName()) {
            gelf->KidList = nullptr; 
            delete gelf;
            return true;
        }
        return false;
    });

    if (elf->kidList != nullptr) {
        GeneralElf* gelf = new GeneralElf(elf->getName(), elf->kidList);
        generalElfKidList.push_back(gelf);
    }
    
    sortData(generalElfKidList);
    writeToFile(generalElfKidList); 
}
void saveNewElfData()
{
    ofstream ffg("users.txt");
    list<User*>::iterator elfItr = usersList.begin();
    while(elfItr!=usersList.end())
    {
        ffg<<(*elfItr)->getName()<<" "<<(*elfItr)->getPassword()<<" "<<(*elfItr)->getStatus()<<" "<<(*elfItr)->getActivity()<<std::endl;
        elfItr++;
    }
}
int main()
{
    list<User*> users;
    User *user = nullptr;
    while(user==nullptr)
    {
        user = logInUser(users);
        if(user!=nullptr)
        {
            if((user)->getStatus()==1)
            {
                loadElfs();
                DoAdminStuff(user);
                saveNewElfData();
                delete(user);
            }
            else{
                if((user)->getActivity()==1) {
                Elf* elfUser = new Elf(user->getName(), user->getPassword(), false, true, nullptr);
                readGeneralElfKidList();
                readKidList(elfUser);
                doElfStuff(elfUser);
                updateGenralElfList(elfUser); 
                elfUser->kidList = nullptr; 
                delete elfUser;
}
            else{
                    cout<<"Elf is not active\n";
                }
            }
        }
        else{
            cout<<"User not found\n";
        }
    }
    return 0;
}