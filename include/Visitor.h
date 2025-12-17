#pragma once
#include "NPC.h"
#include <iostream>

class NPCVisitor {
public:
    virtual bool fight(NPC& a, NPC& b) = 0;
};

class FightVisitor : public NPCVisitor {
public:
    bool fight(NPC& a, NPC& b) override {
        int attack1 = rand() % 6 + 1;
        int attack2 = rand() % 6 + 1;

        if (attack1 > attack2) {
            std::cout << a.getName() << " defeats " << b.getName() << std::endl;
            return true;
        } else {
            std::cout << b.getName() << " defeats " << a.getName() << std::endl;
            return true;
        }
    }
};
