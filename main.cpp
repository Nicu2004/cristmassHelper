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

using std::cin;
using std::cout;
using std::string;
using std::list;
using std::ifstream;
using std::ofstream;
using std::stringstream;
using std::vector;
using std::get;

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
list<Elf*> elfList;
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
        Elf* elf = new Elf(elfName, password, status, activity, nullptr);
        elfList.push_back(elf);
    }
    cout<<elfList.size();
}
int sortDataElfs(list<Elf*>&ElfList)
{
    ElfList.sort([](Elf * entr1, Elf* entr2){
        return entr1->getName()<entr2->getName();});
        if(&ElfList)
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
    cout<<"Enter elf;s password: ";
    cin>>password;
    Elf* elf = new Elf(name, xorCipher(password, 10), false, true, nullptr);//by default the elf's account will be enabled, on the way this can be disabled
    elfList.push_back(elf);
    cout<<"New Elf Created";
    if(sortDataElfs(elfList)==1)
    {
        cout<<"Sorted\n";
    }
}
void ChangeExistingElfPassword(){
    string name;
    cout<<"Enter elf name";
    list<Elf*>::iterator elfItr = elfList.begin();
    while(elfItr!=elfList.end())
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
    list<Elf*>::iterator elfItr = elfList.begin();
    while(elfItr!=elfList.end())
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
   cout<<"COULD NOT FIND THE ELF;";
   exit(1);
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
    list<Elf*>::iterator elfItr = elfList.begin();
    while(elfItr!=elfList.end())
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
                DoAdminStuff(user);
                loadElfs();
                saveNewElfData();
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