#pragma once
#include "NPC.h"

class Squirrel : public NPC {
public:
    Squirrel(std::string n, int x, int y) : NPC(n, x, y, 5, 5) {}

    std::string getType() const override { return "Squirrel"; }
    void accept(NPCVisitor& v, NPC& e) override;
    void interact(NPC* other) override;
};
