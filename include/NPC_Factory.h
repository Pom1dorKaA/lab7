#pragma once
#include "Squirrel.h"
#include "Werewolf.h"
#include "Druid.h"
#include <memory>

class NPC_Factory {
public:
    static std::shared_ptr<NPC> create(const std::string& t, const std::string& n, int x, int y);
};
