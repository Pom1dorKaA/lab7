#include "Squirrel.h"
#include "Werewolf.h"
#include "Druid.h"
#include "Visitor.h"
#include <iostream>

void Squirrel::accept(NPCVisitor& v, NPC& e) {
    v.fight(*this, e);
}

void Squirrel::interact(NPC* other) {
    if (dynamic_cast<Werewolf*>(other)) {
        std::cout << "Squirrel kills Werewolf!" << std::endl;
    } else if (dynamic_cast<Druid*>(other)) {
        std::cout << "Squirrel kills Druid!" << std::endl;
    }
}
