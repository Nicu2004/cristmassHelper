#ifndef GIFT_H
#define GIFT_H

#include <string>
#include "xorCipher.h"
#include <iostream>
#include <list>
#include <tuple>
using std::string;
using std::move;
using std::cout;
using std::list;

class Gift {
public:

    std::list<std::tuple<std::string, float>> jucarii;
    std::list<std::tuple<std::string, float>> dulciuri;
    Gift *next;

    Gift(std::list<std::tuple<std::string, float>> j, std::list<std::tuple<std::string, float>> d) 
        : jucarii(j), dulciuri(d), next(nullptr) {}
    Gift() : next(nullptr) {}

    void displayGift() {
        std::cout << "Jucarii: ";
        for (auto const& i : jucarii) std::cout << std::get<0>(i) << " ";
        std::cout << "\nDulciuri: ";
        for (auto const& i : dulciuri) std::cout << std::get<0>(i) << " ";
        std::cout << "\n";
    }
    ~Gift(){delete next;};
};

#endif