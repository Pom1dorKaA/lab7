#pragma once
#include <string>
#include <iostream>
#include <fstream>

class Observer {
public:
    virtual void onKill(const std::string& killer, const std::string& victim) = 0;
};

class ConsoleObserver : public Observer {
public:
    void onKill(const std::string& killer, const std::string& victim) override {
        std::cout << killer << " killed " << victim << std::endl;
    }
};

class FileObserver : public Observer {
public:
    void onKill(const std::string& killer, const std::string& victim) override {
        std::ofstream("log.txt", std::ios::app) << killer << " killed " << victim << "\n";
    }
};
