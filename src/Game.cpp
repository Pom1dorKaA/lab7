#include "Game.h"
#include <iostream>
#include <thread>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include "Visitor.h"

void Game::addNPC() {
    std::unique_lock<std::mutex> lock(mtx);
    switch (nextToAdd) {
        case 0:
            npcs.push_back(std::make_shared<Druid>("Druid", 0, 0));
            std::cout << "Added Druid\n";
            break;
        case 1:
            npcs.push_back(std::make_shared<Squirrel>("Squirrel", 5, 5));
            std::cout << "Added Squirrel\n";
            break;
        case 2:
            npcs.push_back(std::make_shared<Werewolf>("Werewolf", 10, 10));
            std::cout << "Added Werewolf\n";
            break;
    }
    nextToAdd = (nextToAdd + 1) % 3;
    listNPC();
}

void Game::listNPC() {
    for (auto& npc : npcs) {
        std::cout << npc->getName() << " at (" << npc->getX() << ", " << npc->getY() << ")\n";
    }
}

void Game::moveNPC(NPC* npc) {
    std::unique_lock<std::mutex> lock(mtx);
    int dir = std::rand() % 4;
    int wx = npc->getWalkDistance();
    int nx = npc->getX();
    int ny = npc->getY();
    switch (dir) {
        case 0: nx = nx + wx; break;
        case 1: nx = std::max(0, nx - wx); break;
        case 2: ny = ny + wx; break;
        case 3: ny = std::max(0, ny - wx); break;
    }
    npc->setX(nx);
    npc->setY(ny);
}

void Game::startFight(NPC* npc1, NPC* npc2) {
    std::unique_lock<std::mutex> lock(mtx);
    if (npc1->getKillDistance() > npc2->getKillDistance()) {
        std::cout << npc1->getName() << " wins\n";
    } else {
        std::cout << npc2->getName() << " wins\n";
    }
    gameOver = true;
    cv.notify_all();
}

void Game::printMap() {
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
    while (!gameOver) {
        std::this_thread::sleep_for(std::chrono::seconds(1));
        for (auto& npc : npcs) {
            moveNPC(npc.get());
        }
            {
                std::unique_lock<std::mutex> lock(mtx);
                bool changed = true;
                while (changed) {
                    changed = false;
                    for (size_t i = 0; i < npcs.size(); ++i) {
                        for (size_t j = i + 1; j < npcs.size(); ++j) {
                            auto &a = npcs[i];
                            auto &b = npcs[j];
                            int dx = a->getX() - b->getX();
                            int dy = a->getY() - b->getY();
                            int dist2 = dx*dx + dy*dy;
                            int r1 = a->getKillDistance();
                            int r2 = b->getKillDistance();
                            if (dist2 <= r1*r1 || dist2 <= r2*r2) {
                                FightVisitor fv;
                                bool aWins = fv.fight(*a, *b);
                                if (aWins) {
                                    std::cout << a->getName() << " killed " << b->getName() << "\n";
                                    npcs.erase(npcs.begin() + j);
                                } else {
                                    std::cout << b->getName() << " killed " << a->getName() << "\n";
                                    npcs.erase(npcs.begin() + i);
                                }
                                changed = true;
                                break;
                            }
                        }
                        if (changed) break;
                    }
                }
            }
            listNPC();
            std::cout << "---\n";
            {
                std::unique_lock<std::mutex> lock(mtx);
                if (npcs.size() <= 1) {
                    gameOver = true;
                    cv.notify_all();
                    break;
                }
            }
    }
}

void Game::runMenu() {
    bool gameStarted = false;
    while (!gameOver) {
        if (!gameStarted) {
            std::cout << "1) Add NPC\n";
            std::cout << "2) Start Game\n";
            std::cout << "3) Exit\n";

            int choice;
            std::cin >> choice;

            switch (choice) {
                case 1: 
                    addNPC();
                    break;
                case 2: {
                    gameStarted = true;
                    std::thread printMapThread(&Game::printMap, this);
                    printMapThread.detach();
                    break;
                }
                case 3:
                    gameOver = true;
                    break;
            }
        } else {
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }
    }
}
