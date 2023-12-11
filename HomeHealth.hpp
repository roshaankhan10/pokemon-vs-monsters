#pragma once
#include"game.hpp"
#include"game.cpp"
#include"Healthbar.hpp"
#include"Healthbar.cpp"
#include"Grid.hpp"
#include"Grid.cpp"

class Castle {
private:
    Healthbar* health;
    bool isGameOver;
public:
    Castle(int maxHealth);

    Healthbar* getHealth() const;

    void decreaseHealth();
};
