#pragma once
#include <string>

class NPCVisitor;

class NPC {
protected:
    std::string name;
    int x, y;
    int walkDistance;
    int killDistance;

public:
    NPC(std::string n, int xx, int yy, int walkDist, int killDist)
        : name(n), x(xx), y(yy), walkDistance(walkDist), killDistance(killDist) {}

    virtual ~NPC() = default;
    virtual std::string getType() const = 0;
    virtual void accept(NPCVisitor &v, NPC &enemy) = 0;
    virtual void interact(NPC* other) = 0;

    std::string getName() const { return name; }
    int getX() const { return x; }
    int getY() const { return y; }
    int getWalkDistance() const { return walkDistance; }
    int getKillDistance() const { return killDistance; }
    void setX(int newX) { x = newX; }
    void setY(int newY) { y = newY; }
};
