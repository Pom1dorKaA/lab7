#include "Druid.h"
#include "Visitor.h"

void Druid::accept(NPCVisitor& v, NPC& e) {
    v.fight(*this, e);
}

void Druid::interact(NPC* other) {
}
