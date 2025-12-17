#pragma once
#include "NPC.h"

class Druid : public NPC {
public:
    Druid(std::string n, int x, int y) : NPC(n, x, y, 10, 10) {}

    std::string getType() const override { return "Druid"; }
    void accept(NPCVisitor& v, NPC& e) override;
    void interact(NPC* other) override;
};
