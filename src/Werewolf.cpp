#include "Werewolf.h"
#include "Druid.h"
#include "Visitor.h"
#include <iostream>

void Werewolf::accept(NPCVisitor& v, NPC& e) {
    v.fight(*this, e);
}

void Werewolf::interact(NPC* other) {
    if (dynamic_cast<Druid*>(other)) {
        std::cout << "Werewolf kills Druid!" << std::endl;
    }
}
