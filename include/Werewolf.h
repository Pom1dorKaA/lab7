#pragma once
#include "NPC.h"

class Werewolf : public NPC {
public:
    Werewolf(std::string n, int x, int y) : NPC(n, x, y, 20, 10) {}

    std::string getType() const override { return "Werewolf"; }
    void accept(NPCVisitor& v, NPC& e) override;
    void interact(NPC* other) override;
};
