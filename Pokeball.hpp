#pragma once
#include<string>


// basic class that is used to know enemy drops, pokemon deploy costs and stats (player assets)
class Pokeball
{
  public:
    Pokeball(std::string ball, int amt);

    // stores the type of pokeball and it's amount
    std::string ballType;
    int amount;
};