#pragma once
#include <vector>
#include <memory>
#include "NPC.h"
#include "Druid.h"
#include "Squirrel.h"
#include "Werewolf.h"
#include <mutex>
#include <condition_variable>
#include <thread>
#include <chrono>
#include <atomic>

class Game {
private:
    std::vector<std::shared_ptr<NPC>> npcs;
    std::mutex mtx;
    std::condition_variable cv;
    std::atomic<bool> gameOver{false};
    int nextToAdd = 0;

public:
    void addNPC();
    void listNPC();
    void moveNPC(NPC* npc);
    void startFight(NPC* npc1, NPC* npc2);
    void printMap();
    void runMenu();
};
