#include "NPC_Factory.h"

std::shared_ptr<NPC> NPC_Factory::create(const std::string& t, const std::string& n, int x, int y) {
    if (t == "Squirrel") return std::make_shared<Squirrel>(n, x, y);
    if (t == "Werewolf") return std::make_shared<Werewolf>(n, x, y);
    if (t == "Druid") return std::make_shared<Druid>(n, x, y);
    return nullptr;
}
